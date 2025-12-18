#ifndef ORDER_H
#define ORDER_H

#include <string>
#include "../enums/OrderType.h"
#include "../enums/OrderStatus.h"

class Order {
private:
    int id;
    std::string orderNumber;
    int tableId;
    OrderType orderType;
    OrderStatus status;
    double totalAmount;
    int chefId;
    std::string customerName;
    std::string customerPhone;
    std::string createdAt;
    std::string updatedAt;
    
    // Simulation fields
    int requestTimestep;      // RT: Time when order was received
    int assignmentTimestep;   // GT: Time when chef starts cooking
    int orderSize;            // Number of dishes in the order
    double money;             // Order price
    int waitingTime;          // WT = GT - RT
    int serviceTime;          // ST: Cooking duration
    int finishTime;           // FT = RT + WT + ST
    double priority;          // Priority value for VIP queue
    double extraMoney;        // Extra money paid for promotion

public:
    Order();
    Order(int id, const std::string& orderNumber, OrderType orderType,
          OrderStatus status = OrderStatus::PENDING, int tableId = 0, double totalAmount = 0.0);
    
    // Simulation constructor
    Order(int id, OrderType type, int requestTimestep, int orderSize, double money);
    
    int getId() const;
    std::string getOrderNumber() const;
    int getTableId() const;
    OrderType getOrderType() const;
    OrderStatus getStatus() const;
    double getTotalAmount() const;
    int getChefId() const;
    std::string getCustomerName() const;
    std::string getCustomerPhone() const;
    std::string getCreatedAt() const;
    std::string getUpdatedAt() const;
    
    // Simulation getters
    int getRequestTimestep() const;
    int getAssignmentTimestep() const;
    int getOrderSize() const;
    double getMoney() const;
    int getWaitingTime() const;
    int getServiceTime() const;
    int getFinishTime() const;
    double getPriority() const;
    double getExtraMoney() const;
    
    void setId(int id);
    void setOrderNumber(const std::string& orderNumber);
    void setTableId(int tableId);
    void setOrderType(OrderType orderType);
    void setStatus(OrderStatus status);
    void setTotalAmount(double totalAmount);
    void setChefId(int chefId);
    void setCustomerName(const std::string& customerName);
    void setCustomerPhone(const std::string& customerPhone);
    void setCreatedAt(const std::string& createdAt);
    void setUpdatedAt(const std::string& updatedAt);
    
    // Simulation setters
    void setRequestTimestep(int rt);
    void setAssignmentTimestep(int gt);
    void setOrderSize(int size);
    void setMoney(double money);
    void setWaitingTime(int wt);
    void setServiceTime(int st);
    void setFinishTime(int ft);
    void setPriority(double priority);
    void setExtraMoney(double extraMoney);
    
    // Simulation methods
    void calculatePriority(int currentTime, double alpha = 1.0, double beta = 1.0);
    void promoteToVIP(double extraMoney);
    void calculateWaitingTime();
    void calculateFinishTime();
};

#endif // ORDER_H
