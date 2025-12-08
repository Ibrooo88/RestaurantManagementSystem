#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <string>
#include <memory>
#include <sqlite3.h>

class DatabaseConnection {
public:
    static DatabaseConnection& getInstance();
    bool connect(const std::string& dbPath = "restaurant.db");
    void disconnect();
    bool executeQuery(const std::string& query);
    sqlite3* getConnection() const;
    bool isConnected() const;
    
    // Prevent copying
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;

private:
    DatabaseConnection() : db(nullptr), connected(false) {}
    ~DatabaseConnection();
    
    sqlite3* db;
    bool connected;
};

#endif // DATABASECONNECTION_H

