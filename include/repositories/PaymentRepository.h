#ifndef PAYMENTREPOSITORY_H
#define PAYMENTREPOSITORY_H

#include "../models/Payment.h"
#include <vector>

class PaymentRepository {
public:
    Payment* getById(int id);
    std::vector<Payment*> getAll();
    std::vector<Payment*> getByOrderId(int orderId);
    bool insert(Payment* payment);
    bool update(Payment* payment);
    bool deleteById(int id);
};

#endif // PAYMENTREPOSITORY_H

