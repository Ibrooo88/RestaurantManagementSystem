#include "../../include/simulation/ArrivalEvent.h"
#include <sstream>

ArrivalEvent::ArrivalEvent(int timestep, int orderId, OrderType orderType, int orderSize, double money)
    : Event(EventType::ARRIVAL, timestep, orderId), orderType(orderType), orderSize(orderSize), money(money) {}

OrderType ArrivalEvent::getOrderType() const { return orderType; }
int ArrivalEvent::getOrderSize() const { return orderSize; }
double ArrivalEvent::getMoney() const { return money; }

void ArrivalEvent::execute() {
    // Execution handled by SimulationEngine
}

std::string ArrivalEvent::toString() const {
    std::ostringstream oss;
    oss << "ArrivalEvent[TS=" << timestep << ", ID=" << orderId 
        << ", Size=" << orderSize << ", Money=" << money << "]";
    return oss.str();
}

