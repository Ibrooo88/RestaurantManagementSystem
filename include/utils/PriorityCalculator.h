#ifndef PRIORITYCALCULATOR_H
#define PRIORITYCALCULATOR_H

#include <string>
#include "../enums/OrderType.h"

class PriorityCalculator {
public:
    static int calculateOrderPriority(
        OrderType orderType,
        int waitingTimeMinutes,
        int numberOfItems,
        bool isVIP = false
    );
    static int calculateChefPriority(int currentWorkload, int skillLevel);
};

#endif // PRIORITYCALCULATOR_H

