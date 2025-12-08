#ifndef ROLE_H
#define ROLE_H

#include <string>

class Role {
private:
    int id;
    std::string name;
    std::string description;
    std::string createdAt;

public:
    Role();
    Role(int id, const std::string& name, const std::string& description = "");
    
    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    std::string getCreatedAt() const;
    
    void setId(int id);
    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void setCreatedAt(const std::string& createdAt);
};

#endif // ROLE_H

