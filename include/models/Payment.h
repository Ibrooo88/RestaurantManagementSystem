#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include "../enums/PaymentMethod.h"
#include "../enums/PaymentStatus.h"

class Payment {
private:
    int id;
    int orderId;
    double amount;
    PaymentMethod paymentMethod;
    PaymentStatus status;
    std::string transactionId;
    std::string paymentDate;

public:
    Payment();
    Payment(int id, int orderId, double amount, PaymentMethod paymentMethod,
            PaymentStatus status = PaymentStatus::PENDING);
    
    int getId() const;
    int getOrderId() const;
    double getAmount() const;
    PaymentMethod getPaymentMethod() const;
    PaymentStatus getStatus() const;
    std::string getTransactionId() const;
    std::string getPaymentDate() const;
    
    void setId(int id);
    void setOrderId(int orderId);
    void setAmount(double amount);
    void setPaymentMethod(PaymentMethod paymentMethod);
    void setStatus(PaymentStatus status);
    void setTransactionId(const std::string& transactionId);
    void setPaymentDate(const std::string& paymentDate);
};

#endif // PAYMENT_H

