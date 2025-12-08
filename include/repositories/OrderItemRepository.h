#ifndef ORDERITEMREPOSITORY_H
#define ORDERITEMREPOSITORY_H

#include "../models/OrderItem.h"
#include <vector>

class OrderItemRepository {
public:
    OrderItem* getById(int id);
    std::vector<OrderItem*> getByOrderId(int orderId);
    bool insert(OrderItem* orderItem);
    bool update(OrderItem* orderItem);
    bool deleteById(int id);
};

#endif // ORDERITEMREPOSITORY_H

