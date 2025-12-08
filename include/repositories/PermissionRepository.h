#ifndef PERMISSIONREPOSITORY_H
#define PERMISSIONREPOSITORY_H

#include "../models/Permission.h"
#include <vector>
#include <string>

class PermissionRepository {
public:
    Permission* getById(int id);
    Permission* getByName(const std::string& name);
    std::vector<Permission*> getAll();
    bool insert(Permission* permission);
    bool update(Permission* permission);
    bool deleteById(int id);
};

#endif // PERMISSIONREPOSITORY_H

