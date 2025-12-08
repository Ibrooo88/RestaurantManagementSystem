#include "../../include/controllers/ChefController.h"
#include "../../include/services/ChefService.h"
#include "../../include/repositories/ChefRepository.h"
#include "../../include/utils/Logger.h"

Chef* ChefController::createChef(int userId, ChefType chefType, int skillLevel,
                                 const std::string& specialization) {
    return ChefService::createChef(userId, chefType, skillLevel, specialization);
}

bool ChefController::updateChef(int chefId, ChefType chefType, ChefStatus status,
                                int skillLevel, const std::string& specialization) {
    return ChefService::updateChef(chefId, chefType, status, skillLevel, specialization);
}

bool ChefController::deleteChef(int chefId) {
    return ChefService::deleteChef(chefId);
}

std::vector<Chef*> ChefController::getAllChefs() {
    ChefRepository chefRepo;
    return chefRepo.getAll();
}

std::vector<Chef*> ChefController::getAvailableChefs() {
    return ChefService::getAvailableChefs();
}

std::vector<Chef*> ChefController::getChefsByType(ChefType chefType) {
    return ChefService::getChefsByType(chefType);
}

Chef* ChefController::getChefById(int chefId) {
    return ChefService::getChefById(chefId);
}

Chef* ChefController::getChefByUserId(int userId) {
    ChefRepository chefRepo;
    return chefRepo.getByUserId(userId);
}

bool ChefController::assignOrderToChef(int chefId, int orderId) {
    return ChefService::assignOrderToChef(chefId, orderId);
}

Chef* ChefController::findBestChefForOrder(int orderId) {
    return ChefService::findBestChefForOrder(orderId);
}

