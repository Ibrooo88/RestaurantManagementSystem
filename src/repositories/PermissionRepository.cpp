#include "../../include/repositories/PermissionRepository.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include <sqlite3.h>
#include <sstream>

Permission* PermissionRepository::getById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, name, description, created_at "
          << "FROM permissions WHERE id = " << id << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in PermissionRepository::getById");
        return nullptr;
    }
    
    Permission* permission = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        permission = new Permission();
        permission->setId(sqlite3_column_int(stmt, 0));
        permission->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        permission->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        permission->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
    }
    
    sqlite3_finalize(stmt);
    return permission;
}

Permission* PermissionRepository::getByName(const std::string& name) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, name, description, created_at "
          << "FROM permissions WHERE name = '" << name << "';";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in PermissionRepository::getByName");
        return nullptr;
    }
    
    Permission* permission = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        permission = new Permission();
        permission->setId(sqlite3_column_int(stmt, 0));
        permission->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        permission->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        permission->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
    }
    
    sqlite3_finalize(stmt);
    return permission;
}

std::vector<Permission*> PermissionRepository::getAll() {
    std::vector<Permission*> permissions;
    if (!DatabaseConnection::getInstance().isConnected()) {
        return permissions;
    }
    
    std::string query = "SELECT id, name, description, created_at FROM permissions;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in PermissionRepository::getAll");
        return permissions;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Permission* permission = new Permission();
        permission->setId(sqlite3_column_int(stmt, 0));
        permission->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        permission->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        permission->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        permissions.push_back(permission);
    }
    
    sqlite3_finalize(stmt);
    return permissions;
}

bool PermissionRepository::insert(Permission* permission) {
    if (!DatabaseConnection::getInstance().isConnected() || !permission) {
        return false;
    }
    
    std::ostringstream query;
    query << "INSERT INTO permissions (name, description) VALUES ("
          << "'" << permission->getName() << "', "
          << "'" << permission->getDescription() << "');";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("Permission inserted: " + permission->getName());
    }
    return result;
}

bool PermissionRepository::update(Permission* permission) {
    if (!DatabaseConnection::getInstance().isConnected() || !permission) {
        return false;
    }
    
    std::ostringstream query;
    query << "UPDATE permissions SET "
          << "name = '" << permission->getName() << "', "
          << "description = '" << permission->getDescription() << "' "
          << "WHERE id = " << permission->getId() << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("Permission updated: " + permission->getName());
    }
    return result;
}

bool PermissionRepository::deleteById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "DELETE FROM permissions WHERE id = " << id << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("Permission deleted: " + std::to_string(id));
    }
    return result;
}

