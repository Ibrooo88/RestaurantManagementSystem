#ifndef CHEF_H
#define CHEF_H

#include <string>
#include "../enums/ChefType.h"
#include "../enums/ChefStatus.h"
#include "../enums/OrderType.h"

class Chef {
private:
    int id;
    int userId;
    ChefType chefType;
    ChefStatus status;
    int skillLevel;
    int currentWorkload;
    std::string specialization;
    std::string createdAt;
    
    // Simulation fields
    int speed;                  // Number of dishes chef can prepare per timestep
    int breakDuration;          // Rest period after preparing certain orders
    int ordersBeforeBreak;      // Number of consecutive orders before a break
    int ordersCompleted;        // Orders completed since last break
    int currentOrderId;         // ID of order currently being prepared
    int remainingBreakTime;     // Remaining timesteps in break
    int orderFinishTime;        // Timestep when current order will be done

public:
    Chef();
    Chef(int id, int userId, ChefType chefType, ChefStatus status = ChefStatus::AVAILABLE,
         int skillLevel = 1, int currentWorkload = 0, const std::string& specialization = "");
    
    // Simulation constructor
    Chef(int id, ChefType type, int speed, int ordersBeforeBreak, int breakDuration);
    
    int getId() const;
    int getUserId() const;
    ChefType getChefType() const;
    ChefStatus getStatus() const;
    int getSkillLevel() const;
    int getCurrentWorkload() const;
    std::string getSpecialization() const;
    std::string getCreatedAt() const;
    
    // Simulation getters
    int getSpeed() const;
    int getBreakDuration() const;
    int getOrdersBeforeBreak() const;
    int getOrdersCompleted() const;
    int getCurrentOrderId() const;
    int getRemainingBreakTime() const;
    int getOrderFinishTime() const;
    
    void setId(int id);
    void setUserId(int userId);
    void setChefType(ChefType chefType);
    void setStatus(ChefStatus status);
    void setSkillLevel(int skillLevel);
    void setCurrentWorkload(int currentWorkload);
    void setSpecialization(const std::string& specialization);
    void setCreatedAt(const std::string& createdAt);
    
    // Simulation setters
    void setSpeed(int speed);
    void setBreakDuration(int duration);
    void setOrdersBeforeBreak(int orders);
    void setOrdersCompleted(int completed);
    void setCurrentOrderId(int orderId);
    void setRemainingBreakTime(int time);
    void setOrderFinishTime(int time);
    
    // Simulation methods
    bool isAvailable() const;
    bool canHandleOrder(OrderType orderType) const;
    int calculateServiceTime(int orderSize) const;
    void assignOrder(int orderId, int finishTime);
    void completeOrder();
    void startBreak();
    void updateBreak();
};

#endif // CHEF_H
