#include "../../include/utils/PriorityCalculator.h"
#include "../enums/OrderType.h"

int PriorityCalculator::calculateOrderPriority(
    OrderType orderType,
    int waitingTimeMinutes,
    int numberOfItems,
    bool isVIP
) {
    int priority = 0;
    
    // Base priority by order type
    switch (orderType) {
        case OrderType::DINE_IN:
            priority = 50;
            break;
        case OrderType::TAKEAWAY:
            priority = 30;
            break;
        case OrderType::DELIVERY:
            priority = 40;
            break;
    }
    
    // Waiting time factor (more waiting = higher priority)
    priority += waitingTimeMinutes * 2;
    
    // Number of items factor (fewer items = slightly higher priority)
    priority += (10 - numberOfItems);
    
    // VIP factor
    if (isVIP) {
        priority += 20;
    }
    
    return priority;
}

int PriorityCalculator::calculateChefPriority(int currentWorkload, int skillLevel) {
    // Lower workload and higher skill = higher priority
    return (100 - currentWorkload) + (skillLevel * 10);
}

