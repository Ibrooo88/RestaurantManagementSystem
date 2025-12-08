#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    int id;
    std::string username;
    std::string password;
    std::string email;
    std::string fullName;
    int roleId;
    std::string createdAt;
    std::string updatedAt;

public:
    User();
    User(int id, const std::string& username, const std::string& password,
         const std::string& email = "", const std::string& fullName = "", int roleId = 0);
    
    // Getters
    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getEmail() const;
    std::string getFullName() const;
    int getRoleId() const;
    std::string getCreatedAt() const;
    std::string getUpdatedAt() const;
    
    // Setters
    void setId(int id);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setEmail(const std::string& email);
    void setFullName(const std::string& fullName);
    void setRoleId(int roleId);
    void setCreatedAt(const std::string& createdAt);
    void setUpdatedAt(const std::string& updatedAt);
};

#endif // USER_H

