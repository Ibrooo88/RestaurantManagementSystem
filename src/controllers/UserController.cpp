#include "../../include/controllers/UserController.h"
#include "../../include/repositories/UserRepository.h"
#include "../../include/dto/LoginRequestDTO.h"
#include "../../include/utils/Logger.h"

User* UserController::login(const std::string& username, const std::string& password) {
    LoginRequestDTO loginRequest;
    loginRequest.username = username;
    loginRequest.password = password;
    
    return AuthService::login(loginRequest);
}

bool UserController::logout(int userId) {
    return AuthService::logout(userId);
}

bool UserController::isAuthenticated(int userId) {
    return AuthService::isAuthenticated(userId);
}

bool UserController::hasPermission(int userId, const std::string& permission) {
    return AuthService::hasPermission(userId, permission);
}

std::vector<User*> UserController::getAllUsers() {
    UserRepository userRepo;
    return userRepo.getAll();
}

User* UserController::getUserById(int userId) {
    UserRepository userRepo;
    return userRepo.getById(userId);
}

User* UserController::getUserByUsername(const std::string& username) {
    UserRepository userRepo;
    return userRepo.getByUsername(username);
}

