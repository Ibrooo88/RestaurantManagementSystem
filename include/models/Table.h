#ifndef TABLE_H
#define TABLE_H

#include <string>
#include "../enums/TableStatus.h"

class Table {
private:
    int id;
    int tableNumber;
    int capacity;
    TableStatus status;
    std::string location;
    std::string createdAt;
    std::string updatedAt;

public:
    Table();
    Table(int id, int tableNumber, int capacity, TableStatus status = TableStatus::AVAILABLE,
          const std::string& location = "");
    
    int getId() const;
    int getTableNumber() const;
    int getCapacity() const;
    TableStatus getStatus() const;
    std::string getLocation() const;
    std::string getCreatedAt() const;
    std::string getUpdatedAt() const;
    
    void setId(int id);
    void setTableNumber(int tableNumber);
    void setCapacity(int capacity);
    void setStatus(TableStatus status);
    void setLocation(const std::string& location);
    void setCreatedAt(const std::string& createdAt);
    void setUpdatedAt(const std::string& updatedAt);
};

#endif // TABLE_H

