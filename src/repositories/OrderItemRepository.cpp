#include "../../include/repositories/OrderItemRepository.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include "../../include/enums/OrderStatus.h"
#include <sqlite3.h>
#include <sstream>

OrderItem* OrderItemRepository::getById(int id) {
    // Implementation similar to UserRepository
    return nullptr;
}

std::vector<OrderItem*> OrderItemRepository::getByOrderId(int orderId) {
    std::vector<OrderItem*> items;
    if (!DatabaseConnection::getInstance().isConnected()) {
        return items;
    }
    
    std::ostringstream query;
    query << "SELECT id, order_id, menu_item_id, quantity, price, special_instructions, "
          << "status, created_at FROM order_items WHERE order_id = " << orderId << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return items;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        OrderItem* item = new OrderItem();
        item->setId(sqlite3_column_int(stmt, 0));
        item->setOrderId(sqlite3_column_int(stmt, 1));
        item->setMenuItemId(sqlite3_column_int(stmt, 2));
        item->setQuantity(sqlite3_column_int(stmt, 3));
        item->setPrice(sqlite3_column_double(stmt, 4));
        item->setSpecialInstructions(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        // Parse status...
        items.push_back(item);
    }
    
    sqlite3_finalize(stmt);
    return items;
}

bool OrderItemRepository::insert(OrderItem* orderItem) {
    if (!DatabaseConnection::getInstance().isConnected() || !orderItem) {
        return false;
    }
    
    std::ostringstream query;
    query << "INSERT INTO order_items (order_id, menu_item_id, quantity, price, special_instructions, status) "
          << "VALUES (" << orderItem->getOrderId() << ", " << orderItem->getMenuItemId() << ", "
          << orderItem->getQuantity() << ", " << orderItem->getPrice() << ", "
          << "'" << orderItem->getSpecialInstructions() << "', 'PENDING');";
    
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

bool OrderItemRepository::update(OrderItem* orderItem) {
    // Implementation
    return false;
}

bool OrderItemRepository::deleteById(int id) {
    // Implementation
    return false;
}

