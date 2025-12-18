#include "../../include/repositories/OrderRepository.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include "../../include/utils/TimeUtils.h"
#include "../../include/utils/SimulationMode.h"
#include "../../include/enums/OrderStatus.h"
#include "../../include/enums/OrderType.h"
#include <sqlite3.h>
#include <sstream>
#include <iomanip>
#include <ctime>

Order* OrderRepository::getById(int id) {
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto mockOrders = SimulationMode::getMockOrders();
        for (auto* order : mockOrders) {
            if (order->getId() == id) {
                return new Order(*order);
            }
        }
        return nullptr;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, order_number, table_id, order_type, status, total_amount, "
          << "chef_id, customer_name, customer_phone, created_at, updated_at "
          << "FROM orders WHERE id = " << id << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in OrderRepository::getById");
        return nullptr;
    }
    
    Order* order = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        order = new Order();
        order->setId(sqlite3_column_int(stmt, 0));
        order->setOrderNumber(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        order->setTableId(sqlite3_column_int(stmt, 2));
        
        std::string orderTypeStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        OrderType orderType = (orderTypeStr == "VIP") ? OrderType::VIP :
                             (orderTypeStr == "VEGAN") ? OrderType::VEGAN : OrderType::NORMAL;
        order->setOrderType(orderType);
        
        std::string statusStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        OrderStatus status = OrderStatus::PENDING;
        if (statusStr == "IN_PROGRESS") status = OrderStatus::IN_PROGRESS;
        else if (statusStr == "READY") status = OrderStatus::READY;
        else if (statusStr == "SERVED") status = OrderStatus::SERVED;
        else if (statusStr == "CANCELLED") status = OrderStatus::CANCELLED;
        else if (statusStr == "COMPLETED") status = OrderStatus::COMPLETED;
        order->setStatus(status);
        
        order->setTotalAmount(sqlite3_column_double(stmt, 5));
        order->setChefId(sqlite3_column_int(stmt, 6));
        order->setCustomerName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        order->setCustomerPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        order->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        order->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
    }
    
    sqlite3_finalize(stmt);
    return order;
}

Order* OrderRepository::getByOrderNumber(const std::string& orderNumber) {
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto mockOrders = SimulationMode::getMockOrders();
        for (auto* order : mockOrders) {
            if (order->getOrderNumber() == orderNumber) {
                return new Order(*order);
            }
        }
        return nullptr;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, order_number, table_id, order_type, status, total_amount, "
          << "chef_id, customer_name, customer_phone, created_at, updated_at "
          << "FROM orders WHERE order_number = '" << orderNumber << "';";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return nullptr;
    }
    
    Order* order = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        order = new Order();
        order->setId(sqlite3_column_int(stmt, 0));
        order->setOrderNumber(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        order->setTableId(sqlite3_column_int(stmt, 2));
        // Similar parsing as getById...
    }
    
    sqlite3_finalize(stmt);
    return order;
}

std::vector<Order*> OrderRepository::getAll() {
    std::vector<Order*> orders;
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto mockOrders = SimulationMode::getMockOrders();
        for (auto* order : mockOrders) {
            orders.push_back(new Order(*order));
        }
        return orders;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return orders;
    }
    
    std::string query = "SELECT id, order_number, table_id, order_type, status, total_amount, "
                       "chef_id, customer_name, customer_phone, created_at, updated_at FROM orders;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return orders;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Order* order = new Order();
        order->setId(sqlite3_column_int(stmt, 0));
        order->setOrderNumber(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        order->setTableId(sqlite3_column_int(stmt, 2));
        
        std::string orderTypeStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        OrderType orderType = (orderTypeStr == "VIP") ? OrderType::VIP :
                             (orderTypeStr == "VEGAN") ? OrderType::VEGAN : OrderType::NORMAL;
        order->setOrderType(orderType);
        
        std::string statusStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        OrderStatus status = OrderStatus::PENDING;
        if (statusStr == "IN_PROGRESS") status = OrderStatus::IN_PROGRESS;
        else if (statusStr == "READY") status = OrderStatus::READY;
        else if (statusStr == "SERVED") status = OrderStatus::SERVED;
        else if (statusStr == "CANCELLED") status = OrderStatus::CANCELLED;
        else if (statusStr == "COMPLETED") status = OrderStatus::COMPLETED;
        order->setStatus(status);
        
        order->setTotalAmount(sqlite3_column_double(stmt, 5));
        order->setChefId(sqlite3_column_int(stmt, 6));
        order->setCustomerName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        order->setCustomerPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        order->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        order->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
        orders.push_back(order);
    }
    
    sqlite3_finalize(stmt);
    return orders;
}

std::vector<Order*> OrderRepository::getByStatus(OrderStatus status) {
    std::vector<Order*> orders;
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto mockOrders = SimulationMode::getMockOrders();
        for (auto* order : mockOrders) {
            if (order->getStatus() == status) {
                orders.push_back(new Order(*order));
            }
        }
        return orders;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return orders;
    }
    
    std::string statusStr = "PENDING";
    if (status == OrderStatus::IN_PROGRESS) statusStr = "IN_PROGRESS";
    else if (status == OrderStatus::READY) statusStr = "READY";
    else if (status == OrderStatus::SERVED) statusStr = "SERVED";
    else if (status == OrderStatus::COMPLETED) statusStr = "COMPLETED";
    else if (status == OrderStatus::CANCELLED) statusStr = "CANCELLED";
    
    std::ostringstream query;
    query << "SELECT id, order_number, table_id, order_type, status, total_amount, "
          << "chef_id, customer_name, customer_phone, created_at, updated_at "
          << "FROM orders WHERE status = '" << statusStr << "';";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return orders;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Order* order = new Order();
        order->setId(sqlite3_column_int(stmt, 0));
        order->setOrderNumber(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        order->setTableId(sqlite3_column_int(stmt, 2));
        
        std::string orderTypeStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        OrderType orderType = (orderTypeStr == "VIP") ? OrderType::VIP :
                             (orderTypeStr == "VEGAN") ? OrderType::VEGAN : OrderType::NORMAL;
        order->setOrderType(orderType);
        order->setStatus(status);
        
        order->setTotalAmount(sqlite3_column_double(stmt, 5));
        order->setChefId(sqlite3_column_int(stmt, 6));
        order->setCustomerName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        order->setCustomerPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        order->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        order->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
        orders.push_back(order);
    }
    
    sqlite3_finalize(stmt);
    return orders;
}

std::vector<Order*> OrderRepository::getByTableId(int tableId) {
    std::vector<Order*> orders;
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto mockOrders = SimulationMode::getMockOrders();
        for (auto* order : mockOrders) {
            if (order->getTableId() == tableId) {
                orders.push_back(new Order(*order));
            }
        }
        return orders;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return orders;
    }
    
    std::ostringstream query;
    query << "SELECT id, order_number, table_id, order_type, status, total_amount, "
          << "chef_id, customer_name, customer_phone, created_at, updated_at "
          << "FROM orders WHERE table_id = " << tableId << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return orders;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Order* order = new Order();
        order->setId(sqlite3_column_int(stmt, 0));
        order->setOrderNumber(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        order->setTableId(sqlite3_column_int(stmt, 2));
        
        std::string orderTypeStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        OrderType orderType = (orderTypeStr == "VIP") ? OrderType::VIP :
                             (orderTypeStr == "VEGAN") ? OrderType::VEGAN : OrderType::NORMAL;
        order->setOrderType(orderType);
        
        std::string statusStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        OrderStatus orderStatus = OrderStatus::PENDING;
        if (statusStr == "IN_PROGRESS") orderStatus = OrderStatus::IN_PROGRESS;
        else if (statusStr == "READY") orderStatus = OrderStatus::READY;
        else if (statusStr == "SERVED") orderStatus = OrderStatus::SERVED;
        else if (statusStr == "COMPLETED") orderStatus = OrderStatus::COMPLETED;
        else if (statusStr == "CANCELLED") orderStatus = OrderStatus::CANCELLED;
        order->setStatus(orderStatus);
        
        order->setTotalAmount(sqlite3_column_double(stmt, 5));
        order->setChefId(sqlite3_column_int(stmt, 6));
        order->setCustomerName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        order->setCustomerPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        order->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        order->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
        orders.push_back(order);
    }
    
    sqlite3_finalize(stmt);
    return orders;
}

std::vector<Order*> OrderRepository::getByChefId(int chefId) {
    std::vector<Order*> orders;
    // Implementation
    return orders;
}

bool OrderRepository::insert(Order* order) {
    if (!order) {
        return false;
    }
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        return SimulationMode::insertMockOrder(order);
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::string orderTypeStr = (order->getOrderType() == OrderType::VIP) ? "VIP" :
                              (order->getOrderType() == OrderType::VEGAN) ? "VEGAN" : "NORMAL";
    std::string statusStr = "PENDING";
    if (order->getStatus() == OrderStatus::IN_PROGRESS) statusStr = "IN_PROGRESS";
    else if (order->getStatus() == OrderStatus::READY) statusStr = "READY";
    else if (order->getStatus() == OrderStatus::SERVED) statusStr = "SERVED";
    else if (order->getStatus() == OrderStatus::CANCELLED) statusStr = "CANCELLED";
    else if (order->getStatus() == OrderStatus::COMPLETED) statusStr = "COMPLETED";
    
    std::ostringstream query;
    query << "INSERT INTO orders (order_number, table_id, order_type, status, total_amount, "
          << "chef_id, customer_name, customer_phone) VALUES ("
          << "'" << order->getOrderNumber() << "', "
          << order->getTableId() << ", "
          << "'" << orderTypeStr << "', "
          << "'" << statusStr << "', "
          << order->getTotalAmount() << ", "
          << order->getChefId() << ", "
          << "'" << order->getCustomerName() << "', "
          << "'" << order->getCustomerPhone() << "');";
    
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

bool OrderRepository::update(Order* order) {
    if (!order) {
        return false;
    }
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        return SimulationMode::updateMockOrder(order->getId(), order);
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::string statusStr = "PENDING";
    if (order->getStatus() == OrderStatus::IN_PROGRESS) statusStr = "IN_PROGRESS";
    else if (order->getStatus() == OrderStatus::READY) statusStr = "READY";
    else if (order->getStatus() == OrderStatus::SERVED) statusStr = "SERVED";
    else if (order->getStatus() == OrderStatus::CANCELLED) statusStr = "CANCELLED";
    else if (order->getStatus() == OrderStatus::COMPLETED) statusStr = "COMPLETED";
    
    std::ostringstream query;
    query << "UPDATE orders SET "
          << "status = '" << statusStr << "', "
          << "total_amount = " << order->getTotalAmount() << ", "
          << "chef_id = " << order->getChefId() << ", "
          << "updated_at = CURRENT_TIMESTAMP "
          << "WHERE id = " << order->getId() << ";";
    
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

bool OrderRepository::deleteById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "DELETE FROM orders WHERE id = " << id << ";";
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

std::string OrderRepository::generateOrderNumber() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << "ORD-" << std::put_time(&tm, "%Y%m%d") << "-" 
        << std::setfill('0') << std::setw(4) << (now % 10000);
    return oss.str();
}

