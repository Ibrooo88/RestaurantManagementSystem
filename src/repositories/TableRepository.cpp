#include "../../include/repositories/TableRepository.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include "../../include/utils/SimulationMode.h"
#include <sqlite3.h>
#include <sstream>

Table* TableRepository::getById(int id) {
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto tables = SimulationMode::getMockTables();
        for (auto* table : tables) {
            if (table->getId() == id) {
                return new Table(*table);
            }
        }
        return nullptr;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, table_number, capacity, status, location, created_at, updated_at "
          << "FROM tables WHERE id = " << id << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return nullptr;
    }
    
    Table* table = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        table = new Table();
        table->setId(sqlite3_column_int(stmt, 0));
        table->setTableNumber(sqlite3_column_int(stmt, 1));
        table->setCapacity(sqlite3_column_int(stmt, 2));
        
        std::string statusStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        TableStatus status = TableStatus::AVAILABLE;
        if (statusStr == "OCCUPIED") status = TableStatus::OCCUPIED;
        else if (statusStr == "RESERVED") status = TableStatus::RESERVED;
        else if (statusStr == "CLEANING") status = TableStatus::CLEANING;
        else if (statusStr == "OUT_OF_SERVICE") status = TableStatus::OUT_OF_SERVICE;
        table->setStatus(status);
        
        table->setLocation(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        table->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        table->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
    }
    
    sqlite3_finalize(stmt);
    return table;
}

Table* TableRepository::getByTableNumber(int tableNumber) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, table_number, capacity, status, location, created_at, updated_at "
          << "FROM tables WHERE table_number = " << tableNumber << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return nullptr;
    }
    
    Table* table = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        table = new Table();
        table->setId(sqlite3_column_int(stmt, 0));
        table->setTableNumber(sqlite3_column_int(stmt, 1));
        table->setCapacity(sqlite3_column_int(stmt, 2));
        // Similar parsing as getById...
    }
    
    sqlite3_finalize(stmt);
    return table;
}

std::vector<Table*> TableRepository::getAll() {
    std::vector<Table*> tables;
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto mockTables = SimulationMode::getMockTables();
        for (auto* table : mockTables) {
            tables.push_back(new Table(*table));
        }
        return tables;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return tables;
    }
    
    std::string query = "SELECT id, table_number, capacity, status, location, created_at, updated_at FROM tables;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return tables;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Table* table = new Table();
        table->setId(sqlite3_column_int(stmt, 0));
        table->setTableNumber(sqlite3_column_int(stmt, 1));
        table->setCapacity(sqlite3_column_int(stmt, 2));
        
        std::string statusStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        TableStatus status = TableStatus::AVAILABLE;
        if (statusStr == "OCCUPIED") status = TableStatus::OCCUPIED;
        else if (statusStr == "RESERVED") status = TableStatus::RESERVED;
        else if (statusStr == "CLEANING") status = TableStatus::CLEANING;
        else if (statusStr == "OUT_OF_SERVICE") status = TableStatus::OUT_OF_SERVICE;
        table->setStatus(status);
        
        table->setLocation(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        table->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        table->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        tables.push_back(table);
    }
    
    sqlite3_finalize(stmt);
    return tables;
}

std::vector<Table*> TableRepository::getByStatus(TableStatus status) {
    std::vector<Table*> tables;
    // Implementation similar to getAll with WHERE status = ...
    return tables;
}

std::vector<Table*> TableRepository::getAvailable() {
    return getByStatus(TableStatus::AVAILABLE);
}

bool TableRepository::insert(Table* table) {
    if (!table) {
        return false;
    }
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        return SimulationMode::insertMockTable(table);
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::string statusStr = "AVAILABLE";
    if (table->getStatus() == TableStatus::OCCUPIED) statusStr = "OCCUPIED";
    else if (table->getStatus() == TableStatus::RESERVED) statusStr = "RESERVED";
    else if (table->getStatus() == TableStatus::CLEANING) statusStr = "CLEANING";
    else if (table->getStatus() == TableStatus::OUT_OF_SERVICE) statusStr = "OUT_OF_SERVICE";
    
    std::ostringstream query;
    query << "INSERT INTO tables (table_number, capacity, status, location) VALUES ("
          << table->getTableNumber() << ", "
          << table->getCapacity() << ", "
          << "'" << statusStr << "', "
          << "'" << table->getLocation() << "');";
    
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

bool TableRepository::update(Table* table) {
    if (!table) {
        return false;
    }
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        return SimulationMode::updateMockTable(table->getId(), table);
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::string statusStr = "AVAILABLE";
    if (table->getStatus() == TableStatus::OCCUPIED) statusStr = "OCCUPIED";
    else if (table->getStatus() == TableStatus::RESERVED) statusStr = "RESERVED";
    else if (table->getStatus() == TableStatus::CLEANING) statusStr = "CLEANING";
    else if (table->getStatus() == TableStatus::OUT_OF_SERVICE) statusStr = "OUT_OF_SERVICE";
    
    std::ostringstream query;
    query << "UPDATE tables SET "
          << "table_number = " << table->getTableNumber() << ", "
          << "capacity = " << table->getCapacity() << ", "
          << "status = '" << statusStr << "', "
          << "location = '" << table->getLocation() << "', "
          << "updated_at = CURRENT_TIMESTAMP "
          << "WHERE id = " << table->getId() << ";";
    
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

bool TableRepository::deleteById(int id) {
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        return SimulationMode::deleteMockTable(id);
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "DELETE FROM tables WHERE id = " << id << ";";
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

