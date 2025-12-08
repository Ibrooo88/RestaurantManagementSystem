#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "../models/User.h"
#include "../services/AuthService.h"
#include <string>
#include <vector>

class UserController {
public:
    static User* login(const std::string& username, const std::string& password);
    static bool logout(int userId);
    static bool isAuthenticated(int userId);
    static bool hasPermission(int userId, const std::string& permission);
    static std::vector<User*> getAllUsers();
    static User* getUserById(int userId);
    static User* getUserByUsername(const std::string& username);
};

#endif // USERCONTROLLER_H

