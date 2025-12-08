#ifndef ORDERQUEUEREPOSITORY_H
#define ORDERQUEUEREPOSITORY_H

#include "../models/OrderQueue.h"
#include <vector>

class OrderQueueRepository {
public:
    OrderQueue* getById(int id);
    OrderQueue* getByOrderId(int orderId);
    std::vector<OrderQueue*> getAll();
    std::vector<OrderQueue*> getByPriority(int priority);
    std::vector<OrderQueue*> getPending();
    bool insert(OrderQueue* orderQueue);
    bool update(OrderQueue* orderQueue);
    bool deleteById(int id);
    bool deleteByOrderId(int orderId);
};

#endif // ORDERQUEUEREPOSITORY_H

