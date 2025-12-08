#include "../../include/repositories/PaymentRepository.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include "../../include/utils/SimulationMode.h"
#include <sqlite3.h>
#include <sstream>

Payment* PaymentRepository::getById(int id) {
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto payments = SimulationMode::getMockPayments();
        for (auto* payment : payments) {
            if (payment->getId() == id) {
                return new Payment(*payment);
            }
        }
        return nullptr;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, order_id, amount, payment_method, status, transaction_id, payment_date "
          << "FROM payments WHERE id = " << id << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return nullptr;
    }
    
    Payment* payment = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        payment = new Payment();
        payment->setId(sqlite3_column_int(stmt, 0));
        payment->setOrderId(sqlite3_column_int(stmt, 1));
        payment->setAmount(sqlite3_column_double(stmt, 2));
        
        std::string methodStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        PaymentMethod method = PaymentMethod::CASH;
        if (methodStr == "CREDIT_CARD") method = PaymentMethod::CREDIT_CARD;
        else if (methodStr == "DEBIT_CARD") method = PaymentMethod::DEBIT_CARD;
        else if (methodStr == "MOBILE_PAYMENT") method = PaymentMethod::MOBILE_PAYMENT;
        else if (methodStr == "ONLINE_PAYMENT") method = PaymentMethod::ONLINE_PAYMENT;
        payment->setPaymentMethod(method);
        
        std::string statusStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        PaymentStatus status = PaymentStatus::PENDING;
        if (statusStr == "COMPLETED") status = PaymentStatus::COMPLETED;
        else if (statusStr == "FAILED") status = PaymentStatus::FAILED;
        else if (statusStr == "REFUNDED") status = PaymentStatus::REFUNDED;
        payment->setStatus(status);
        
        payment->setTransactionId(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        payment->setPaymentDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
    }
    
    sqlite3_finalize(stmt);
    return payment;
}

std::vector<Payment*> PaymentRepository::getAll() {
    std::vector<Payment*> payments;
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto mockPayments = SimulationMode::getMockPayments();
        for (auto* payment : mockPayments) {
            payments.push_back(new Payment(*payment));
        }
        return payments;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return payments;
    }
    
    std::string query = "SELECT id, order_id, amount, payment_method, status, transaction_id, payment_date FROM payments;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return payments;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Payment* payment = new Payment();
        payment->setId(sqlite3_column_int(stmt, 0));
        payment->setOrderId(sqlite3_column_int(stmt, 1));
        payment->setAmount(sqlite3_column_double(stmt, 2));
        
        std::string methodStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        PaymentMethod method = PaymentMethod::CASH;
        if (methodStr == "CREDIT_CARD") method = PaymentMethod::CREDIT_CARD;
        else if (methodStr == "DEBIT_CARD") method = PaymentMethod::DEBIT_CARD;
        else if (methodStr == "MOBILE_PAYMENT") method = PaymentMethod::MOBILE_PAYMENT;
        else if (methodStr == "ONLINE_PAYMENT") method = PaymentMethod::ONLINE_PAYMENT;
        payment->setPaymentMethod(method);
        
        std::string statusStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        PaymentStatus status = PaymentStatus::PENDING;
        if (statusStr == "COMPLETED") status = PaymentStatus::COMPLETED;
        else if (statusStr == "FAILED") status = PaymentStatus::FAILED;
        else if (statusStr == "REFUNDED") status = PaymentStatus::REFUNDED;
        payment->setStatus(status);
        
        payment->setTransactionId(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        payment->setPaymentDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        payments.push_back(payment);
    }
    
    sqlite3_finalize(stmt);
    return payments;
}

std::vector<Payment*> PaymentRepository::getByOrderId(int orderId) {
    std::vector<Payment*> payments;
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto mockPayments = SimulationMode::getMockPayments();
        for (auto* payment : mockPayments) {
            if (payment->getOrderId() == orderId) {
                payments.push_back(new Payment(*payment));
            }
        }
        return payments;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return payments;
    }
    
    std::ostringstream query;
    query << "SELECT id, order_id, amount, payment_method, status, transaction_id, payment_date "
          << "FROM payments WHERE order_id = " << orderId << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return payments;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Payment* payment = new Payment();
        payment->setId(sqlite3_column_int(stmt, 0));
        payment->setOrderId(sqlite3_column_int(stmt, 1));
        payment->setAmount(sqlite3_column_double(stmt, 2));
        
        std::string methodStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        PaymentMethod method = PaymentMethod::CASH;
        if (methodStr == "CREDIT_CARD") method = PaymentMethod::CREDIT_CARD;
        else if (methodStr == "DEBIT_CARD") method = PaymentMethod::DEBIT_CARD;
        else if (methodStr == "MOBILE_PAYMENT") method = PaymentMethod::MOBILE_PAYMENT;
        else if (methodStr == "ONLINE_PAYMENT") method = PaymentMethod::ONLINE_PAYMENT;
        payment->setPaymentMethod(method);
        
        std::string statusStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        PaymentStatus paymentStatus = PaymentStatus::PENDING;
        if (statusStr == "COMPLETED") paymentStatus = PaymentStatus::COMPLETED;
        else if (statusStr == "FAILED") paymentStatus = PaymentStatus::FAILED;
        else if (statusStr == "REFUNDED") paymentStatus = PaymentStatus::REFUNDED;
        payment->setStatus(paymentStatus);
        
        payment->setTransactionId(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        payment->setPaymentDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        payments.push_back(payment);
    }
    
    sqlite3_finalize(stmt);
    return payments;
}

bool PaymentRepository::insert(Payment* payment) {
    if (!payment) {
        return false;
    }
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        return SimulationMode::insertMockPayment(payment);
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::string methodStr = "CASH";
    switch (payment->getPaymentMethod()) {
        case PaymentMethod::CREDIT_CARD: methodStr = "CREDIT_CARD"; break;
        case PaymentMethod::DEBIT_CARD: methodStr = "DEBIT_CARD"; break;
        case PaymentMethod::MOBILE_PAYMENT: methodStr = "MOBILE_PAYMENT"; break;
        case PaymentMethod::ONLINE_PAYMENT: methodStr = "ONLINE_PAYMENT"; break;
    }
    
    std::string statusStr = "PENDING";
    switch (payment->getStatus()) {
        case PaymentStatus::COMPLETED: statusStr = "COMPLETED"; break;
        case PaymentStatus::FAILED: statusStr = "FAILED"; break;
        case PaymentStatus::REFUNDED: statusStr = "REFUNDED"; break;
    }
    
    std::ostringstream query;
    query << "INSERT INTO payments (order_id, amount, payment_method, status, transaction_id) VALUES ("
          << payment->getOrderId() << ", "
          << payment->getAmount() << ", "
          << "'" << methodStr << "', "
          << "'" << statusStr << "', "
          << "'" << payment->getTransactionId() << "');";
    
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

bool PaymentRepository::update(Payment* payment) {
    if (!payment) {
        return false;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::string statusStr = "PENDING";
    switch (payment->getStatus()) {
        case PaymentStatus::COMPLETED: statusStr = "COMPLETED"; break;
        case PaymentStatus::FAILED: statusStr = "FAILED"; break;
        case PaymentStatus::REFUNDED: statusStr = "REFUNDED"; break;
    }
    
    std::ostringstream query;
    query << "UPDATE payments SET "
          << "status = '" << statusStr << "', "
          << "transaction_id = '" << payment->getTransactionId() << "' "
          << "WHERE id = " << payment->getId() << ";";
    
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

bool PaymentRepository::deleteById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "DELETE FROM payments WHERE id = " << id << ";";
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

