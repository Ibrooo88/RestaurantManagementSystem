#ifndef TABLESERVICE_H
#define TABLESERVICE_H

#include "../models/Table.h"
#include "../enums/TableStatus.h"
#include <vector>

class TableService {
public:
    static Table* createTable(int tableNumber, int capacity, 
                             const std::string& location = "",
                             TableStatus status = TableStatus::AVAILABLE);
    static bool updateTable(int tableId, int tableNumber, int capacity,
                           const std::string& location, TableStatus status);
    static bool deleteTable(int tableId);
    static std::vector<Table*> getAvailableTables();
    static std::vector<Table*> getOccupiedTables();
    static std::vector<Table*> getAllTables();
    static Table* getTableById(int tableId);
    static bool setTableStatus(int tableId, TableStatus status);
    static bool isTableAvailable(int tableId);
};

#endif // TABLESERVICE_H

