#include "../../include/controllers/PaymentController.h"
#include "../../include/services/PaymentService.h"
#include "../../include/repositories/PaymentRepository.h"
#include "../../include/utils/Logger.h"

Payment* PaymentController::processPayment(int orderId, double amount, PaymentMethod paymentMethod) {
    return PaymentService::processPayment(orderId, amount, paymentMethod);
}

bool PaymentController::refundPayment(int paymentId) {
    return PaymentService::refundPayment(paymentId);
}

std::vector<Payment*> PaymentController::getPaymentsByOrder(int orderId) {
    return PaymentService::getPaymentsByOrder(orderId);
}

std::vector<Payment*> PaymentController::getAllPayments() {
    PaymentRepository paymentRepo;
    return paymentRepo.getAll();
}

Payment* PaymentController::getPaymentById(int paymentId) {
    return PaymentService::getPaymentById(paymentId);
}

double PaymentController::getTotalRevenue() {
    return PaymentService::getTotalRevenue();
}

double PaymentController::getTotalRevenueByDate(const std::string& date) {
    return PaymentService::getTotalRevenueByDate(date);
}

bool PaymentController::updatePaymentStatus(int paymentId, PaymentStatus status) {
    return PaymentService::updatePaymentStatus(paymentId, status);
}

