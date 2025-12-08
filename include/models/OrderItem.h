#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <string>
#include "../enums/OrderStatus.h"

class OrderItem {
private:
    int id;
    int orderId;
    int menuItemId;
    int quantity;
    double price;
    std::string specialInstructions;
    OrderStatus status;
    std::string createdAt;

public:
    OrderItem();
    OrderItem(int id, int orderId, int menuItemId, int quantity, double price,
              OrderStatus status = OrderStatus::PENDING);
    
    int getId() const;
    int getOrderId() const;
    int getMenuItemId() const;
    int getQuantity() const;
    double getPrice() const;
    std::string getSpecialInstructions() const;
    OrderStatus getStatus() const;
    std::string getCreatedAt() const;
    
    void setId(int id);
    void setOrderId(int orderId);
    void setMenuItemId(int menuItemId);
    void setQuantity(int quantity);
    void setPrice(double price);
    void setSpecialInstructions(const std::string& specialInstructions);
    void setStatus(OrderStatus status);
    void setCreatedAt(const std::string& createdAt);
};

#endif // ORDERITEM_H

