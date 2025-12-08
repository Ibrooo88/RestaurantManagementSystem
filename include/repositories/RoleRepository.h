#ifndef ROLEREPOSITORY_H
#define ROLEREPOSITORY_H

#include "../models/Role.h"
#include <vector>
#include <string>

class RoleRepository {
public:
    Role* getById(int id);
    Role* getByName(const std::string& name);
    std::vector<Role*> getAll();
    bool insert(Role* role);
    bool update(Role* role);
    bool deleteById(int id);
};

#endif // ROLEREPOSITORY_H

