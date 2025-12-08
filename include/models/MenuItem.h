#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>

class MenuItem {
private:
    int id;
    std::string name;
    std::string description;
    double price;
    std::string category;
    int preparationTime;
    bool isAvailable;
    std::string imagePath;
    std::string createdAt;
    std::string updatedAt;

public:
    MenuItem();
    MenuItem(int id, const std::string& name, double price, const std::string& category = "",
             const std::string& description = "", int preparationTime = 0, bool isAvailable = true);
    
    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    double getPrice() const;
    std::string getCategory() const;
    int getPreparationTime() const;
    bool getIsAvailable() const;
    std::string getImagePath() const;
    std::string getCreatedAt() const;
    std::string getUpdatedAt() const;
    
    void setId(int id);
    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void setPrice(double price);
    void setCategory(const std::string& category);
    void setPreparationTime(int preparationTime);
    void setIsAvailable(bool isAvailable);
    void setImagePath(const std::string& imagePath);
    void setCreatedAt(const std::string& createdAt);
    void setUpdatedAt(const std::string& updatedAt);
};

#endif // MENUITEM_H

