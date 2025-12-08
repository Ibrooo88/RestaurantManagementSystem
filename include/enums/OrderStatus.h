#ifndef ORDERSTATUS_H
#define ORDERSTATUS_H

enum class OrderStatus {
    PENDING,
    IN_PROGRESS,
    READY,
    SERVED,
    CANCELLED,
    COMPLETED
};

#endif // ORDERSTATUS_H

