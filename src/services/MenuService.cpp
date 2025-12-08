#include "../../include/services/MenuService.h"
#include "../../include/repositories/MenuItemRepository.h"
#include "../../include/utils/Logger.h"

MenuItem* MenuService::createMenuItem(const std::string& name, double price,
                                     const std::string& category,
                                     const std::string& description,
                                     int preparationTime, bool isAvailable) {
    if (name.empty() || price <= 0) {
        Logger::getInstance().warning("Invalid menu item data");
        return nullptr;
    }
    
    MenuItem* item = new MenuItem();
    item->setName(name);
    item->setPrice(price);
    item->setCategory(category);
    item->setDescription(description);
    item->setPreparationTime(preparationTime);
    item->setIsAvailable(isAvailable);
    
    MenuItemRepository menuRepo;
    if (menuRepo.insert(item)) {
        Logger::getInstance().info("Menu item created: " + name);
        return item;
    }
    
    delete item;
    return nullptr;
}

bool MenuService::updateMenuItem(int itemId, const std::string& name, double price,
                                const std::string& category, const std::string& description,
                                int preparationTime, bool isAvailable) {
    MenuItemRepository menuRepo;
    MenuItem* item = menuRepo.getById(itemId);
    if (!item) {
        return false;
    }
    
    item->setName(name);
    item->setPrice(price);
    item->setCategory(category);
    item->setDescription(description);
    item->setPreparationTime(preparationTime);
    item->setIsAvailable(isAvailable);
    
    bool result = menuRepo.update(item);
    if (result) {
        Logger::getInstance().info("Menu item updated: " + name);
    }
    delete item;
    return result;
}

bool MenuService::deleteMenuItem(int itemId) {
    MenuItemRepository menuRepo;
    bool result = menuRepo.deleteById(itemId);
    if (result) {
        Logger::getInstance().info("Menu item deleted: " + std::to_string(itemId));
    }
    return result;
}

std::vector<MenuItem*> MenuService::getAllMenuItems() {
    MenuItemRepository menuRepo;
    return menuRepo.getAll();
}

std::vector<MenuItem*> MenuService::getAvailableMenuItems() {
    MenuItemRepository menuRepo;
    return menuRepo.getAvailable();
}

std::vector<MenuItem*> MenuService::getMenuItemsByCategory(const std::string& category) {
    MenuItemRepository menuRepo;
    return menuRepo.getByCategory(category);
}

MenuItem* MenuService::getMenuItemById(int itemId) {
    MenuItemRepository menuRepo;
    return menuRepo.getById(itemId);
}

bool MenuService::toggleMenuItemAvailability(int itemId) {
    MenuItemRepository menuRepo;
    MenuItem* item = menuRepo.getById(itemId);
    if (!item) {
        return false;
    }
    
    item->setIsAvailable(!item->getIsAvailable());
    bool result = menuRepo.update(item);
    delete item;
    return result;
}

