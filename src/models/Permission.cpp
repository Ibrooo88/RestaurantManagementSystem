#include "../../include/models/Permission.h"

Permission::Permission() : id(0) {}

Permission::Permission(int id, const std::string& name, const std::string& description)
    : id(id), name(name), description(description) {}

int Permission::getId() const { return id; }
std::string Permission::getName() const { return name; }
std::string Permission::getDescription() const { return description; }
std::string Permission::getCreatedAt() const { return createdAt; }

void Permission::setId(int id) { this->id = id; }
void Permission::setName(const std::string& name) { this->name = name; }
void Permission::setDescription(const std::string& description) { this->description = description; }
void Permission::setCreatedAt(const std::string& createdAt) { this->createdAt = createdAt; }

