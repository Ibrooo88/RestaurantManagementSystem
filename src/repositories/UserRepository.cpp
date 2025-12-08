#include "../../include/repositories/UserRepository.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include <sqlite3.h>
#include <sstream>
#include <cstring>

User* UserRepository::getById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, username, password, email, full_name, role_id, created_at, updated_at "
          << "FROM users WHERE id = " << id << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in UserRepository::getById");
        return nullptr;
    }
    
    User* user = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        user = new User();
        user->setId(sqlite3_column_int(stmt, 0));
        user->setUsername(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        user->setPassword(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        user->setEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        user->setFullName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        user->setRoleId(sqlite3_column_int(stmt, 5));
        user->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        user->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
    }
    
    sqlite3_finalize(stmt);
    return user;
}

User* UserRepository::getByUsername(const std::string& username) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, username, password, email, full_name, role_id, created_at, updated_at "
          << "FROM users WHERE username = '" << username << "';";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in UserRepository::getByUsername");
        return nullptr;
    }
    
    User* user = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        user = new User();
        user->setId(sqlite3_column_int(stmt, 0));
        user->setUsername(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        user->setPassword(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        user->setEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        user->setFullName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        user->setRoleId(sqlite3_column_int(stmt, 5));
        user->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        user->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
    }
    
    sqlite3_finalize(stmt);
    return user;
}

std::vector<User*> UserRepository::getAll() {
    std::vector<User*> users;
    if (!DatabaseConnection::getInstance().isConnected()) {
        return users;
    }
    
    std::string query = "SELECT id, username, password, email, full_name, role_id, created_at, updated_at FROM users;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in UserRepository::getAll");
        return users;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        User* user = new User();
        user->setId(sqlite3_column_int(stmt, 0));
        user->setUsername(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        user->setPassword(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        user->setEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        user->setFullName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        user->setRoleId(sqlite3_column_int(stmt, 5));
        user->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        user->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        users.push_back(user);
    }
    
    sqlite3_finalize(stmt);
    return users;
}

bool UserRepository::insert(User* user) {
    if (!DatabaseConnection::getInstance().isConnected() || !user) {
        return false;
    }
    
    std::ostringstream query;
    query << "INSERT INTO users (username, password, email, full_name, role_id) VALUES ("
          << "'" << user->getUsername() << "', "
          << "'" << user->getPassword() << "', "
          << "'" << user->getEmail() << "', "
          << "'" << user->getFullName() << "', "
          << user->getRoleId() << ");";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("User inserted: " + user->getUsername());
    }
    return result;
}

bool UserRepository::update(User* user) {
    if (!DatabaseConnection::getInstance().isConnected() || !user) {
        return false;
    }
    
    std::ostringstream query;
    query << "UPDATE users SET "
          << "username = '" << user->getUsername() << "', "
          << "password = '" << user->getPassword() << "', "
          << "email = '" << user->getEmail() << "', "
          << "full_name = '" << user->getFullName() << "', "
          << "role_id = " << user->getRoleId() << ", "
          << "updated_at = CURRENT_TIMESTAMP "
          << "WHERE id = " << user->getId() << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("User updated: " + user->getUsername());
    }
    return result;
}

bool UserRepository::deleteById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "DELETE FROM users WHERE id = " << id << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("User deleted: " + std::to_string(id));
    }
    return result;
}

bool UserRepository::authenticate(const std::string& username, const std::string& password) {
    User* user = getByUsername(username);
    if (!user) {
        return false;
    }
    
    bool authenticated = (user->getPassword() == password);
    delete user;
    return authenticated;
}

