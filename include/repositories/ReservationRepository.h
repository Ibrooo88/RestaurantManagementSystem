#ifndef RESERVATIONREPOSITORY_H
#define RESERVATIONREPOSITORY_H

#include "../models/Reservation.h"
#include "../enums/ReservationStatus.h"
#include <vector>
#include <string>

class ReservationRepository {
public:
    Reservation* getById(int id);
    std::vector<Reservation*> getAll();
    std::vector<Reservation*> getByTableId(int tableId);
    std::vector<Reservation*> getByDate(const std::string& date);
    std::vector<Reservation*> getByStatus(ReservationStatus status);
    bool insert(Reservation* reservation);
    bool update(Reservation* reservation);
    bool deleteById(int id);
};

#endif // RESERVATIONREPOSITORY_H

