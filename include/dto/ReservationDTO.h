#ifndef RESERVATIONDTO_H
#define RESERVATIONDTO_H

#include <string>
#include "../enums/ReservationStatus.h"

struct ReservationDTO {
    std::string customerName;
    std::string customerPhone;
    std::string customerEmail;
    int tableId;
    std::string reservationDate;
    std::string reservationTime;
    int numberOfGuests;
    std::string specialRequests;
    ReservationStatus status;
    
    ReservationDTO() : tableId(0), numberOfGuests(1), status(ReservationStatus::PENDING) {}
    ReservationDTO(const std::string& name, int table, const std::string& date, 
                   const std::string& time, int guests)
        : customerName(name), tableId(table), reservationDate(date),
          reservationTime(time), numberOfGuests(guests), status(ReservationStatus::PENDING) {}
};

#endif // RESERVATIONDTO_H

