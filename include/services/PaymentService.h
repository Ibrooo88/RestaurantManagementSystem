#ifndef PAYMENTSERVICE_H
#define PAYMENTSERVICE_H

#include "../models/Payment.h"
#include "../enums/PaymentMethod.h"
#include "../enums/PaymentStatus.h"
#include <vector>

class PaymentService {
public:
    static Payment* processPayment(int orderId, double amount, PaymentMethod paymentMethod);
    static bool refundPayment(int paymentId);
    static std::vector<Payment*> getPaymentsByOrder(int orderId);
    static double getTotalRevenue();
    static double getTotalRevenueByDate(const std::string& date);
    static Payment* getPaymentById(int paymentId);
    static bool updatePaymentStatus(int paymentId, PaymentStatus status);
};

#endif // PAYMENTSERVICE_H

