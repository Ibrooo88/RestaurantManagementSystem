#ifndef PROMOTEEVENT_H
#define PROMOTEEVENT_H

#include "Event.h"

class PromoteEvent : public Event {
private:
    double extraMoney;

public:
    PromoteEvent(int timestep, int orderId, double extraMoney);
    
    double getExtraMoney() const;
    
    void execute() override;
    std::string toString() const override;
};

#endif // PROMOTEEVENT_H

