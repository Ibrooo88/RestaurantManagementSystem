#ifndef EVENT_H
#define EVENT_H

#include <string>

// Event types
enum class EventType {
    ARRIVAL,    // R - New order arrives
    CANCEL,     // X - Cancel a normal order
    PROMOTE     // P - Promote normal to VIP
};

// Abstract base class for all events
class Event {
protected:
    EventType type;
    int timestep;
    int orderId;

public:
    Event(EventType type, int timestep, int orderId);
    virtual ~Event() = default;
    
    EventType getType() const;
    int getTimestep() const;
    int getOrderId() const;
    
    virtual void execute() = 0;
    virtual std::string toString() const = 0;
};

#endif // EVENT_H

