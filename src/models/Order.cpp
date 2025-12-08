#include "../../include/models/Order.h"

Order::Order() : id(0), tableId(0), orderType(OrderType::DINE_IN),
                status(OrderStatus::PENDING), totalAmount(0.0), chefId(0) {}

Order::Order(int id, const std::string& orderNumber, OrderType orderType,
             OrderStatus status, int tableId, double totalAmount)
    : id(id), orderNumber(orderNumber), tableId(tableId), orderType(orderType),
      status(status), totalAmount(totalAmount), chefId(0) {}

int Order::getId() const { return id; }
std::string Order::getOrderNumber() const { return orderNumber; }
int Order::getTableId() const { return tableId; }
OrderType Order::getOrderType() const { return orderType; }
OrderStatus Order::getStatus() const { return status; }
double Order::getTotalAmount() const { return totalAmount; }
int Order::getChefId() const { return chefId; }
std::string Order::getCustomerName() const { return customerName; }
std::string Order::getCustomerPhone() const { return customerPhone; }
std::string Order::getCreatedAt() const { return createdAt; }
std::string Order::getUpdatedAt() const { return updatedAt; }

void Order::setId(int id) { this->id = id; }
void Order::setOrderNumber(const std::string& orderNumber) { this->orderNumber = orderNumber; }
void Order::setTableId(int tableId) { this->tableId = tableId; }
void Order::setOrderType(OrderType orderType) { this->orderType = orderType; }
void Order::setStatus(OrderStatus status) { this->status = status; }
void Order::setTotalAmount(double totalAmount) { this->totalAmount = totalAmount; }
void Order::setChefId(int chefId) { this->chefId = chefId; }
void Order::setCustomerName(const std::string& customerName) { this->customerName = customerName; }
void Order::setCustomerPhone(const std::string& customerPhone) { this->customerPhone = customerPhone; }
void Order::setCreatedAt(const std::string& createdAt) { this->createdAt = createdAt; }
void Order::setUpdatedAt(const std::string& updatedAt) { this->updatedAt = updatedAt; }

