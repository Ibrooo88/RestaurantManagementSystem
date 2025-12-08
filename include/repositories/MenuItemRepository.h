#ifndef MENUITEMREPOSITORY_H
#define MENUITEMREPOSITORY_H

#include "../models/MenuItem.h"
#include <vector>
#include <string>

class MenuItemRepository {
public:
    MenuItem* getById(int id);
    std::vector<MenuItem*> getAll();
    std::vector<MenuItem*> getByCategory(const std::string& category);
    std::vector<MenuItem*> getAvailable();
    bool insert(MenuItem* menuItem);
    bool update(MenuItem* menuItem);
    bool deleteById(int id);
};

#endif // MENUITEMREPOSITORY_H

