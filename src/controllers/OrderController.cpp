#include "../../include/controllers/OrderController.h"
#include "../../include/enums/OrderStatus.h"
#include "../../include/repositories/OrderRepository.h"

Order* OrderController::createOrder(int tableId, const std::string& customerName,
                                   const std::map<int, int>& menuItems) {
    return OrderService::createOrder(tableId, customerName, menuItems);
}

bool OrderController::updateOrderStatus(int orderId, int status) {
    OrderStatus orderStatus = static_cast<OrderStatus>(status);
    return OrderService::updateOrderStatus(orderId, orderStatus);
}

std::vector<Order*> OrderController::getAllOrders() {
    OrderRepository orderRepo;
    return orderRepo.getAll();
}

std::vector<Order*> OrderController::getOrdersByTable(int tableId) {
    return OrderService::getOrdersByTable(tableId);
}

bool OrderController::assignChef(int orderId, int chefId) {
    return OrderService::assignChefToOrder(orderId, chefId);
}

