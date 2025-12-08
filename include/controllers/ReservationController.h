#ifndef RESERVATIONCONTROLLER_H
#define RESERVATIONCONTROLLER_H

#include "../models/Reservation.h"
#include "../enums/ReservationStatus.h"
#include <vector>
#include <string>

class ReservationController {
public:
    static Reservation* createReservation(const std::string& customerName,
                                           int tableId,
                                           const std::string& reservationDate,
                                           const std::string& reservationTime,
                                           int numberOfGuests,
                                           const std::string& customerPhone = "",
                                           const std::string& customerEmail = "",
                                           const std::string& specialRequests = "");
    static bool updateReservation(int reservationId, const std::string& customerName,
                                 int tableId, const std::string& reservationDate,
                                 const std::string& reservationTime, int numberOfGuests);
    static bool cancelReservation(int reservationId);
    static bool confirmReservation(int reservationId);
    static bool markReservationAsSeated(int reservationId);
    static std::vector<Reservation*> getAllReservations();
    static std::vector<Reservation*> getReservationsByDate(const std::string& date);
    static std::vector<Reservation*> getReservationsByTable(int tableId);
    static std::vector<Reservation*> getPendingReservations();
    static Reservation* getReservationById(int reservationId);
};

#endif // RESERVATIONCONTROLLER_H

