#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
private:
    int id;
    std::string name;
    std::string unit;
    double quantityInStock;
    double minQuantity;
    std::string supplier;
    std::string createdAt;
    std::string updatedAt;

public:
    Ingredient();
    Ingredient(int id, const std::string& name, const std::string& unit = "",
               double quantityInStock = 0.0, double minQuantity = 0.0);
    
    int getId() const;
    std::string getName() const;
    std::string getUnit() const;
    double getQuantityInStock() const;
    double getMinQuantity() const;
    std::string getSupplier() const;
    std::string getCreatedAt() const;
    std::string getUpdatedAt() const;
    
    void setId(int id);
    void setName(const std::string& name);
    void setUnit(const std::string& unit);
    void setQuantityInStock(double quantityInStock);
    void setMinQuantity(double minQuantity);
    void setSupplier(const std::string& supplier);
    void setCreatedAt(const std::string& createdAt);
    void setUpdatedAt(const std::string& updatedAt);
};

#endif // INGREDIENT_H

