#include "../../include/repositories/EventRepository.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include <sqlite3.h>
#include <sstream>

Event* EventRepository::getById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, name, description, event_date, event_time, number_of_guests, special_requirements, created_at "
          << "FROM events WHERE id = " << id << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in EventRepository::getById");
        return nullptr;
    }
    
    Event* event = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        event = new Event();
        event->setId(sqlite3_column_int(stmt, 0));
        event->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        event->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        event->setEventDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        event->setEventTime(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        event->setNumberOfGuests(sqlite3_column_int(stmt, 5));
        event->setSpecialRequirements(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        event->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
    }
    
    sqlite3_finalize(stmt);
    return event;
}

std::vector<Event*> EventRepository::getAll() {
    std::vector<Event*> events;
    if (!DatabaseConnection::getInstance().isConnected()) {
        return events;
    }
    
    std::string query = "SELECT id, name, description, event_date, event_time, number_of_guests, special_requirements, created_at "
                       "FROM events ORDER BY event_date ASC, event_time ASC;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in EventRepository::getAll");
        return events;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Event* event = new Event();
        event->setId(sqlite3_column_int(stmt, 0));
        event->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        event->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        event->setEventDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        event->setEventTime(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        event->setNumberOfGuests(sqlite3_column_int(stmt, 5));
        event->setSpecialRequirements(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        event->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        events.push_back(event);
    }
    
    sqlite3_finalize(stmt);
    return events;
}

std::vector<Event*> EventRepository::getByDate(const std::string& date) {
    std::vector<Event*> events;
    if (!DatabaseConnection::getInstance().isConnected()) {
        return events;
    }
    
    std::ostringstream query;
    query << "SELECT id, name, description, event_date, event_time, number_of_guests, special_requirements, created_at "
          << "FROM events WHERE event_date = '" << date << "' "
          << "ORDER BY event_time ASC;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in EventRepository::getByDate");
        return events;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Event* event = new Event();
        event->setId(sqlite3_column_int(stmt, 0));
        event->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        event->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        event->setEventDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        event->setEventTime(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        event->setNumberOfGuests(sqlite3_column_int(stmt, 5));
        event->setSpecialRequirements(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        event->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        events.push_back(event);
    }
    
    sqlite3_finalize(stmt);
    return events;
}

bool EventRepository::insert(Event* event) {
    if (!DatabaseConnection::getInstance().isConnected() || !event) {
        return false;
    }
    
    std::ostringstream query;
    query << "INSERT INTO events (name, description, event_date, event_time, number_of_guests, special_requirements) VALUES ("
          << "'" << event->getName() << "', "
          << "'" << event->getDescription() << "', "
          << "'" << event->getEventDate() << "', "
          << "'" << event->getEventTime() << "', "
          << event->getNumberOfGuests() << ", "
          << "'" << event->getSpecialRequirements() << "');";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("Event inserted: " + event->getName());
    }
    return result;
}

bool EventRepository::update(Event* event) {
    if (!DatabaseConnection::getInstance().isConnected() || !event) {
        return false;
    }
    
    std::ostringstream query;
    query << "UPDATE events SET "
          << "name = '" << event->getName() << "', "
          << "description = '" << event->getDescription() << "', "
          << "event_date = '" << event->getEventDate() << "', "
          << "event_time = '" << event->getEventTime() << "', "
          << "number_of_guests = " << event->getNumberOfGuests() << ", "
          << "special_requirements = '" << event->getSpecialRequirements() << "' "
          << "WHERE id = " << event->getId() << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("Event updated: " + event->getName());
    }
    return result;
}

bool EventRepository::deleteById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "DELETE FROM events WHERE id = " << id << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("Event deleted: " + std::to_string(id));
    }
    return result;
}

