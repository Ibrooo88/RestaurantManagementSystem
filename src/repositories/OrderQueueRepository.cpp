#include "../../include/repositories/OrderQueueRepository.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include <sqlite3.h>
#include <sstream>

OrderQueue* OrderQueueRepository::getById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, order_id, priority, estimated_completion_time, created_at "
          << "FROM order_queue WHERE id = " << id << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in OrderQueueRepository::getById");
        return nullptr;
    }
    
    OrderQueue* orderQueue = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        orderQueue = new OrderQueue();
        orderQueue->setId(sqlite3_column_int(stmt, 0));
        orderQueue->setOrderId(sqlite3_column_int(stmt, 1));
        orderQueue->setPriority(sqlite3_column_int(stmt, 2));
        orderQueue->setEstimatedCompletionTime(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        orderQueue->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
    }
    
    sqlite3_finalize(stmt);
    return orderQueue;
}

OrderQueue* OrderQueueRepository::getByOrderId(int orderId) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, order_id, priority, estimated_completion_time, created_at "
          << "FROM order_queue WHERE order_id = " << orderId << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in OrderQueueRepository::getByOrderId");
        return nullptr;
    }
    
    OrderQueue* orderQueue = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        orderQueue = new OrderQueue();
        orderQueue->setId(sqlite3_column_int(stmt, 0));
        orderQueue->setOrderId(sqlite3_column_int(stmt, 1));
        orderQueue->setPriority(sqlite3_column_int(stmt, 2));
        orderQueue->setEstimatedCompletionTime(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        orderQueue->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
    }
    
    sqlite3_finalize(stmt);
    return orderQueue;
}

std::vector<OrderQueue*> OrderQueueRepository::getAll() {
    std::vector<OrderQueue*> orderQueues;
    if (!DatabaseConnection::getInstance().isConnected()) {
        return orderQueues;
    }
    
    std::string query = "SELECT id, order_id, priority, estimated_completion_time, created_at "
                       "FROM order_queue ORDER BY priority DESC, created_at ASC;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in OrderQueueRepository::getAll");
        return orderQueues;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        OrderQueue* orderQueue = new OrderQueue();
        orderQueue->setId(sqlite3_column_int(stmt, 0));
        orderQueue->setOrderId(sqlite3_column_int(stmt, 1));
        orderQueue->setPriority(sqlite3_column_int(stmt, 2));
        orderQueue->setEstimatedCompletionTime(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        orderQueue->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        orderQueues.push_back(orderQueue);
    }
    
    sqlite3_finalize(stmt);
    return orderQueues;
}

std::vector<OrderQueue*> OrderQueueRepository::getByPriority(int priority) {
    std::vector<OrderQueue*> orderQueues;
    if (!DatabaseConnection::getInstance().isConnected()) {
        return orderQueues;
    }
    
    std::ostringstream query;
    query << "SELECT id, order_id, priority, estimated_completion_time, created_at "
          << "FROM order_queue WHERE priority = " << priority << " "
          << "ORDER BY created_at ASC;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in OrderQueueRepository::getByPriority");
        return orderQueues;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        OrderQueue* orderQueue = new OrderQueue();
        orderQueue->setId(sqlite3_column_int(stmt, 0));
        orderQueue->setOrderId(sqlite3_column_int(stmt, 1));
        orderQueue->setPriority(sqlite3_column_int(stmt, 2));
        orderQueue->setEstimatedCompletionTime(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        orderQueue->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        orderQueues.push_back(orderQueue);
    }
    
    sqlite3_finalize(stmt);
    return orderQueues;
}

std::vector<OrderQueue*> OrderQueueRepository::getPending() {
    return getAll();
}

bool OrderQueueRepository::insert(OrderQueue* orderQueue) {
    if (!DatabaseConnection::getInstance().isConnected() || !orderQueue) {
        return false;
    }
    
    std::ostringstream query;
    query << "INSERT INTO order_queue (order_id, priority, estimated_completion_time) VALUES ("
          << orderQueue->getOrderId() << ", "
          << orderQueue->getPriority() << ", "
          << "'" << orderQueue->getEstimatedCompletionTime() << "');";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("OrderQueue inserted for order: " + std::to_string(orderQueue->getOrderId()));
    }
    return result;
}

bool OrderQueueRepository::update(OrderQueue* orderQueue) {
    if (!DatabaseConnection::getInstance().isConnected() || !orderQueue) {
        return false;
    }
    
    std::ostringstream query;
    query << "UPDATE order_queue SET "
          << "priority = " << orderQueue->getPriority() << ", "
          << "estimated_completion_time = '" << orderQueue->getEstimatedCompletionTime() << "' "
          << "WHERE id = " << orderQueue->getId() << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("OrderQueue updated: " + std::to_string(orderQueue->getId()));
    }
    return result;
}

bool OrderQueueRepository::deleteById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "DELETE FROM order_queue WHERE id = " << id << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("OrderQueue deleted: " + std::to_string(id));
    }
    return result;
}

bool OrderQueueRepository::deleteByOrderId(int orderId) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "DELETE FROM order_queue WHERE order_id = " << orderId << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("OrderQueue deleted for order: " + std::to_string(orderId));
    }
    return result;
}

