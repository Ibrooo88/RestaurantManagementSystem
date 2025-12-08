#include "../../include/models/Payment.h"

Payment::Payment() : id(0), orderId(0), amount(0.0),
                    paymentMethod(PaymentMethod::CASH), status(PaymentStatus::PENDING) {}

Payment::Payment(int id, int orderId, double amount, PaymentMethod paymentMethod, PaymentStatus status)
    : id(id), orderId(orderId), amount(amount), paymentMethod(paymentMethod), status(status) {}

int Payment::getId() const { return id; }
int Payment::getOrderId() const { return orderId; }
double Payment::getAmount() const { return amount; }
PaymentMethod Payment::getPaymentMethod() const { return paymentMethod; }
PaymentStatus Payment::getStatus() const { return status; }
std::string Payment::getTransactionId() const { return transactionId; }
std::string Payment::getPaymentDate() const { return paymentDate; }

void Payment::setId(int id) { this->id = id; }
void Payment::setOrderId(int orderId) { this->orderId = orderId; }
void Payment::setAmount(double amount) { this->amount = amount; }
void Payment::setPaymentMethod(PaymentMethod paymentMethod) { this->paymentMethod = paymentMethod; }
void Payment::setStatus(PaymentStatus status) { this->status = status; }
void Payment::setTransactionId(const std::string& transactionId) { this->transactionId = transactionId; }
void Payment::setPaymentDate(const std::string& paymentDate) { this->paymentDate = paymentDate; }

