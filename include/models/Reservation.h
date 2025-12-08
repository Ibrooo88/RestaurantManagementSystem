#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include "../enums/ReservationStatus.h"

class Reservation {
private:
    int id;
    std::string customerName;
    std::string customerPhone;
    std::string customerEmail;
    int tableId;
    std::string reservationDate;
    std::string reservationTime;
    int numberOfGuests;
    ReservationStatus status;
    std::string specialRequests;
    std::string createdAt;
    std::string updatedAt;

public:
    Reservation();
    Reservation(int id, const std::string& customerName, int tableId,
                const std::string& reservationDate, const std::string& reservationTime,
                int numberOfGuests, ReservationStatus status = ReservationStatus::PENDING);
    
    int getId() const;
    std::string getCustomerName() const;
    std::string getCustomerPhone() const;
    std::string getCustomerEmail() const;
    int getTableId() const;
    std::string getReservationDate() const;
    std::string getReservationTime() const;
    int getNumberOfGuests() const;
    ReservationStatus getStatus() const;
    std::string getSpecialRequests() const;
    std::string getCreatedAt() const;
    std::string getUpdatedAt() const;
    
    void setId(int id);
    void setCustomerName(const std::string& customerName);
    void setCustomerPhone(const std::string& customerPhone);
    void setCustomerEmail(const std::string& customerEmail);
    void setTableId(int tableId);
    void setReservationDate(const std::string& reservationDate);
    void setReservationTime(const std::string& reservationTime);
    void setNumberOfGuests(int numberOfGuests);
    void setStatus(ReservationStatus status);
    void setSpecialRequests(const std::string& specialRequests);
    void setCreatedAt(const std::string& createdAt);
    void setUpdatedAt(const std::string& updatedAt);
};

#endif // RESERVATION_H

