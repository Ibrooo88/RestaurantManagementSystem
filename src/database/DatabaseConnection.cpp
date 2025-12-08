#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include <iostream>

DatabaseConnection& DatabaseConnection::getInstance() {
    static DatabaseConnection instance;
    return instance;
}

DatabaseConnection::~DatabaseConnection() {
    disconnect();
}

bool DatabaseConnection::connect(const std::string& dbPath) {
    if (connected && db != nullptr) {
        return true;
    }
    
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::string error = "Can't open database: " + std::string(sqlite3_errmsg(db));
        Logger::getInstance().error(error);
        sqlite3_close(db);
        db = nullptr;
        connected = false;
        return false;
    }
    
    connected = true;
    Logger::getInstance().info("Database connected successfully: " + dbPath);
    return true;
}

void DatabaseConnection::disconnect() {
    if (db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
        connected = false;
        Logger::getInstance().info("Database disconnected");
    }
}

bool DatabaseConnection::executeQuery(const std::string& query) {
    if (!connected || db == nullptr) {
        Logger::getInstance().error("Database not connected");
        return false;
    }
    
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::string error = "SQL error: " + std::string(errMsg);
        Logger::getInstance().error(error);
        sqlite3_free(errMsg);
        return false;
    }
    
    return true;
}

sqlite3* DatabaseConnection::getConnection() const {
    return db;
}

bool DatabaseConnection::isConnected() const {
    return connected && db != nullptr;
}

