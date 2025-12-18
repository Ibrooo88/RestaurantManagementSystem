#include "../../include/simulation/CancelEvent.h"
#include <sstream>

CancelEvent::CancelEvent(int timestep, int orderId)
    : Event(EventType::CANCEL, timestep, orderId) {}

void CancelEvent::execute() {
    // Execution handled by SimulationEngine
}

std::string CancelEvent::toString() const {
    std::ostringstream oss;
    oss << "CancelEvent[TS=" << timestep << ", ID=" << orderId << "]";
    return oss.str();
}

