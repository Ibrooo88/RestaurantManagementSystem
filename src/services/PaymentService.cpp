#include "../../include/services/PaymentService.h"
#include "../../include/repositories/PaymentRepository.h"
#include "../../include/repositories/OrderRepository.h"
#include "../../include/utils/Logger.h"
#include "../../include/utils/TimeUtils.h"
#include "../../include/enums/PaymentStatus.h"

Payment* PaymentService::processPayment(int orderId, double amount, PaymentMethod paymentMethod) {
    if (orderId <= 0 || amount <= 0) {
        Logger::getInstance().warning("Invalid payment data");
        return nullptr;
    }
    
    // Verify order exists
    OrderRepository orderRepo;
    Order* order = orderRepo.getById(orderId);
    if (!order) {
        Logger::getInstance().warning("Order not found: " + std::to_string(orderId));
        return nullptr;
    }
    
    // Check if amount matches order total (with tolerance)
    if (amount < order->getTotalAmount() * 0.9) {
        Logger::getInstance().warning("Payment amount is less than order total");
        delete order;
        return nullptr;
    }
    
    delete order;
    
    Payment* payment = new Payment();
    payment->setOrderId(orderId);
    payment->setAmount(amount);
    payment->setPaymentMethod(paymentMethod);
    payment->setStatus(PaymentStatus::COMPLETED);
    payment->setPaymentDate(TimeUtils::getCurrentDateTime());
    
    // Generate transaction ID
    std::string transactionId = "TXN-" + TimeUtils::getCurrentDateTime();
    payment->setTransactionId(transactionId);
    
    PaymentRepository paymentRepo;
    if (paymentRepo.insert(payment)) {
        Logger::getInstance().info("Payment processed: " + transactionId + " for order: " + std::to_string(orderId));
        return payment;
    }
    
    delete payment;
    return nullptr;
}

bool PaymentService::refundPayment(int paymentId) {
    PaymentRepository paymentRepo;
    Payment* payment = paymentRepo.getById(paymentId);
    if (!payment) {
        return false;
    }
    
    payment->setStatus(PaymentStatus::REFUNDED);
    bool result = paymentRepo.update(payment);
    if (result) {
        Logger::getInstance().info("Payment refunded: " + std::to_string(paymentId));
    }
    delete payment;
    return result;
}

std::vector<Payment*> PaymentService::getPaymentsByOrder(int orderId) {
    PaymentRepository paymentRepo;
    return paymentRepo.getByOrderId(orderId);
}

double PaymentService::getTotalRevenue() {
    PaymentRepository paymentRepo;
    auto payments = paymentRepo.getAll();
    
    double total = 0.0;
    for (auto* payment : payments) {
        if (payment->getStatus() == PaymentStatus::COMPLETED) {
            total += payment->getAmount();
        }
        delete payment;
    }
    
    return total;
}

double PaymentService::getTotalRevenueByDate(const std::string& date) {
    PaymentRepository paymentRepo;
    auto payments = paymentRepo.getAll();
    
    double total = 0.0;
    for (auto* payment : payments) {
        std::string paymentDate = payment->getPaymentDate().substr(0, 10); // Get date part
        if (paymentDate == date && payment->getStatus() == PaymentStatus::COMPLETED) {
            total += payment->getAmount();
        }
        delete payment;
    }
    
    return total;
}

Payment* PaymentService::getPaymentById(int paymentId) {
    PaymentRepository paymentRepo;
    return paymentRepo.getById(paymentId);
}

bool PaymentService::updatePaymentStatus(int paymentId, PaymentStatus status) {
    PaymentRepository paymentRepo;
    Payment* payment = paymentRepo.getById(paymentId);
    if (!payment) {
        return false;
    }
    
    payment->setStatus(status);
    bool result = paymentRepo.update(payment);
    delete payment;
    return result;
}

