#include "../../include/controllers/QueueController.h"
#include "../../include/services/OrderService.h"
#include "../../include/repositories/OrderRepository.h"
#include "../../include/enums/OrderStatus.h"
#include "../../include/utils/Logger.h"

std::vector<Order*> QueueController::getPendingOrders() {
    return OrderService::getPendingOrders();
}

std::vector<Order*> QueueController::getInProgressOrders() {
    OrderRepository orderRepo;
    return orderRepo.getByStatus(OrderStatus::IN_PROGRESS);
}

std::vector<Order*> QueueController::getReadyOrders() {
    OrderRepository orderRepo;
    return orderRepo.getByStatus(OrderStatus::READY);
}

bool QueueController::assignChefToOrder(int orderId, int chefId) {
    return OrderService::assignChefToOrder(orderId, chefId);
}

bool QueueController::updateOrderStatus(int orderId, OrderStatus status) {
    return OrderService::updateOrderStatus(orderId, status);
}

bool QueueController::markOrderAsReady(int orderId) {
    return OrderService::updateOrderStatus(orderId, OrderStatus::READY);
}

bool QueueController::markOrderAsServed(int orderId) {
    return OrderService::updateOrderStatus(orderId, OrderStatus::SERVED);
}

bool QueueController::completeOrder(int orderId) {
    return OrderService::completeOrder(orderId);
}

Order* QueueController::getNextOrderInQueue() {
    auto pendingOrders = getPendingOrders();
    if (pendingOrders.empty()) {
        return nullptr;
    }
    
    // Return the first pending order
    Order* nextOrder = pendingOrders[0];
    // Create a copy for return
    Order* result = new Order(*nextOrder);
    
    // Clean up
    for (auto* order : pendingOrders) {
        delete order;
    }
    
    return result;
}

int QueueController::getQueueSize() {
    return static_cast<int>(getPendingOrders().size());
}

