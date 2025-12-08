#ifndef ROLECONTROLLER_H
#define ROLECONTROLLER_H

#include "../models/Role.h"
#include <vector>

class RoleController {
public:
    static std::vector<Role*> getAllRoles();
    static Role* getRoleById(int roleId);
    static Role* getRoleByName(const std::string& roleName);
    static bool hasPermission(int roleId, const std::string& permission);
};

#endif // ROLECONTROLLER_H

