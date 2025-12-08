#ifndef PAYMENTCONTROLLER_H
#define PAYMENTCONTROLLER_H

#include "../models/Payment.h"
#include "../enums/PaymentMethod.h"
#include "../enums/PaymentStatus.h"
#include <vector>

class PaymentController {
public:
    static Payment* processPayment(int orderId, double amount, PaymentMethod paymentMethod);
    static bool refundPayment(int paymentId);
    static std::vector<Payment*> getPaymentsByOrder(int orderId);
    static std::vector<Payment*> getAllPayments();
    static Payment* getPaymentById(int paymentId);
    static double getTotalRevenue();
    static double getTotalRevenueByDate(const std::string& date);
    static bool updatePaymentStatus(int paymentId, PaymentStatus status);
};

#endif // PAYMENTCONTROLLER_H

