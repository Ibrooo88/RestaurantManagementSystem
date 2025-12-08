#ifndef MENUITEMDTO_H
#define MENUITEMDTO_H

#include <string>
#include <vector>

struct MenuItemDTO {
    int id;
    std::string name;
    std::string description;
    double price;
    std::string category;
    int preparationTime;
    bool isAvailable;
    std::string imagePath;
    std::vector<int> ingredientIds; // IDs of required ingredients
    
    MenuItemDTO() : id(0), price(0.0), preparationTime(0), isAvailable(true) {}
    MenuItemDTO(int id, const std::string& name, double price, const std::string& category = "")
        : id(id), name(name), price(price), category(category),
          preparationTime(0), isAvailable(true) {}
};

#endif // MENUITEMDTO_H

