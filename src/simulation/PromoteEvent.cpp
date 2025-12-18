#include "../../include/simulation/PromoteEvent.h"
#include <sstream>

PromoteEvent::PromoteEvent(int timestep, int orderId, double extraMoney)
    : Event(EventType::PROMOTE, timestep, orderId), extraMoney(extraMoney) {}

double PromoteEvent::getExtraMoney() const { return extraMoney; }

void PromoteEvent::execute() {
    // Execution handled by SimulationEngine
}

std::string PromoteEvent::toString() const {
    std::ostringstream oss;
    oss << "PromoteEvent[TS=" << timestep << ", ID=" << orderId 
        << ", ExtraMoney=" << extraMoney << "]";
    return oss.str();
}

