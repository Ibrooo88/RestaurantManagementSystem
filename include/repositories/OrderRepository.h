#ifndef ORDERREPOSITORY_H
#define ORDERREPOSITORY_H

#include "../models/Order.h"
#include "../enums/OrderStatus.h"
#include <vector>

class OrderRepository {
public:
    Order* getById(int id);
    Order* getByOrderNumber(const std::string& orderNumber);
    std::vector<Order*> getAll();
    std::vector<Order*> getByStatus(OrderStatus status);
    std::vector<Order*> getByTableId(int tableId);
    std::vector<Order*> getByChefId(int chefId);
    bool insert(Order* order);
    bool update(Order* order);
    bool deleteById(int id);
    std::string generateOrderNumber();
};

#endif // ORDERREPOSITORY_H

