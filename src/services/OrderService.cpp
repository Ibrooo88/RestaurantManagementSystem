#include "../../include/services/OrderService.h"
#include "../../include/repositories/OrderRepository.h"
#include "../../include/repositories/OrderItemRepository.h"
#include "../../include/repositories/MenuItemRepository.h"
#include "../../include/utils/Logger.h"
#include "../../include/utils/PriceCalculator.h"
#include "../../include/utils/SimulationMode.h"
#include "../../include/enums/OrderType.h"
#include "../../include/enums/OrderStatus.h"
#include <algorithm>

Order* OrderService::createOrder(int tableId, const std::string& customerName,
                                const std::map<int, int>& menuItems) {
    OrderRepository orderRepo;
    OrderItemRepository orderItemRepo;
    MenuItemRepository menuItemRepo;
    
    // Generate order number
    std::string orderNumber = orderRepo.generateOrderNumber();
    
    // Create order
    Order* order = new Order();
    order->setOrderNumber(orderNumber);
    order->setTableId(tableId);
    order->setOrderType(OrderType::NORMAL);
    order->setStatus(OrderStatus::PENDING);
    order->setCustomerName(customerName);
    
    // Calculate total
    double total = 0.0;
    for (const auto& item : menuItems) {
        MenuItem* menuItem = menuItemRepo.getById(item.first);
        if (menuItem) {
            total += menuItem->getPrice() * item.second;
            delete menuItem;
        }
    }
    order->setTotalAmount(total);
    
    // Insert order
    bool inserted = false;
    if (SimulationMode::isEnabled()) {
        inserted = SimulationMode::insertMockOrder(order);
    } else {
        inserted = orderRepo.insert(order);
    }
    
    if (!inserted) {
        delete order;
        return nullptr;
    }
    
    // Insert order items
    for (const auto& item : menuItems) {
        MenuItem* menuItem = menuItemRepo.getById(item.first);
        if (menuItem) {
            OrderItem* orderItem = new OrderItem();
            orderItem->setOrderId(order->getId());
            orderItem->setMenuItemId(item.first);
            orderItem->setQuantity(item.second);
            orderItem->setPrice(menuItem->getPrice());
            orderItemRepo.insert(orderItem);
            delete menuItem;
            delete orderItem;
        }
    }
    
    Logger::getInstance().info("Order created: " + orderNumber);
    return order;
}

bool OrderService::updateOrderStatus(int orderId, OrderStatus status) {
    OrderRepository orderRepo;
    Order* order = orderRepo.getById(orderId);
    if (!order) {
        return false;
    }
    
    order->setStatus(status);
    bool result = false;
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        result = SimulationMode::updateMockOrder(orderId, order);
    } else {
        result = orderRepo.update(order);
    }
    
    delete order;
    return result;
}

bool OrderService::assignChefToOrder(int orderId, int chefId) {
    OrderRepository orderRepo;
    Order* order = orderRepo.getById(orderId);
    if (!order) {
        return false;
    }
    
    order->setChefId(chefId);
    order->setStatus(OrderStatus::IN_PROGRESS);
    bool result = false;
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        result = SimulationMode::updateMockOrder(orderId, order);
    } else {
        result = orderRepo.update(order);
    }
    
    delete order;
    return result;
}

std::vector<Order*> OrderService::getPendingOrders() {
    OrderRepository orderRepo;
    return orderRepo.getByStatus(OrderStatus::PENDING);
}

std::vector<Order*> OrderService::getOrdersByTable(int tableId) {
    OrderRepository orderRepo;
    return orderRepo.getByTableId(tableId);
}

bool OrderService::completeOrder(int orderId) {
    return updateOrderStatus(orderId, OrderStatus::COMPLETED);
}

double OrderService::calculateOrderTotal(int orderId) {
    OrderRepository orderRepo;
    Order* order = orderRepo.getById(orderId);
    if (!order) {
        return 0.0;
    }
    
    double total = order->getTotalAmount();
    delete order;
    return total;
}

