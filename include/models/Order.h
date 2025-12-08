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

public:
    Order();
    Order(int id, const std::string& orderNumber, OrderType orderType,
          OrderStatus status = OrderStatus::PENDING, int tableId = 0, double totalAmount = 0.0);
    
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
};

#endif // ORDER_H

