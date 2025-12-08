#include "../../include/repositories/AccessScopeRepository.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include <sqlite3.h>
#include <sstream>

AccessScope* AccessScopeRepository::getById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, name, description, created_at "
          << "FROM access_scopes WHERE id = " << id << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in AccessScopeRepository::getById");
        return nullptr;
    }
    
    AccessScope* accessScope = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        accessScope = new AccessScope();
        accessScope->setId(sqlite3_column_int(stmt, 0));
        accessScope->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        accessScope->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        accessScope->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
    }
    
    sqlite3_finalize(stmt);
    return accessScope;
}

AccessScope* AccessScopeRepository::getByName(const std::string& name) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, name, description, created_at "
          << "FROM access_scopes WHERE name = '" << name << "';";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in AccessScopeRepository::getByName");
        return nullptr;
    }
    
    AccessScope* accessScope = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        accessScope = new AccessScope();
        accessScope->setId(sqlite3_column_int(stmt, 0));
        accessScope->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        accessScope->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        accessScope->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
    }
    
    sqlite3_finalize(stmt);
    return accessScope;
}

std::vector<AccessScope*> AccessScopeRepository::getAll() {
    std::vector<AccessScope*> accessScopes;
    if (!DatabaseConnection::getInstance().isConnected()) {
        return accessScopes;
    }
    
    std::string query = "SELECT id, name, description, created_at FROM access_scopes;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in AccessScopeRepository::getAll");
        return accessScopes;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        AccessScope* accessScope = new AccessScope();
        accessScope->setId(sqlite3_column_int(stmt, 0));
        accessScope->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        accessScope->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        accessScope->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        accessScopes.push_back(accessScope);
    }
    
    sqlite3_finalize(stmt);
    return accessScopes;
}

bool AccessScopeRepository::insert(AccessScope* accessScope) {
    if (!DatabaseConnection::getInstance().isConnected() || !accessScope) {
        return false;
    }
    
    std::ostringstream query;
    query << "INSERT INTO access_scopes (name, description) VALUES ("
          << "'" << accessScope->getName() << "', "
          << "'" << accessScope->getDescription() << "');";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("AccessScope inserted: " + accessScope->getName());
    }
    return result;
}

bool AccessScopeRepository::update(AccessScope* accessScope) {
    if (!DatabaseConnection::getInstance().isConnected() || !accessScope) {
        return false;
    }
    
    std::ostringstream query;
    query << "UPDATE access_scopes SET "
          << "name = '" << accessScope->getName() << "', "
          << "description = '" << accessScope->getDescription() << "' "
          << "WHERE id = " << accessScope->getId() << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("AccessScope updated: " + accessScope->getName());
    }
    return result;
}

bool AccessScopeRepository::deleteById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "DELETE FROM access_scopes WHERE id = " << id << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("AccessScope deleted: " + std::to_string(id));
    }
    return result;
}

