#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include "../models/User.h"
#include "../dto/LoginRequestDTO.h"
#include <string>

class AuthService {
public:
    static User* login(const LoginRequestDTO& loginRequest);
    static bool logout(int userId);
    static bool hasPermission(int userId, const std::string& permission);
    static bool isAuthenticated(int userId);
};

#endif // AUTHSERVICE_H

