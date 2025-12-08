#include "../../include/controllers/ReservationController.h"
#include "../../include/services/ReservationService.h"
#include "../../include/repositories/ReservationRepository.h"
#include "../../include/utils/Logger.h"

Reservation* ReservationController::createReservation(const std::string& customerName,
                                                     int tableId,
                                                     const std::string& reservationDate,
                                                     const std::string& reservationTime,
                                                     int numberOfGuests,
                                                     const std::string& customerPhone,
                                                     const std::string& customerEmail,
                                                     const std::string& specialRequests) {
    return ReservationService::createReservation(customerName, tableId, reservationDate,
                                                 reservationTime, numberOfGuests,
                                                 customerPhone, customerEmail, specialRequests);
}

bool ReservationController::updateReservation(int reservationId, const std::string& customerName,
                                              int tableId, const std::string& reservationDate,
                                              const std::string& reservationTime, int numberOfGuests) {
    return ReservationService::updateReservation(reservationId, customerName, tableId,
                                                  reservationDate, reservationTime, numberOfGuests);
}

bool ReservationController::cancelReservation(int reservationId) {
    return ReservationService::cancelReservation(reservationId);
}

bool ReservationController::confirmReservation(int reservationId) {
    return ReservationService::confirmReservation(reservationId);
}

bool ReservationController::markReservationAsSeated(int reservationId) {
    return ReservationService::markReservationAsSeated(reservationId);
}

std::vector<Reservation*> ReservationController::getAllReservations() {
    ReservationRepository reservationRepo;
    return reservationRepo.getAll();
}

std::vector<Reservation*> ReservationController::getReservationsByDate(const std::string& date) {
    return ReservationService::getReservationsByDate(date);
}

std::vector<Reservation*> ReservationController::getReservationsByTable(int tableId) {
    return ReservationService::getReservationsByTable(tableId);
}

std::vector<Reservation*> ReservationController::getPendingReservations() {
    return ReservationService::getPendingReservations();
}

Reservation* ReservationController::getReservationById(int reservationId) {
    return ReservationService::getReservationById(reservationId);
}

