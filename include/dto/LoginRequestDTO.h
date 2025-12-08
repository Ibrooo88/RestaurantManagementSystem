#ifndef LOGINREQUESTDTO_H
#define LOGINREQUESTDTO_H

#include <string>

struct LoginRequestDTO {
    std::string username;
    std::string password;
    
    LoginRequestDTO() = default;
    LoginRequestDTO(const std::string& username, const std::string& password)
        : username(username), password(password) {}
};

#endif // LOGINREQUESTDTO_H

