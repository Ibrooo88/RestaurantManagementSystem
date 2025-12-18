#include "../../include/repositories/ChefRepository.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include "../../include/utils/SimulationMode.h"
#include <sqlite3.h>
#include <sstream>

Chef* ChefRepository::getById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, user_id, chef_type, status, skill_level, current_workload, specialization, created_at "
          << "FROM chefs WHERE id = " << id << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return nullptr;
    }
    
    Chef* chef = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        chef = new Chef();
        chef->setId(sqlite3_column_int(stmt, 0));
        chef->setUserId(sqlite3_column_int(stmt, 1));
        
        std::string typeStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        ChefType type = ChefType::NORMAL_CHEF;
        if (typeStr == "VIP_CHEF") type = ChefType::VIP_CHEF;
        else if (typeStr == "VEGAN_CHEF") type = ChefType::VEGAN_CHEF;
        else if (typeStr == "NORMAL_CHEF") type = ChefType::NORMAL_CHEF;
        chef->setChefType(type);
        
        std::string statusStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        ChefStatus status = ChefStatus::AVAILABLE;
        if (statusStr == "BUSY") status = ChefStatus::BUSY;
        else if (statusStr == "ON_BREAK") status = ChefStatus::ON_BREAK;
        else if (statusStr == "OFF_DUTY") status = ChefStatus::OFF_DUTY;
        chef->setStatus(status);
        
        chef->setSkillLevel(sqlite3_column_int(stmt, 4));
        chef->setCurrentWorkload(sqlite3_column_int(stmt, 5));
        chef->setSpecialization(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        chef->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
    }
    
    sqlite3_finalize(stmt);
    return chef;
}

Chef* ChefRepository::getByUserId(int userId) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, user_id, chef_type, status, skill_level, current_workload, specialization, created_at "
          << "FROM chefs WHERE user_id = " << userId << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return nullptr;
    }
    
    Chef* chef = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        chef = new Chef();
        chef->setId(sqlite3_column_int(stmt, 0));
        chef->setUserId(sqlite3_column_int(stmt, 1));
        // Similar parsing as getById...
    }
    
    sqlite3_finalize(stmt);
    return chef;
}

std::vector<Chef*> ChefRepository::getAll() {
    std::vector<Chef*> chefs;
    if (!DatabaseConnection::getInstance().isConnected()) {
        return chefs;
    }
    
    std::string query = "SELECT id, user_id, chef_type, status, skill_level, current_workload, specialization, created_at FROM chefs;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return chefs;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Chef* chef = new Chef();
        chef->setId(sqlite3_column_int(stmt, 0));
        chef->setUserId(sqlite3_column_int(stmt, 1));
        
        std::string typeStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        ChefType type = ChefType::NORMAL_CHEF;
        if (typeStr == "VIP_CHEF") type = ChefType::VIP_CHEF;
        else if (typeStr == "VEGAN_CHEF") type = ChefType::VEGAN_CHEF;
        else if (typeStr == "NORMAL_CHEF") type = ChefType::NORMAL_CHEF;
        chef->setChefType(type);
        
        std::string statusStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        ChefStatus status = ChefStatus::AVAILABLE;
        if (statusStr == "BUSY") status = ChefStatus::BUSY;
        else if (statusStr == "ON_BREAK") status = ChefStatus::ON_BREAK;
        else if (statusStr == "OFF_DUTY") status = ChefStatus::OFF_DUTY;
        chef->setStatus(status);
        
        chef->setSkillLevel(sqlite3_column_int(stmt, 4));
        chef->setCurrentWorkload(sqlite3_column_int(stmt, 5));
        chef->setSpecialization(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        chef->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        chefs.push_back(chef);
    }
    
    sqlite3_finalize(stmt);
    return chefs;
}

std::vector<Chef*> ChefRepository::getByStatus(ChefStatus status) {
    std::vector<Chef*> chefs;
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return chefs;
    }
    
    std::string statusStr = "AVAILABLE";
    switch (status) {
        case ChefStatus::BUSY: statusStr = "BUSY"; break;
        case ChefStatus::ON_BREAK: statusStr = "ON_BREAK"; break;
        case ChefStatus::OFF_DUTY: statusStr = "OFF_DUTY"; break;
        default: statusStr = "AVAILABLE"; break;
    }
    
    std::ostringstream query;
    query << "SELECT id, user_id, chef_type, status, skill_level, current_workload, specialization, created_at "
          << "FROM chefs WHERE status = '" << statusStr << "';";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return chefs;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Chef* chef = new Chef();
        chef->setId(sqlite3_column_int(stmt, 0));
        chef->setUserId(sqlite3_column_int(stmt, 1));
        
        std::string typeStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        ChefType type = ChefType::NORMAL_CHEF;
        if (typeStr == "VIP_CHEF") type = ChefType::VIP_CHEF;
        else if (typeStr == "VEGAN_CHEF") type = ChefType::VEGAN_CHEF;
        else if (typeStr == "NORMAL_CHEF") type = ChefType::NORMAL_CHEF;
        chef->setChefType(type);
        
        chef->setStatus(status);
        chef->setSkillLevel(sqlite3_column_int(stmt, 4));
        chef->setCurrentWorkload(sqlite3_column_int(stmt, 5));
        chef->setSpecialization(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        chef->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        chefs.push_back(chef);
    }
    
    sqlite3_finalize(stmt);
    return chefs;
}

std::vector<Chef*> ChefRepository::getAvailable() {
    return getByStatus(ChefStatus::AVAILABLE);
}

bool ChefRepository::insert(Chef* chef) {
    if (!chef) {
        return false;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::string typeStr = "NORMAL_CHEF";
    switch (chef->getChefType()) {
        case ChefType::VIP_CHEF: typeStr = "VIP_CHEF"; break;
        case ChefType::VEGAN_CHEF: typeStr = "VEGAN_CHEF"; break;
        case ChefType::NORMAL_CHEF: typeStr = "NORMAL_CHEF"; break;
    }
    
    std::string statusStr = "AVAILABLE";
    switch (chef->getStatus()) {
        case ChefStatus::BUSY: statusStr = "BUSY"; break;
        case ChefStatus::ON_BREAK: statusStr = "ON_BREAK"; break;
        case ChefStatus::OFF_DUTY: statusStr = "OFF_DUTY"; break;
        default: statusStr = "AVAILABLE"; break;
    }
    
    std::ostringstream query;
    query << "INSERT INTO chefs (user_id, chef_type, status, skill_level, current_workload, specialization) VALUES ("
          << chef->getUserId() << ", "
          << "'" << typeStr << "', "
          << "'" << statusStr << "', "
          << chef->getSkillLevel() << ", "
          << chef->getCurrentWorkload() << ", "
          << "'" << chef->getSpecialization() << "');";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("Chef inserted successfully");
    }
    return result;
}

bool ChefRepository::update(Chef* chef) {
    if (!chef) {
        return false;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::string typeStr = "NORMAL_CHEF";
    switch (chef->getChefType()) {
        case ChefType::VIP_CHEF: typeStr = "VIP_CHEF"; break;
        case ChefType::VEGAN_CHEF: typeStr = "VEGAN_CHEF"; break;
        case ChefType::NORMAL_CHEF: typeStr = "NORMAL_CHEF"; break;
    }
    
    std::string statusStr = "AVAILABLE";
    switch (chef->getStatus()) {
        case ChefStatus::BUSY: statusStr = "BUSY"; break;
        case ChefStatus::ON_BREAK: statusStr = "ON_BREAK"; break;
        case ChefStatus::OFF_DUTY: statusStr = "OFF_DUTY"; break;
        default: statusStr = "AVAILABLE"; break;
    }
    
    std::ostringstream query;
    query << "UPDATE chefs SET "
          << "chef_type = '" << typeStr << "', "
          << "status = '" << statusStr << "', "
          << "skill_level = " << chef->getSkillLevel() << ", "
          << "current_workload = " << chef->getCurrentWorkload() << ", "
          << "specialization = '" << chef->getSpecialization() << "' "
          << "WHERE id = " << chef->getId() << ";";
    
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

bool ChefRepository::deleteById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "DELETE FROM chefs WHERE id = " << id << ";";
    return DatabaseConnection::getInstance().executeQuery(query.str());
}
