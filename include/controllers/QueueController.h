#ifndef QUEUECONTROLLER_H
#define QUEUECONTROLLER_H

#include "../models/Order.h"
#include "../enums/OrderStatus.h"
#include <vector>

class QueueController {
public:
    static std::vector<Order*> getPendingOrders();
    static std::vector<Order*> getInProgressOrders();
    static std::vector<Order*> getReadyOrders();
    static bool assignChefToOrder(int orderId, int chefId);
    static bool updateOrderStatus(int orderId, OrderStatus status);
    static bool markOrderAsReady(int orderId);
    static bool markOrderAsServed(int orderId);
    static bool completeOrder(int orderId);
    static Order* getNextOrderInQueue();
    static int getQueueSize();
};

#endif // QUEUECONTROLLER_H

