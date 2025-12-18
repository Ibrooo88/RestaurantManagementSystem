#include "../../include/models/AccessScope.h"

AccessScope::AccessScope() : id(0) {}

AccessScope::AccessScope(int id, const std::string& name, const std::string& description)
    : id(id), name(name), description(description) {}

int AccessScope::getId() const { return id; }
std::string AccessScope::getName() const { return name; }
std::string AccessScope::getDescription() const { return description; }
std::string AccessScope::getCreatedAt() const { return createdAt; }

void AccessScope::setId(int id) { this->id = id; }
void AccessScope::setName(const std::string& name) { this->name = name; }
void AccessScope::setDescription(const std::string& description) { this->description = description; }
void AccessScope::setCreatedAt(const std::string& createdAt) { this->createdAt = createdAt; }

