#ifndef ACCESSSCOPREPOSITORY_H
#define ACCESSSCOPREPOSITORY_H

#include "../models/AccessScope.h"
#include <vector>
#include <string>

class AccessScopeRepository {
public:
    AccessScope* getById(int id);
    AccessScope* getByName(const std::string& name);
    std::vector<AccessScope*> getAll();
    bool insert(AccessScope* accessScope);
    bool update(AccessScope* accessScope);
    bool deleteById(int id);
};

#endif // ACCESSSCOPREPOSITORY_H

