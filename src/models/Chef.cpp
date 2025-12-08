#include "../../include/models/Chef.h"

Chef::Chef() : id(0), userId(0), chefType(ChefType::LINE_CHEF),
              status(ChefStatus::AVAILABLE), skillLevel(1), currentWorkload(0) {}

Chef::Chef(int id, int userId, ChefType chefType, ChefStatus status,
           int skillLevel, int currentWorkload, const std::string& specialization)
    : id(id), userId(userId), chefType(chefType), status(status),
      skillLevel(skillLevel), currentWorkload(currentWorkload), specialization(specialization) {}

int Chef::getId() const { return id; }
int Chef::getUserId() const { return userId; }
ChefType Chef::getChefType() const { return chefType; }
ChefStatus Chef::getStatus() const { return status; }
int Chef::getSkillLevel() const { return skillLevel; }
int Chef::getCurrentWorkload() const { return currentWorkload; }
std::string Chef::getSpecialization() const { return specialization; }
std::string Chef::getCreatedAt() const { return createdAt; }

void Chef::setId(int id) { this->id = id; }
void Chef::setUserId(int userId) { this->userId = userId; }
void Chef::setChefType(ChefType chefType) { this->chefType = chefType; }
void Chef::setStatus(ChefStatus status) { this->status = status; }
void Chef::setSkillLevel(int skillLevel) { this->skillLevel = skillLevel; }
void Chef::setCurrentWorkload(int currentWorkload) { this->currentWorkload = currentWorkload; }
void Chef::setSpecialization(const std::string& specialization) { this->specialization = specialization; }
void Chef::setCreatedAt(const std::string& createdAt) { this->createdAt = createdAt; }

