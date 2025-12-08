#include "../../include/models/Table.h"

Table::Table() : id(0), tableNumber(0), capacity(0), status(TableStatus::AVAILABLE) {}

Table::Table(int id, int tableNumber, int capacity, TableStatus status, const std::string& location)
    : id(id), tableNumber(tableNumber), capacity(capacity), status(status), location(location) {}

int Table::getId() const { return id; }
int Table::getTableNumber() const { return tableNumber; }
int Table::getCapacity() const { return capacity; }
TableStatus Table::getStatus() const { return status; }
std::string Table::getLocation() const { return location; }
std::string Table::getCreatedAt() const { return createdAt; }
std::string Table::getUpdatedAt() const { return updatedAt; }

void Table::setId(int id) { this->id = id; }
void Table::setTableNumber(int tableNumber) { this->tableNumber = tableNumber; }
void Table::setCapacity(int capacity) { this->capacity = capacity; }
void Table::setStatus(TableStatus status) { this->status = status; }
void Table::setLocation(const std::string& location) { this->location = location; }
void Table::setCreatedAt(const std::string& createdAt) { this->createdAt = createdAt; }
void Table::setUpdatedAt(const std::string& updatedAt) { this->updatedAt = updatedAt; }

