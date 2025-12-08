#include "../../include/services/ChefService.h"
#include "../../include/repositories/ChefRepository.h"
#include "../../include/repositories/OrderRepository.h"
#include "../../include/utils/Logger.h"
#include "../../include/utils/PriorityCalculator.h"
#include "../../include/enums/ChefStatus.h"
#include "../../include/enums/ChefType.h"
#include <algorithm>

Chef* ChefService::createChef(int userId, ChefType chefType, int skillLevel,
                              const std::string& specialization) {
    if (userId <= 0 || skillLevel < 1 || skillLevel > 10) {
        Logger::getInstance().warning("Invalid chef data");
        return nullptr;
    }
    
    Chef* chef = new Chef();
    chef->setUserId(userId);
    chef->setChefType(chefType);
    chef->setStatus(ChefStatus::AVAILABLE);
    chef->setSkillLevel(skillLevel);
    chef->setSpecialization(specialization);
    chef->setCurrentWorkload(0);
    
    ChefRepository chefRepo;
    if (chefRepo.insert(chef)) {
        Logger::getInstance().info("Chef created for user: " + std::to_string(userId));
        return chef;
    }
    
    delete chef;
    return nullptr;
}

bool ChefService::updateChef(int chefId, ChefType chefType, ChefStatus status,
                             int skillLevel, const std::string& specialization) {
    ChefRepository chefRepo;
    Chef* chef = chefRepo.getById(chefId);
    if (!chef) {
        return false;
    }
    
    chef->setChefType(chefType);
    chef->setStatus(status);
    chef->setSkillLevel(skillLevel);
    chef->setSpecialization(specialization);
    
    bool result = chefRepo.update(chef);
    if (result) {
        Logger::getInstance().info("Chef updated: " + std::to_string(chefId));
    }
    delete chef;
    return result;
}

bool ChefService::deleteChef(int chefId) {
    ChefRepository chefRepo;
    bool result = chefRepo.deleteById(chefId);
    if (result) {
        Logger::getInstance().info("Chef deleted: " + std::to_string(chefId));
    }
    return result;
}

std::vector<Chef*> ChefService::getAvailableChefs() {
    ChefRepository chefRepo;
    return chefRepo.getAvailable();
}

std::vector<Chef*> ChefService::getChefsByType(ChefType chefType) {
    ChefRepository chefRepo;
    auto allChefs = chefRepo.getAll();
    std::vector<Chef*> filteredChefs;
    
    for (auto* chef : allChefs) {
        if (chef->getChefType() == chefType) {
            filteredChefs.push_back(chef);
        } else {
            delete chef;
        }
    }
    
    return filteredChefs;
}

Chef* ChefService::getChefById(int chefId) {
    ChefRepository chefRepo;
    return chefRepo.getById(chefId);
}

bool ChefService::setChefStatus(int chefId, ChefStatus status) {
    ChefRepository chefRepo;
    Chef* chef = chefRepo.getById(chefId);
    if (!chef) {
        return false;
    }
    
    chef->setStatus(status);
    bool result = chefRepo.update(chef);
    delete chef;
    return result;
}

bool ChefService::assignOrderToChef(int chefId, int orderId) {
    ChefRepository chefRepo;
    Chef* chef = chefRepo.getById(chefId);
    if (!chef) {
        return false;
    }
    
    if (chef->getStatus() != ChefStatus::AVAILABLE) {
        Logger::getInstance().warning("Chef is not available: " + std::to_string(chefId));
        delete chef;
        return false;
    }
    
    // Update chef workload
    chef->setCurrentWorkload(chef->getCurrentWorkload() + 1);
    if (chef->getCurrentWorkload() > 0) {
        chef->setStatus(ChefStatus::BUSY);
    }
    chefRepo.update(chef);
    delete chef;
    
    // Assign order to chef
    OrderRepository orderRepo;
    Order* order = orderRepo.getById(orderId);
    if (!order) {
        return false;
    }
    
    order->setChefId(chefId);
    bool result = orderRepo.update(order);
    delete order;
    return result;
}

Chef* ChefService::findBestChefForOrder(int orderId) {
    OrderRepository orderRepo;
    Order* order = orderRepo.getById(orderId);
    if (!order) {
        return nullptr;
    }
    
    auto availableChefs = getAvailableChefs();
    if (availableChefs.empty()) {
        delete order;
        return nullptr;
    }
    
    // Find chef with lowest workload and highest skill
    Chef* bestChef = nullptr;
    int bestPriority = -1;
    
    for (auto* chef : availableChefs) {
        int priority = PriorityCalculator::calculateChefPriority(
            chef->getCurrentWorkload(), chef->getSkillLevel());
        
        if (priority > bestPriority) {
            bestPriority = priority;
            if (bestChef) delete bestChef;
            bestChef = new Chef(*chef);
        }
        delete chef;
    }
    
    delete order;
    return bestChef;
}

