#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H

#include <string>

class OrderQueue {
private:
    int id;
    int orderId;
    int priority;
    std::string estimatedCompletionTime;
    std::string createdAt;

public:
    OrderQueue();
    OrderQueue(int id, int orderId, int priority = 0,
               const std::string& estimatedCompletionTime = "");
    
    int getId() const;
    int getOrderId() const;
    int getPriority() const;
    std::string getEstimatedCompletionTime() const;
    std::string getCreatedAt() const;
    
    void setId(int id);
    void setOrderId(int orderId);
    void setPriority(int priority);
    void setEstimatedCompletionTime(const std::string& estimatedCompletionTime);
    void setCreatedAt(const std::string& createdAt);
};

#endif // ORDERQUEUE_H

