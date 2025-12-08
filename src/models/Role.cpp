#include "../../include/models/Role.h"

Role::Role() : id(0) {}
Role::Role(int id, const std::string& name, const std::string& description)
    : id(id), name(name), description(description) {}

int Role::getId() const { return id; }
std::string Role::getName() const { return name; }
std::string Role::getDescription() const { return description; }
std::string Role::getCreatedAt() const { return createdAt; }

void Role::setId(int id) { this->id = id; }
void Role::setName(const std::string& name) { this->name = name; }
void Role::setDescription(const std::string& description) { this->description = description; }
void Role::setCreatedAt(const std::string& createdAt) { this->createdAt = createdAt; }

