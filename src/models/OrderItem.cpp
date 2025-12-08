#include "../../include/models/OrderItem.h"

OrderItem::OrderItem() : id(0), orderId(0), menuItemId(0), quantity(0),
                        price(0.0), status(OrderStatus::PENDING) {}

OrderItem::OrderItem(int id, int orderId, int menuItemId, int quantity, double price, OrderStatus status)
    : id(id), orderId(orderId), menuItemId(menuItemId), quantity(quantity),
      price(price), status(status) {}

int OrderItem::getId() const { return id; }
int OrderItem::getOrderId() const { return orderId; }
int OrderItem::getMenuItemId() const { return menuItemId; }
int OrderItem::getQuantity() const { return quantity; }
double OrderItem::getPrice() const { return price; }
std::string OrderItem::getSpecialInstructions() const { return specialInstructions; }
OrderStatus OrderItem::getStatus() const { return status; }
std::string OrderItem::getCreatedAt() const { return createdAt; }

void OrderItem::setId(int id) { this->id = id; }
void OrderItem::setOrderId(int orderId) { this->orderId = orderId; }
void OrderItem::setMenuItemId(int menuItemId) { this->menuItemId = menuItemId; }
void OrderItem::setQuantity(int quantity) { this->quantity = quantity; }
void OrderItem::setPrice(double price) { this->price = price; }
void OrderItem::setSpecialInstructions(const std::string& specialInstructions) { this->specialInstructions = specialInstructions; }
void OrderItem::setStatus(OrderStatus status) { this->status = status; }
void OrderItem::setCreatedAt(const std::string& createdAt) { this->createdAt = createdAt; }

