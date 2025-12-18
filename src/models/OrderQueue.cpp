#include "../../include/models/OrderQueue.h"

OrderQueue::OrderQueue() : id(0), orderId(0), priority(0) {}

OrderQueue::OrderQueue(int id, int orderId, int priority, const std::string& estimatedCompletionTime)
    : id(id), orderId(orderId), priority(priority), estimatedCompletionTime(estimatedCompletionTime) {}

int OrderQueue::getId() const { return id; }
int OrderQueue::getOrderId() const { return orderId; }
int OrderQueue::getPriority() const { return priority; }
std::string OrderQueue::getEstimatedCompletionTime() const { return estimatedCompletionTime; }
std::string OrderQueue::getCreatedAt() const { return createdAt; }

void OrderQueue::setId(int id) { this->id = id; }
void OrderQueue::setOrderId(int orderId) { this->orderId = orderId; }
void OrderQueue::setPriority(int priority) { this->priority = priority; }
void OrderQueue::setEstimatedCompletionTime(const std::string& estimatedCompletionTime) { this->estimatedCompletionTime = estimatedCompletionTime; }
void OrderQueue::setCreatedAt(const std::string& createdAt) { this->createdAt = createdAt; }

