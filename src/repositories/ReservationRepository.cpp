#include "../../include/repositories/ReservationRepository.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include "../../include/utils/SimulationMode.h"
#include <sqlite3.h>
#include <sstream>

Reservation* ReservationRepository::getById(int id) {
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto reservations = SimulationMode::getMockReservations();
        for (auto* reservation : reservations) {
            if (reservation->getId() == id) {
                return new Reservation(*reservation);
            }
        }
        return nullptr;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, customer_name, customer_phone, customer_email, table_id, "
          << "reservation_date, reservation_time, number_of_guests, status, special_requests, "
          << "created_at, updated_at FROM reservations WHERE id = " << id << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return nullptr;
    }
    
    Reservation* reservation = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        reservation = new Reservation();
        reservation->setId(sqlite3_column_int(stmt, 0));
        reservation->setCustomerName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        reservation->setCustomerPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        reservation->setCustomerEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        reservation->setTableId(sqlite3_column_int(stmt, 4));
        reservation->setReservationDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        reservation->setReservationTime(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        reservation->setNumberOfGuests(sqlite3_column_int(stmt, 7));
        
        std::string statusStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
        ReservationStatus status = ReservationStatus::PENDING;
        if (statusStr == "CONFIRMED") status = ReservationStatus::CONFIRMED;
        else if (statusStr == "SEATED") status = ReservationStatus::SEATED;
        else if (statusStr == "CANCELLED") status = ReservationStatus::CANCELLED;
        else if (statusStr == "COMPLETED") status = ReservationStatus::COMPLETED;
        else if (statusStr == "NO_SHOW") status = ReservationStatus::NO_SHOW;
        reservation->setStatus(status);
        
        reservation->setSpecialRequests(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        reservation->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
        reservation->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11)));
    }
    
    sqlite3_finalize(stmt);
    return reservation;
}

std::vector<Reservation*> ReservationRepository::getAll() {
    std::vector<Reservation*> reservations;
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto mockReservations = SimulationMode::getMockReservations();
        for (auto* reservation : mockReservations) {
            reservations.push_back(new Reservation(*reservation));
        }
        return reservations;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return reservations;
    }
    
    std::string query = "SELECT id, customer_name, customer_phone, customer_email, table_id, "
                       "reservation_date, reservation_time, number_of_guests, status, special_requests, "
                       "created_at, updated_at FROM reservations;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return reservations;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Reservation* reservation = new Reservation();
        reservation->setId(sqlite3_column_int(stmt, 0));
        reservation->setCustomerName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        reservation->setCustomerPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        reservation->setCustomerEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        reservation->setTableId(sqlite3_column_int(stmt, 4));
        reservation->setReservationDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        reservation->setReservationTime(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        reservation->setNumberOfGuests(sqlite3_column_int(stmt, 7));
        
        std::string statusStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
        ReservationStatus status = ReservationStatus::PENDING;
        if (statusStr == "CONFIRMED") status = ReservationStatus::CONFIRMED;
        else if (statusStr == "SEATED") status = ReservationStatus::SEATED;
        else if (statusStr == "CANCELLED") status = ReservationStatus::CANCELLED;
        else if (statusStr == "COMPLETED") status = ReservationStatus::COMPLETED;
        else if (statusStr == "NO_SHOW") status = ReservationStatus::NO_SHOW;
        reservation->setStatus(status);
        
        reservation->setSpecialRequests(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        reservation->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
        reservation->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11)));
        reservations.push_back(reservation);
    }
    
    sqlite3_finalize(stmt);
    return reservations;
}

std::vector<Reservation*> ReservationRepository::getByTableId(int tableId) {
    std::vector<Reservation*> reservations;
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto mockReservations = SimulationMode::getMockReservations();
        for (auto* reservation : mockReservations) {
            if (reservation->getTableId() == tableId) {
                reservations.push_back(new Reservation(*reservation));
            }
        }
        return reservations;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return reservations;
    }
    
    std::ostringstream query;
    query << "SELECT id, customer_name, customer_phone, customer_email, table_id, "
          << "reservation_date, reservation_time, number_of_guests, status, special_requests, "
          << "created_at, updated_at FROM reservations WHERE table_id = " << tableId << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return reservations;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Reservation* reservation = new Reservation();
        reservation->setId(sqlite3_column_int(stmt, 0));
        reservation->setCustomerName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        reservation->setCustomerPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        reservation->setCustomerEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        reservation->setTableId(sqlite3_column_int(stmt, 4));
        reservation->setReservationDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        reservation->setReservationTime(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        reservation->setNumberOfGuests(sqlite3_column_int(stmt, 7));
        
        std::string statusStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
        ReservationStatus status = ReservationStatus::PENDING;
        if (statusStr == "CONFIRMED") status = ReservationStatus::CONFIRMED;
        else if (statusStr == "SEATED") status = ReservationStatus::SEATED;
        else if (statusStr == "CANCELLED") status = ReservationStatus::CANCELLED;
        else if (statusStr == "COMPLETED") status = ReservationStatus::COMPLETED;
        else if (statusStr == "NO_SHOW") status = ReservationStatus::NO_SHOW;
        reservation->setStatus(status);
        
        reservation->setSpecialRequests(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        reservation->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
        reservation->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11)));
        reservations.push_back(reservation);
    }
    
    sqlite3_finalize(stmt);
    return reservations;
}

std::vector<Reservation*> ReservationRepository::getByDate(const std::string& date) {
    std::vector<Reservation*> reservations;
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto mockReservations = SimulationMode::getMockReservations();
        for (auto* reservation : mockReservations) {
            if (reservation->getReservationDate() == date) {
                reservations.push_back(new Reservation(*reservation));
            }
        }
        return reservations;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return reservations;
    }
    
    std::ostringstream query;
    query << "SELECT id, customer_name, customer_phone, customer_email, table_id, "
          << "reservation_date, reservation_time, number_of_guests, status, special_requests, "
          << "created_at, updated_at FROM reservations WHERE reservation_date = '" << date << "';";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return reservations;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Reservation* reservation = new Reservation();
        reservation->setId(sqlite3_column_int(stmt, 0));
        reservation->setCustomerName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        reservation->setCustomerPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        reservation->setCustomerEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        reservation->setTableId(sqlite3_column_int(stmt, 4));
        reservation->setReservationDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        reservation->setReservationTime(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        reservation->setNumberOfGuests(sqlite3_column_int(stmt, 7));
        
        std::string statusStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
        ReservationStatus status = ReservationStatus::PENDING;
        if (statusStr == "CONFIRMED") status = ReservationStatus::CONFIRMED;
        else if (statusStr == "SEATED") status = ReservationStatus::SEATED;
        else if (statusStr == "CANCELLED") status = ReservationStatus::CANCELLED;
        else if (statusStr == "COMPLETED") status = ReservationStatus::COMPLETED;
        else if (statusStr == "NO_SHOW") status = ReservationStatus::NO_SHOW;
        reservation->setStatus(status);
        
        reservation->setSpecialRequests(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        reservation->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
        reservation->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11)));
        reservations.push_back(reservation);
    }
    
    sqlite3_finalize(stmt);
    return reservations;
}

std::vector<Reservation*> ReservationRepository::getByStatus(ReservationStatus status) {
    std::vector<Reservation*> reservations;
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto mockReservations = SimulationMode::getMockReservations();
        for (auto* reservation : mockReservations) {
            if (reservation->getStatus() == status) {
                reservations.push_back(new Reservation(*reservation));
            }
        }
        return reservations;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return reservations;
    }
    
    std::string statusStr = "PENDING";
    switch (status) {
        case ReservationStatus::CONFIRMED: statusStr = "CONFIRMED"; break;
        case ReservationStatus::SEATED: statusStr = "SEATED"; break;
        case ReservationStatus::CANCELLED: statusStr = "CANCELLED"; break;
        case ReservationStatus::COMPLETED: statusStr = "COMPLETED"; break;
        case ReservationStatus::NO_SHOW: statusStr = "NO_SHOW"; break;
    }
    
    std::ostringstream query;
    query << "SELECT id, customer_name, customer_phone, customer_email, table_id, "
          << "reservation_date, reservation_time, number_of_guests, status, special_requests, "
          << "created_at, updated_at FROM reservations WHERE status = '" << statusStr << "';";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return reservations;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Reservation* reservation = new Reservation();
        reservation->setId(sqlite3_column_int(stmt, 0));
        reservation->setCustomerName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        reservation->setCustomerPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        reservation->setCustomerEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        reservation->setTableId(sqlite3_column_int(stmt, 4));
        reservation->setReservationDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        reservation->setReservationTime(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        reservation->setNumberOfGuests(sqlite3_column_int(stmt, 7));
        reservation->setStatus(status);
        reservation->setSpecialRequests(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        reservation->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
        reservation->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11)));
        reservations.push_back(reservation);
    }
    
    sqlite3_finalize(stmt);
    return reservations;
}

bool ReservationRepository::insert(Reservation* reservation) {
    if (!reservation) {
        return false;
    }
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        return SimulationMode::insertMockReservation(reservation);
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::string statusStr = "PENDING";
    switch (reservation->getStatus()) {
        case ReservationStatus::CONFIRMED: statusStr = "CONFIRMED"; break;
        case ReservationStatus::SEATED: statusStr = "SEATED"; break;
        case ReservationStatus::CANCELLED: statusStr = "CANCELLED"; break;
        case ReservationStatus::COMPLETED: statusStr = "COMPLETED"; break;
        case ReservationStatus::NO_SHOW: statusStr = "NO_SHOW"; break;
    }
    
    std::ostringstream query;
    query << "INSERT INTO reservations (customer_name, customer_phone, customer_email, table_id, "
          << "reservation_date, reservation_time, number_of_guests, status, special_requests) VALUES ("
          << "'" << reservation->getCustomerName() << "', "
          << "'" << reservation->getCustomerPhone() << "', "
          << "'" << reservation->getCustomerEmail() << "', "
          << reservation->getTableId() << ", "
          << "'" << reservation->getReservationDate() << "', "
          << "'" << reservation->getReservationTime() << "', "
          << reservation->getNumberOfGuests() << ", "
          << "'" << statusStr << "', "
          << "'" << reservation->getSpecialRequests() << "');";
    
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

bool ReservationRepository::update(Reservation* reservation) {
    if (!reservation) {
        return false;
    }
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        return SimulationMode::updateMockReservation(reservation->getId(), reservation);
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::string statusStr = "PENDING";
    switch (reservation->getStatus()) {
        case ReservationStatus::CONFIRMED: statusStr = "CONFIRMED"; break;
        case ReservationStatus::SEATED: statusStr = "SEATED"; break;
        case ReservationStatus::CANCELLED: statusStr = "CANCELLED"; break;
        case ReservationStatus::COMPLETED: statusStr = "COMPLETED"; break;
        case ReservationStatus::NO_SHOW: statusStr = "NO_SHOW"; break;
    }
    
    std::ostringstream query;
    query << "UPDATE reservations SET "
          << "customer_name = '" << reservation->getCustomerName() << "', "
          << "customer_phone = '" << reservation->getCustomerPhone() << "', "
          << "customer_email = '" << reservation->getCustomerEmail() << "', "
          << "table_id = " << reservation->getTableId() << ", "
          << "reservation_date = '" << reservation->getReservationDate() << "', "
          << "reservation_time = '" << reservation->getReservationTime() << "', "
          << "number_of_guests = " << reservation->getNumberOfGuests() << ", "
          << "status = '" << statusStr << "', "
          << "special_requests = '" << reservation->getSpecialRequests() << "', "
          << "updated_at = CURRENT_TIMESTAMP "
          << "WHERE id = " << reservation->getId() << ";";
    
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

bool ReservationRepository::deleteById(int id) {
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        return SimulationMode::deleteMockReservation(id);
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "DELETE FROM reservations WHERE id = " << id << ";";
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

