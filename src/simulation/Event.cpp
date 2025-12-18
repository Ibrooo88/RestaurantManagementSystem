#include "../../include/simulation/Event.h"

Event::Event(EventType type, int timestep, int orderId)
    : type(type), timestep(timestep), orderId(orderId) {}

EventType Event::getType() const { return type; }
int Event::getTimestep() const { return timestep; }
int Event::getOrderId() const { return orderId; }

