#include "../../include/services/TableService.h"
#include "../../include/repositories/TableRepository.h"
#include "../../include/utils/Logger.h"
#include "../../include/enums/TableStatus.h"

Table* TableService::createTable(int tableNumber, int capacity,
                                 const std::string& location,
                                 TableStatus status) {
    if (tableNumber <= 0 || capacity <= 0) {
        Logger::getInstance().warning("Invalid table data");
        return nullptr;
    }
    
    // Check if table number already exists
    TableRepository tableRepo;
    Table* existingTable = tableRepo.getByTableNumber(tableNumber);
    if (existingTable) {
        Logger::getInstance().warning("Table number already exists: " + std::to_string(tableNumber));
        delete existingTable;
        return nullptr;
    }
    
    Table* table = new Table();
    table->setTableNumber(tableNumber);
    table->setCapacity(capacity);
    table->setLocation(location);
    table->setStatus(status);
    
    if (tableRepo.insert(table)) {
        Logger::getInstance().info("Table created: " + std::to_string(tableNumber));
        return table;
    }
    
    delete table;
    return nullptr;
}

bool TableService::updateTable(int tableId, int tableNumber, int capacity,
                               const std::string& location, TableStatus status) {
    TableRepository tableRepo;
    Table* table = tableRepo.getById(tableId);
    if (!table) {
        return false;
    }
    
    table->setTableNumber(tableNumber);
    table->setCapacity(capacity);
    table->setLocation(location);
    table->setStatus(status);
    
    bool result = tableRepo.update(table);
    if (result) {
        Logger::getInstance().info("Table updated: " + std::to_string(tableId));
    }
    delete table;
    return result;
}

bool TableService::deleteTable(int tableId) {
    TableRepository tableRepo;
    bool result = tableRepo.deleteById(tableId);
    if (result) {
        Logger::getInstance().info("Table deleted: " + std::to_string(tableId));
    }
    return result;
}

std::vector<Table*> TableService::getAvailableTables() {
    TableRepository tableRepo;
    return tableRepo.getAvailable();
}

std::vector<Table*> TableService::getOccupiedTables() {
    TableRepository tableRepo;
    return tableRepo.getByStatus(TableStatus::OCCUPIED);
}

std::vector<Table*> TableService::getAllTables() {
    TableRepository tableRepo;
    return tableRepo.getAll();
}

Table* TableService::getTableById(int tableId) {
    TableRepository tableRepo;
    return tableRepo.getById(tableId);
}

bool TableService::setTableStatus(int tableId, TableStatus status) {
    TableRepository tableRepo;
    Table* table = tableRepo.getById(tableId);
    if (!table) {
        return false;
    }
    
    table->setStatus(status);
    bool result = tableRepo.update(table);
    delete table;
    return result;
}

bool TableService::isTableAvailable(int tableId) {
    Table* table = getTableById(tableId);
    if (!table) {
        return false;
    }
    
    bool available = (table->getStatus() == TableStatus::AVAILABLE);
    delete table;
    return available;
}

