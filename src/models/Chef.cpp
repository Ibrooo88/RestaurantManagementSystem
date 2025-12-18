#include "../../include/models/Chef.h"

Chef::Chef() 
    : id(0), userId(0), chefType(ChefType::NORMAL_CHEF), status(ChefStatus::AVAILABLE),
      skillLevel(1), currentWorkload(0), speed(1), breakDuration(0),
      ordersBeforeBreak(5), ordersCompleted(0), currentOrderId(0),
      remainingBreakTime(0), orderFinishTime(0) {}

Chef::Chef(int id, int userId, ChefType chefType, ChefStatus status,
           int skillLevel, int currentWorkload, const std::string& specialization)
    : id(id), userId(userId), chefType(chefType), status(status),
      skillLevel(skillLevel), currentWorkload(currentWorkload),
      specialization(specialization), speed(skillLevel), breakDuration(3),
      ordersBeforeBreak(5), ordersCompleted(0), currentOrderId(0),
      remainingBreakTime(0), orderFinishTime(0) {}

Chef::Chef(int id, ChefType type, int speed, int ordersBeforeBreak, int breakDuration)
    : id(id), userId(0), chefType(type), status(ChefStatus::AVAILABLE),
      skillLevel(speed), currentWorkload(0), speed(speed),
      breakDuration(breakDuration), ordersBeforeBreak(ordersBeforeBreak),
      ordersCompleted(0), currentOrderId(0), remainingBreakTime(0), orderFinishTime(0) {}

// Original getters
int Chef::getId() const { return id; }
int Chef::getUserId() const { return userId; }
ChefType Chef::getChefType() const { return chefType; }
ChefStatus Chef::getStatus() const { return status; }
int Chef::getSkillLevel() const { return skillLevel; }
int Chef::getCurrentWorkload() const { return currentWorkload; }
std::string Chef::getSpecialization() const { return specialization; }
std::string Chef::getCreatedAt() const { return createdAt; }

// Simulation getters
int Chef::getSpeed() const { return speed; }
int Chef::getBreakDuration() const { return breakDuration; }
int Chef::getOrdersBeforeBreak() const { return ordersBeforeBreak; }
int Chef::getOrdersCompleted() const { return ordersCompleted; }
int Chef::getCurrentOrderId() const { return currentOrderId; }
int Chef::getRemainingBreakTime() const { return remainingBreakTime; }
int Chef::getOrderFinishTime() const { return orderFinishTime; }

// Original setters
void Chef::setId(int id) { this->id = id; }
void Chef::setUserId(int userId) { this->userId = userId; }
void Chef::setChefType(ChefType chefType) { this->chefType = chefType; }
void Chef::setStatus(ChefStatus status) { this->status = status; }
void Chef::setSkillLevel(int skillLevel) { this->skillLevel = skillLevel; }
void Chef::setCurrentWorkload(int currentWorkload) { this->currentWorkload = currentWorkload; }
void Chef::setSpecialization(const std::string& specialization) { this->specialization = specialization; }
void Chef::setCreatedAt(const std::string& createdAt) { this->createdAt = createdAt; }

// Simulation setters
void Chef::setSpeed(int s) { speed = s; }
void Chef::setBreakDuration(int duration) { breakDuration = duration; }
void Chef::setOrdersBeforeBreak(int orders) { ordersBeforeBreak = orders; }
void Chef::setOrdersCompleted(int completed) { ordersCompleted = completed; }
void Chef::setCurrentOrderId(int orderId) { currentOrderId = orderId; }
void Chef::setRemainingBreakTime(int time) { remainingBreakTime = time; }
void Chef::setOrderFinishTime(int time) { orderFinishTime = time; }

// Simulation methods
bool Chef::isAvailable() const {
    return status == ChefStatus::AVAILABLE && remainingBreakTime <= 0;
}

bool Chef::canHandleOrder(OrderType orderType) const {
    switch (chefType) {
        case ChefType::VIP_CHEF:
            return true;  // VIP chef can handle any order
        case ChefType::VEGAN_CHEF:
            return orderType == OrderType::VEGAN;
        case ChefType::NORMAL_CHEF:
            return orderType == OrderType::NORMAL || orderType == OrderType::VIP;
    }
    return false;
}

int Chef::calculateServiceTime(int orderSize) const {
    if (speed <= 0) return orderSize;
    return (orderSize + speed - 1) / speed;  // Ceiling division
}

void Chef::assignOrder(int orderId, int finishTime) {
    currentOrderId = orderId;
    orderFinishTime = finishTime;
    status = ChefStatus::BUSY;
    currentWorkload++;
}

void Chef::completeOrder() {
    currentOrderId = 0;
    orderFinishTime = 0;
    ordersCompleted++;
    currentWorkload--;
    status = ChefStatus::AVAILABLE;
}

void Chef::startBreak() {
    remainingBreakTime = breakDuration;
    status = ChefStatus::ON_BREAK;
}

void Chef::updateBreak() {
    if (remainingBreakTime > 0) {
        remainingBreakTime--;
        if (remainingBreakTime <= 0) {
            status = ChefStatus::AVAILABLE;
        }
    }
}
