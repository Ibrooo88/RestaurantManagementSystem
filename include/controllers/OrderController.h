#ifndef ORDERCONTROLLER_H
#define ORDERCONTROLLER_H

#include "../models/Order.h"
#include "../services/OrderService.h"
#include <vector>
#include <map>

class OrderController {
public:
    static Order* createOrder(int tableId, const std::string& customerName,
                             const std::map<int, int>& menuItems);
    static bool updateOrderStatus(int orderId, int status);
    static std::vector<Order*> getAllOrders();
    static std::vector<Order*> getOrdersByTable(int tableId);
    static bool assignChef(int orderId, int chefId);
};

#endif // ORDERCONTROLLER_H

