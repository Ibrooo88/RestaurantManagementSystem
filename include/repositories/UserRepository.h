#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include "../models/User.h"
#include <vector>
#include <string>

class UserRepository {
public:
    User* getById(int id);
    User* getByUsername(const std::string& username);
    std::vector<User*> getAll();
    bool insert(User* user);
    bool update(User* user);
    bool deleteById(int id);
    bool authenticate(const std::string& username, const std::string& password);
};

#endif // USERREPOSITORY_H

