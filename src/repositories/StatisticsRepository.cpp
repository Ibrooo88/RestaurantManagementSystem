#include "../../include/repositories/StatisticsRepository.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include <sqlite3.h>
#include <sstream>

Statistics* StatisticsRepository::getById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, date, total_orders, total_revenue, total_customers, average_order_value, most_popular_item_id, created_at "
          << "FROM statistics WHERE id = " << id << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in StatisticsRepository::getById");
        return nullptr;
    }
    
    Statistics* statistics = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        statistics = new Statistics();
        statistics->setId(sqlite3_column_int(stmt, 0));
        statistics->setDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        statistics->setTotalOrders(sqlite3_column_int(stmt, 2));
        statistics->setTotalRevenue(sqlite3_column_double(stmt, 3));
        statistics->setTotalCustomers(sqlite3_column_int(stmt, 4));
        statistics->setAverageOrderValue(sqlite3_column_double(stmt, 5));
        statistics->setMostPopularItemId(sqlite3_column_int(stmt, 6));
        statistics->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
    }
    
    sqlite3_finalize(stmt);
    return statistics;
}

Statistics* StatisticsRepository::getByDate(const std::string& date) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, date, total_orders, total_revenue, total_customers, average_order_value, most_popular_item_id, created_at "
          << "FROM statistics WHERE date = '" << date << "';";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in StatisticsRepository::getByDate");
        return nullptr;
    }
    
    Statistics* statistics = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        statistics = new Statistics();
        statistics->setId(sqlite3_column_int(stmt, 0));
        statistics->setDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        statistics->setTotalOrders(sqlite3_column_int(stmt, 2));
        statistics->setTotalRevenue(sqlite3_column_double(stmt, 3));
        statistics->setTotalCustomers(sqlite3_column_int(stmt, 4));
        statistics->setAverageOrderValue(sqlite3_column_double(stmt, 5));
        statistics->setMostPopularItemId(sqlite3_column_int(stmt, 6));
        statistics->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
    }
    
    sqlite3_finalize(stmt);
    return statistics;
}

std::vector<Statistics*> StatisticsRepository::getAll() {
    std::vector<Statistics*> statisticsList;
    if (!DatabaseConnection::getInstance().isConnected()) {
        return statisticsList;
    }
    
    std::string query = "SELECT id, date, total_orders, total_revenue, total_customers, average_order_value, most_popular_item_id, created_at "
                       "FROM statistics ORDER BY date DESC;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in StatisticsRepository::getAll");
        return statisticsList;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Statistics* statistics = new Statistics();
        statistics->setId(sqlite3_column_int(stmt, 0));
        statistics->setDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        statistics->setTotalOrders(sqlite3_column_int(stmt, 2));
        statistics->setTotalRevenue(sqlite3_column_double(stmt, 3));
        statistics->setTotalCustomers(sqlite3_column_int(stmt, 4));
        statistics->setAverageOrderValue(sqlite3_column_double(stmt, 5));
        statistics->setMostPopularItemId(sqlite3_column_int(stmt, 6));
        statistics->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        statisticsList.push_back(statistics);
    }
    
    sqlite3_finalize(stmt);
    return statisticsList;
}

std::vector<Statistics*> StatisticsRepository::getByDateRange(const std::string& startDate, const std::string& endDate) {
    std::vector<Statistics*> statisticsList;
    if (!DatabaseConnection::getInstance().isConnected()) {
        return statisticsList;
    }
    
    std::ostringstream query;
    query << "SELECT id, date, total_orders, total_revenue, total_customers, average_order_value, most_popular_item_id, created_at "
          << "FROM statistics WHERE date >= '" << startDate << "' AND date <= '" << endDate << "' "
          << "ORDER BY date ASC;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in StatisticsRepository::getByDateRange");
        return statisticsList;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Statistics* statistics = new Statistics();
        statistics->setId(sqlite3_column_int(stmt, 0));
        statistics->setDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        statistics->setTotalOrders(sqlite3_column_int(stmt, 2));
        statistics->setTotalRevenue(sqlite3_column_double(stmt, 3));
        statistics->setTotalCustomers(sqlite3_column_int(stmt, 4));
        statistics->setAverageOrderValue(sqlite3_column_double(stmt, 5));
        statistics->setMostPopularItemId(sqlite3_column_int(stmt, 6));
        statistics->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        statisticsList.push_back(statistics);
    }
    
    sqlite3_finalize(stmt);
    return statisticsList;
}

bool StatisticsRepository::insert(Statistics* statistics) {
    if (!DatabaseConnection::getInstance().isConnected() || !statistics) {
        return false;
    }
    
    std::ostringstream query;
    query << "INSERT INTO statistics (date, total_orders, total_revenue, total_customers, average_order_value, most_popular_item_id) VALUES ("
          << "'" << statistics->getDate() << "', "
          << statistics->getTotalOrders() << ", "
          << statistics->getTotalRevenue() << ", "
          << statistics->getTotalCustomers() << ", "
          << statistics->getAverageOrderValue() << ", "
          << statistics->getMostPopularItemId() << ");";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("Statistics inserted for date: " + statistics->getDate());
    }
    return result;
}

bool StatisticsRepository::update(Statistics* statistics) {
    if (!DatabaseConnection::getInstance().isConnected() || !statistics) {
        return false;
    }
    
    std::ostringstream query;
    query << "UPDATE statistics SET "
          << "total_orders = " << statistics->getTotalOrders() << ", "
          << "total_revenue = " << statistics->getTotalRevenue() << ", "
          << "total_customers = " << statistics->getTotalCustomers() << ", "
          << "average_order_value = " << statistics->getAverageOrderValue() << ", "
          << "most_popular_item_id = " << statistics->getMostPopularItemId() << " "
          << "WHERE id = " << statistics->getId() << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("Statistics updated for date: " + statistics->getDate());
    }
    return result;
}

bool StatisticsRepository::deleteById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "DELETE FROM statistics WHERE id = " << id << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("Statistics deleted: " + std::to_string(id));
    }
    return result;
}

