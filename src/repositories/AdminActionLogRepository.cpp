#include "../../include/repositories/AdminActionLogRepository.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include <sqlite3.h>
#include <sstream>

AdminActionLog* AdminActionLogRepository::getById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, user_id, action_type, entity_type, entity_id, description, ip_address, created_at "
          << "FROM admin_action_logs WHERE id = " << id << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return nullptr;
    }
    
    AdminActionLog* log = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        log = new AdminActionLog();
        log->setId(sqlite3_column_int(stmt, 0));
        log->setUserId(sqlite3_column_int(stmt, 1));
        log->setActionType(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        log->setEntityType(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        log->setEntityId(sqlite3_column_int(stmt, 4));
        log->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        log->setIpAddress(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        log->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
    }
    
    sqlite3_finalize(stmt);
    return log;
}

std::vector<AdminActionLog*> AdminActionLogRepository::getAll() {
    std::vector<AdminActionLog*> logs;
    if (!DatabaseConnection::getInstance().isConnected()) {
        return logs;
    }
    
    std::string query = "SELECT id, user_id, action_type, entity_type, entity_id, description, ip_address, created_at "
                       "FROM admin_action_logs ORDER BY created_at DESC;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return logs;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        AdminActionLog* log = new AdminActionLog();
        log->setId(sqlite3_column_int(stmt, 0));
        log->setUserId(sqlite3_column_int(stmt, 1));
        log->setActionType(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        log->setEntityType(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        log->setEntityId(sqlite3_column_int(stmt, 4));
        log->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        log->setIpAddress(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        log->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        logs.push_back(log);
    }
    
    sqlite3_finalize(stmt);
    return logs;
}

std::vector<AdminActionLog*> AdminActionLogRepository::getByUserId(int userId) {
    std::vector<AdminActionLog*> logs;
    // Implementation similar to getAll with WHERE user_id = ...
    return logs;
}

std::vector<AdminActionLog*> AdminActionLogRepository::getByActionType(const std::string& actionType) {
    std::vector<AdminActionLog*> logs;
    // Implementation
    return logs;
}

bool AdminActionLogRepository::insert(AdminActionLog* log) {
    if (!log) {
        return false;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "INSERT INTO admin_action_logs (user_id, action_type, entity_type, entity_id, description, ip_address) VALUES ("
          << log->getUserId() << ", "
          << "'" << log->getActionType() << "', "
          << "'" << log->getEntityType() << "', "
          << log->getEntityId() << ", "
          << "'" << log->getDescription() << "', "
          << "'" << log->getIpAddress() << "');";
    
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

bool AdminActionLogRepository::deleteById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "DELETE FROM admin_action_logs WHERE id = " << id << ";";
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

