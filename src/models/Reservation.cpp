#include "../../include/models/Reservation.h"

Reservation::Reservation() : id(0), tableId(0), numberOfGuests(0),
                            status(ReservationStatus::PENDING) {}

Reservation::Reservation(int id, const std::string& customerName, int tableId,
                         const std::string& reservationDate, const std::string& reservationTime,
                         int numberOfGuests, ReservationStatus status)
    : id(id), customerName(customerName), tableId(tableId), reservationDate(reservationDate),
      reservationTime(reservationTime), numberOfGuests(numberOfGuests), status(status) {}

int Reservation::getId() const { return id; }
std::string Reservation::getCustomerName() const { return customerName; }
std::string Reservation::getCustomerPhone() const { return customerPhone; }
std::string Reservation::getCustomerEmail() const { return customerEmail; }
int Reservation::getTableId() const { return tableId; }
std::string Reservation::getReservationDate() const { return reservationDate; }
std::string Reservation::getReservationTime() const { return reservationTime; }
int Reservation::getNumberOfGuests() const { return numberOfGuests; }
ReservationStatus Reservation::getStatus() const { return status; }
std::string Reservation::getSpecialRequests() const { return specialRequests; }
std::string Reservation::getCreatedAt() const { return createdAt; }
std::string Reservation::getUpdatedAt() const { return updatedAt; }

void Reservation::setId(int id) { this->id = id; }
void Reservation::setCustomerName(const std::string& customerName) { this->customerName = customerName; }
void Reservation::setCustomerPhone(const std::string& customerPhone) { this->customerPhone = customerPhone; }
void Reservation::setCustomerEmail(const std::string& customerEmail) { this->customerEmail = customerEmail; }
void Reservation::setTableId(int tableId) { this->tableId = tableId; }
void Reservation::setReservationDate(const std::string& reservationDate) { this->reservationDate = reservationDate; }
void Reservation::setReservationTime(const std::string& reservationTime) { this->reservationTime = reservationTime; }
void Reservation::setNumberOfGuests(int numberOfGuests) { this->numberOfGuests = numberOfGuests; }
void Reservation::setStatus(ReservationStatus status) { this->status = status; }
void Reservation::setSpecialRequests(const std::string& specialRequests) { this->specialRequests = specialRequests; }
void Reservation::setCreatedAt(const std::string& createdAt) { this->createdAt = createdAt; }
void Reservation::setUpdatedAt(const std::string& updatedAt) { this->updatedAt = updatedAt; }

