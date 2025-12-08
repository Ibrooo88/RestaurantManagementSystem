#include "../../include/repositories/RoleRepository.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include <sqlite3.h>
#include <sstream>

Role* RoleRepository::getById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, name, description, created_at "
          << "FROM roles WHERE id = " << id << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in RoleRepository::getById");
        return nullptr;
    }
    
    Role* role = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        role = new Role();
        role->setId(sqlite3_column_int(stmt, 0));
        role->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        role->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        role->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
    }
    
    sqlite3_finalize(stmt);
    return role;
}

Role* RoleRepository::getByName(const std::string& name) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, name, description, created_at "
          << "FROM roles WHERE name = '" << name << "';";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in RoleRepository::getByName");
        return nullptr;
    }
    
    Role* role = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        role = new Role();
        role->setId(sqlite3_column_int(stmt, 0));
        role->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        role->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        role->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
    }
    
    sqlite3_finalize(stmt);
    return role;
}

std::vector<Role*> RoleRepository::getAll() {
    std::vector<Role*> roles;
    if (!DatabaseConnection::getInstance().isConnected()) {
        return roles;
    }
    
    std::string query = "SELECT id, name, description, created_at FROM roles;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in RoleRepository::getAll");
        return roles;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Role* role = new Role();
        role->setId(sqlite3_column_int(stmt, 0));
        role->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        role->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        role->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        roles.push_back(role);
    }
    
    sqlite3_finalize(stmt);
    return roles;
}

bool RoleRepository::insert(Role* role) {
    if (!DatabaseConnection::getInstance().isConnected() || !role) {
        return false;
    }
    
    std::ostringstream query;
    query << "INSERT INTO roles (name, description) VALUES ("
          << "'" << role->getName() << "', "
          << "'" << role->getDescription() << "');";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("Role inserted: " + role->getName());
    }
    return result;
}

bool RoleRepository::update(Role* role) {
    if (!DatabaseConnection::getInstance().isConnected() || !role) {
        return false;
    }
    
    std::ostringstream query;
    query << "UPDATE roles SET "
          << "name = '" << role->getName() << "', "
          << "description = '" << role->getDescription() << "' "
          << "WHERE id = " << role->getId() << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("Role updated: " + role->getName());
    }
    return result;
}

bool RoleRepository::deleteById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "DELETE FROM roles WHERE id = " << id << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("Role deleted: " + std::to_string(id));
    }
    return result;
}

