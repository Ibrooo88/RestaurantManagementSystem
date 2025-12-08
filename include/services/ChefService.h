#ifndef CHEFSERVICE_H
#define CHEFSERVICE_H

#include "../models/Chef.h"
#include "../enums/ChefStatus.h"
#include "../enums/ChefType.h"
#include <vector>

class ChefService {
public:
    static Chef* createChef(int userId, ChefType chefType, int skillLevel = 1,
                           const std::string& specialization = "");
    static bool updateChef(int chefId, ChefType chefType, ChefStatus status,
                          int skillLevel, const std::string& specialization);
    static bool deleteChef(int chefId);
    static std::vector<Chef*> getAvailableChefs();
    static std::vector<Chef*> getChefsByType(ChefType chefType);
    static Chef* getChefById(int chefId);
    static bool setChefStatus(int chefId, ChefStatus status);
    static bool assignOrderToChef(int chefId, int orderId);
    static Chef* findBestChefForOrder(int orderId);
};

#endif // CHEFSERVICE_H

