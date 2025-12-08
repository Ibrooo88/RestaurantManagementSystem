#include "../../include/models/User.h"

User::User() : id(0), roleId(0) {}

User::User(int id, const std::string& username, const std::string& password,
           const std::string& email, const std::string& fullName, int roleId)
    : id(id), username(username), password(password), email(email),
      fullName(fullName), roleId(roleId) {}

int User::getId() const { return id; }
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
std::string User::getEmail() const { return email; }
std::string User::getFullName() const { return fullName; }
int User::getRoleId() const { return roleId; }
std::string User::getCreatedAt() const { return createdAt; }
std::string User::getUpdatedAt() const { return updatedAt; }

void User::setId(int id) { this->id = id; }
void User::setUsername(const std::string& username) { this->username = username; }
void User::setPassword(const std::string& password) { this->password = password; }
void User::setEmail(const std::string& email) { this->email = email; }
void User::setFullName(const std::string& fullName) { this->fullName = fullName; }
void User::setRoleId(int roleId) { this->roleId = roleId; }
void User::setCreatedAt(const std::string& createdAt) { this->createdAt = createdAt; }
void User::setUpdatedAt(const std::string& updatedAt) { this->updatedAt = updatedAt; }

