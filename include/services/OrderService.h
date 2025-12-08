#ifndef ORDERSERVICE_H
#define ORDERSERVICE_H

#include "../models/Order.h"
#include "../models/OrderItem.h"
#include "../enums/OrderStatus.h"
#include "../enums/OrderType.h"
#include <vector>
#include <map>

class OrderService {
public:
    static Order* createOrder(int tableId, const std::string& customerName, 
                             const std::map<int, int>& menuItems); // menuItemId -> quantity
    static bool updateOrderStatus(int orderId, OrderStatus status);
    static bool assignChefToOrder(int orderId, int chefId);
    static std::vector<Order*> getPendingOrders();
    static std::vector<Order*> getOrdersByTable(int tableId);
    static bool completeOrder(int orderId);
    static double calculateOrderTotal(int orderId);
};

#endif // ORDERSERVICE_H
