#ifndef MENUSERVICE_H
#define MENUSERVICE_H

#include "../models/MenuItem.h"
#include <vector>
#include <string>

class MenuService {
public:
    static MenuItem* createMenuItem(const std::string& name, double price, 
                                   const std::string& category = "",
                                   const std::string& description = "",
                                   int preparationTime = 0, bool isAvailable = true);
    static bool updateMenuItem(int itemId, const std::string& name, double price,
                              const std::string& category, const std::string& description,
                              int preparationTime, bool isAvailable);
    static bool deleteMenuItem(int itemId);
    static std::vector<MenuItem*> getAllMenuItems();
    static std::vector<MenuItem*> getAvailableMenuItems();
    static std::vector<MenuItem*> getMenuItemsByCategory(const std::string& category);
    static MenuItem* getMenuItemById(int itemId);
    static bool toggleMenuItemAvailability(int itemId);
};

#endif // MENUSERVICE_H

