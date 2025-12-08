#include "../../include/controllers/MenuController.h"
#include "../../include/services/MenuService.h"
#include "../../include/utils/Logger.h"

MenuItem* MenuController::createMenuItem(const std::string& name, double price,
                                        const std::string& category,
                                        const std::string& description,
                                        int preparationTime, bool isAvailable) {
    return MenuService::createMenuItem(name, price, category, description, preparationTime, isAvailable);
}

bool MenuController::updateMenuItem(int itemId, const std::string& name, double price,
                                   const std::string& category, const std::string& description,
                                   int preparationTime, bool isAvailable) {
    return MenuService::updateMenuItem(itemId, name, price, category, description, preparationTime, isAvailable);
}

bool MenuController::deleteMenuItem(int itemId) {
    return MenuService::deleteMenuItem(itemId);
}

std::vector<MenuItem*> MenuController::getAllMenuItems() {
    return MenuService::getAllMenuItems();
}

std::vector<MenuItem*> MenuController::getAvailableMenuItems() {
    return MenuService::getAvailableMenuItems();
}

std::vector<MenuItem*> MenuController::getMenuItemsByCategory(const std::string& category) {
    return MenuService::getMenuItemsByCategory(category);
}

MenuItem* MenuController::getMenuItemById(int itemId) {
    return MenuService::getMenuItemById(itemId);
}

bool MenuController::toggleMenuItemAvailability(int itemId) {
    return MenuService::toggleMenuItemAvailability(itemId);
}

