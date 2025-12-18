#ifndef ARRIVALEVENT_H
#define ARRIVALEVENT_H

#include "Event.h"
#include "../enums/OrderType.h"

class ArrivalEvent : public Event {
private:
    OrderType orderType;
    int orderSize;
    double money;

public:
    ArrivalEvent(int timestep, int orderId, OrderType orderType, int orderSize, double money);
    
    OrderType getOrderType() const;
    int getOrderSize() const;
    double getMoney() const;
    
    void execute() override;
    std::string toString() const override;
};

#endif // ARRIVALEVENT_H

