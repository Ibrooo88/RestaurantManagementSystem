#ifndef ACCESSSCOPE_H
#define ACCESSSCOPE_H

#include <string>

class AccessScope {
private:
    int id;
    std::string name;
    std::string description;
    std::string createdAt;

public:
    AccessScope();
    AccessScope(int id, const std::string& name, const std::string& description = "");
    
    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    std::string getCreatedAt() const;
    
    void setId(int id);
    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void setCreatedAt(const std::string& createdAt);
};

#endif // ACCESSSCOPE_H

