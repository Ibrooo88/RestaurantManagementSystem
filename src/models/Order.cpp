#include "../../include/models/Order.h"

Order::Order() 
    : id(0), tableId(0), orderType(OrderType::NORMAL), status(OrderStatus::PENDING),
      totalAmount(0.0), chefId(0), requestTimestep(0), assignmentTimestep(0),
      orderSize(0), money(0.0), waitingTime(0), serviceTime(0), finishTime(0),
      priority(0.0), extraMoney(0.0) {}

Order::Order(int id, const std::string& orderNumber, OrderType orderType,
             OrderStatus status, int tableId, double totalAmount)
    : id(id), orderNumber(orderNumber), tableId(tableId), orderType(orderType),
      status(status), totalAmount(totalAmount), chefId(0), requestTimestep(0),
      assignmentTimestep(0), orderSize(0), money(totalAmount), waitingTime(0),
      serviceTime(0), finishTime(0), priority(0.0), extraMoney(0.0) {}

Order::Order(int id, OrderType type, int requestTimestep, int orderSize, double money)
    : id(id), tableId(0), orderType(type), status(OrderStatus::PENDING),
      totalAmount(money), chefId(0), requestTimestep(requestTimestep),
      assignmentTimestep(0), orderSize(orderSize), money(money), waitingTime(0),
      serviceTime(0), finishTime(0), priority(0.0), extraMoney(0.0) {
    orderNumber = "ORD-" + std::to_string(id);
}

// Original getters
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

// Simulation getters
int Order::getRequestTimestep() const { return requestTimestep; }
int Order::getAssignmentTimestep() const { return assignmentTimestep; }
int Order::getOrderSize() const { return orderSize; }
double Order::getMoney() const { return money; }
int Order::getWaitingTime() const { return waitingTime; }
int Order::getServiceTime() const { return serviceTime; }
int Order::getFinishTime() const { return finishTime; }
double Order::getPriority() const { return priority; }
double Order::getExtraMoney() const { return extraMoney; }

// Original setters
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

// Simulation setters
void Order::setRequestTimestep(int rt) { requestTimestep = rt; }
void Order::setAssignmentTimestep(int gt) { assignmentTimestep = gt; }
void Order::setOrderSize(int size) { orderSize = size; }
void Order::setMoney(double m) { money = m; totalAmount = m; }
void Order::setWaitingTime(int wt) { waitingTime = wt; }
void Order::setServiceTime(int st) { serviceTime = st; }
void Order::setFinishTime(int ft) { finishTime = ft; }
void Order::setPriority(double p) { priority = p; }
void Order::setExtraMoney(double em) { extraMoney = em; }

// Simulation methods
void Order::calculatePriority(int currentTime, double alpha, double beta) {
    // Priority = (Money × α) / (OrderSize × β × (CurrentTime − RT + 1))
    double timeFactor = currentTime - requestTimestep + 1;
    if (timeFactor <= 0) timeFactor = 1;
    priority = (money * alpha) / (orderSize * beta * timeFactor);
}

void Order::promoteToVIP(double extra) {
    orderType = OrderType::VIP;
    extraMoney = extra;
    money += extra;
    totalAmount = money;
}

void Order::calculateWaitingTime() {
    waitingTime = assignmentTimestep - requestTimestep;
}

void Order::calculateFinishTime() {
    finishTime = requestTimestep + waitingTime + serviceTime;
}
