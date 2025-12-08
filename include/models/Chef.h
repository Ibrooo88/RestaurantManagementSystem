#ifndef CHEF_H
#define CHEF_H

#include <string>
#include "../enums/ChefType.h"
#include "../enums/ChefStatus.h"

class Chef {
private:
    int id;
    int userId;
    ChefType chefType;
    ChefStatus status;
    int skillLevel;
    int currentWorkload;
    std::string specialization;
    std::string createdAt;

public:
    Chef();
    Chef(int id, int userId, ChefType chefType, ChefStatus status = ChefStatus::AVAILABLE,
         int skillLevel = 1, int currentWorkload = 0, const std::string& specialization = "");
    
    int getId() const;
    int getUserId() const;
    ChefType getChefType() const;
    ChefStatus getStatus() const;
    int getSkillLevel() const;
    int getCurrentWorkload() const;
    std::string getSpecialization() const;
    std::string getCreatedAt() const;
    
    void setId(int id);
    void setUserId(int userId);
    void setChefType(ChefType chefType);
    void setStatus(ChefStatus status);
    void setSkillLevel(int skillLevel);
    void setCurrentWorkload(int currentWorkload);
    void setSpecialization(const std::string& specialization);
    void setCreatedAt(const std::string& createdAt);
};

#endif // CHEF_H

