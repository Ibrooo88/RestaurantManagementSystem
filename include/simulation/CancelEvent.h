#ifndef CANCELEVENT_H
#define CANCELEVENT_H

#include "Event.h"

class CancelEvent : public Event {
public:
    CancelEvent(int timestep, int orderId);
    
    void execute() override;
    std::string toString() const override;
};

#endif // CANCELEVENT_H

