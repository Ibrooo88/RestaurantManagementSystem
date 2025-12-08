#ifndef TABLEREPOSITORY_H
#define TABLEREPOSITORY_H

#include "../models/Table.h"
#include "../enums/TableStatus.h"
#include <vector>

class TableRepository {
public:
    Table* getById(int id);
    Table* getByTableNumber(int tableNumber);
    std::vector<Table*> getAll();
    std::vector<Table*> getByStatus(TableStatus status);
    std::vector<Table*> getAvailable();
    bool insert(Table* table);
    bool update(Table* table);
    bool deleteById(int id);
};

#endif // TABLEREPOSITORY_H

