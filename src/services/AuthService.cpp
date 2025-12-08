#include "../../include/services/AuthService.h"
#include "../../include/repositories/UserRepository.h"
#include "../../include/utils/Logger.h"
#include "../../include/utils/SimulationMode.h"

User* AuthService::login(const LoginRequestDTO& loginRequest) {
    // Check if simulation mode is enabled
    if (SimulationMode::isEnabled()) {
        User* user = SimulationMode::authenticate(loginRequest.username, loginRequest.password);
        if (user) {
            Logger::getInstance().info("User logged in successfully (SIMULATION): " + loginRequest.username);
        } else {
            Logger::getInstance().warning("Login failed (SIMULATION): Invalid credentials - " + loginRequest.username);
        }
        return user;
    }
    
    // Normal database mode
    UserRepository userRepo;
    User* user = userRepo.getByUsername(loginRequest.username);
    
    if (!user) {
        Logger::getInstance().warning("Login failed: User not found - " + loginRequest.username);
        return nullptr;
    }
    
    if (user->getPassword() != loginRequest.password) {
        Logger::getInstance().warning("Login failed: Invalid password for user - " + loginRequest.username);
        delete user;
        return nullptr;
    }
    
    Logger::getInstance().info("User logged in successfully: " + loginRequest.username);
    return user;
}

bool AuthService::logout(int userId) {
    Logger::getInstance().info("User logged out: " + std::to_string(userId));
    return true;
}

bool AuthService::hasPermission(int userId, const std::string& permission) {
    // TODO: Implement permission checking logic
    return true;
}

bool AuthService::isAuthenticated(int userId) {
    UserRepository userRepo;
    User* user = userRepo.getById(userId);
    bool authenticated = (user != nullptr);
    if (user) delete user;
    return authenticated;
}

