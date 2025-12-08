#ifndef CHEFREPOSITORY_H
#define CHEFREPOSITORY_H

#include "../models/Chef.h"
#include "../enums/ChefStatus.h"
#include <vector>

class ChefRepository {
public:
    Chef* getById(int id);
    Chef* getByUserId(int userId);
    std::vector<Chef*> getAll();
    std::vector<Chef*> getByStatus(ChefStatus status);
    std::vector<Chef*> getAvailable();
    bool insert(Chef* chef);
    bool update(Chef* chef);
    bool deleteById(int id);
};

#endif // CHEFREPOSITORY_H

