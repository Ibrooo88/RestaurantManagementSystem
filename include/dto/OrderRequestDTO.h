#ifndef ORDERREQUESTDTO_H
#define ORDERREQUESTDTO_H

#include <string>
#include <vector>
#include <map>
#include "../enums/OrderType.h"

struct OrderItemRequest {
    int menuItemId;
    int quantity;
    std::string specialInstructions;
    
    OrderItemRequest() : menuItemId(0), quantity(1) {}
    OrderItemRequest(int id, int qty, const std::string& instructions = "")
        : menuItemId(id), quantity(qty), specialInstructions(instructions) {}
};

struct OrderRequestDTO {
    int tableId;
    OrderType orderType;
    std::string customerName;
    std::string customerPhone;
    std::vector<OrderItemRequest> items;
    
    OrderRequestDTO() : tableId(0), orderType(OrderType::DINE_IN) {}
    OrderRequestDTO(int table, OrderType type)
        : tableId(table), orderType(type) {}
};

#endif // ORDERREQUESTDTO_H

