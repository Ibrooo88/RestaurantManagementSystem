#ifndef INGREDIENTREPOSITORY_H
#define INGREDIENTREPOSITORY_H

#include "../models/Ingredient.h"
#include <vector>
#include <string>

class IngredientRepository {
public:
    Ingredient* getById(int id);
    Ingredient* getByName(const std::string& name);
    std::vector<Ingredient*> getAll();
    std::vector<Ingredient*> getLowStock();
    bool insert(Ingredient* ingredient);
    bool update(Ingredient* ingredient);
    bool deleteById(int id);
};

#endif // INGREDIENTREPOSITORY_H

