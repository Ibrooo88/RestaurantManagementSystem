#include "../../include/services/ReservationService.h"
#include "../../include/repositories/ReservationRepository.h"
#include "../../include/repositories/TableRepository.h"
#include "../../include/utils/Logger.h"
#include "../../include/enums/ReservationStatus.h"

Reservation* ReservationService::createReservation(const std::string& customerName,
                                                   int tableId,
                                                   const std::string& reservationDate,
                                                   const std::string& reservationTime,
                                                   int numberOfGuests,
                                                   const std::string& customerPhone,
                                                   const std::string& customerEmail,
                                                   const std::string& specialRequests) {
    if (customerName.empty() || tableId <= 0 || numberOfGuests <= 0) {
        Logger::getInstance().warning("Invalid reservation data");
        return nullptr;
    }
    
    // Check if table exists
    TableRepository tableRepo;
    Table* table = tableRepo.getById(tableId);
    if (!table) {
        Logger::getInstance().warning("Table not found: " + std::to_string(tableId));
        return nullptr;
    }
    
    if (numberOfGuests > table->getCapacity()) {
        Logger::getInstance().warning("Number of guests exceeds table capacity");
        delete table;
        return nullptr;
    }
    
    delete table;
    
    Reservation* reservation = new Reservation();
    reservation->setCustomerName(customerName);
    reservation->setCustomerPhone(customerPhone);
    reservation->setCustomerEmail(customerEmail);
    reservation->setTableId(tableId);
    reservation->setReservationDate(reservationDate);
    reservation->setReservationTime(reservationTime);
    reservation->setNumberOfGuests(numberOfGuests);
    reservation->setStatus(ReservationStatus::PENDING);
    reservation->setSpecialRequests(specialRequests);
    
    ReservationRepository reservationRepo;
    if (reservationRepo.insert(reservation)) {
        Logger::getInstance().info("Reservation created for: " + customerName);
        return reservation;
    }
    
    delete reservation;
    return nullptr;
}

bool ReservationService::updateReservation(int reservationId, const std::string& customerName,
                                           int tableId, const std::string& reservationDate,
                                           const std::string& reservationTime, int numberOfGuests) {
    ReservationRepository reservationRepo;
    Reservation* reservation = reservationRepo.getById(reservationId);
    if (!reservation) {
        return false;
    }
    
    reservation->setCustomerName(customerName);
    reservation->setTableId(tableId);
    reservation->setReservationDate(reservationDate);
    reservation->setReservationTime(reservationTime);
    reservation->setNumberOfGuests(numberOfGuests);
    
    bool result = reservationRepo.update(reservation);
    if (result) {
        Logger::getInstance().info("Reservation updated: " + std::to_string(reservationId));
    }
    delete reservation;
    return result;
}

bool ReservationService::cancelReservation(int reservationId) {
    ReservationRepository reservationRepo;
    Reservation* reservation = reservationRepo.getById(reservationId);
    if (!reservation) {
        return false;
    }
    
    reservation->setStatus(ReservationStatus::CANCELLED);
    bool result = reservationRepo.update(reservation);
    if (result) {
        Logger::getInstance().info("Reservation cancelled: " + std::to_string(reservationId));
    }
    delete reservation;
    return result;
}

bool ReservationService::confirmReservation(int reservationId) {
    ReservationRepository reservationRepo;
    Reservation* reservation = reservationRepo.getById(reservationId);
    if (!reservation) {
        return false;
    }
    
    reservation->setStatus(ReservationStatus::CONFIRMED);
    bool result = reservationRepo.update(reservation);
    if (result) {
        Logger::getInstance().info("Reservation confirmed: " + std::to_string(reservationId));
    }
    delete reservation;
    return result;
}

bool ReservationService::markReservationAsSeated(int reservationId) {
    ReservationRepository reservationRepo;
    Reservation* reservation = reservationRepo.getById(reservationId);
    if (!reservation) {
        return false;
    }
    
    reservation->setStatus(ReservationStatus::SEATED);
    bool result = reservationRepo.update(reservation);
    if (result) {
        Logger::getInstance().info("Reservation marked as seated: " + std::to_string(reservationId));
    }
    delete reservation;
    return result;
}

std::vector<Reservation*> ReservationService::getReservationsByDate(const std::string& date) {
    ReservationRepository reservationRepo;
    return reservationRepo.getByDate(date);
}

std::vector<Reservation*> ReservationService::getReservationsByTable(int tableId) {
    ReservationRepository reservationRepo;
    return reservationRepo.getByTableId(tableId);
}

std::vector<Reservation*> ReservationService::getPendingReservations() {
    ReservationRepository reservationRepo;
    return reservationRepo.getByStatus(ReservationStatus::PENDING);
}

Reservation* ReservationService::getReservationById(int reservationId) {
    ReservationRepository reservationRepo;
    return reservationRepo.getById(reservationId);
}

