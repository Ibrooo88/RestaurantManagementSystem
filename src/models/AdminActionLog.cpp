#include "../../include/models/AdminActionLog.h"

AdminActionLog::AdminActionLog() : id(0), userId(0), entityId(0) {}

AdminActionLog::AdminActionLog(int id, int userId, const std::string& actionType,
                               const std::string& entityType, int entityId, const std::string& description)
    : id(id), userId(userId), actionType(actionType), entityType(entityType),
      entityId(entityId), description(description) {}

int AdminActionLog::getId() const { return id; }
int AdminActionLog::getUserId() const { return userId; }
std::string AdminActionLog::getActionType() const { return actionType; }
std::string AdminActionLog::getEntityType() const { return entityType; }
int AdminActionLog::getEntityId() const { return entityId; }
std::string AdminActionLog::getDescription() const { return description; }
std::string AdminActionLog::getIpAddress() const { return ipAddress; }
std::string AdminActionLog::getCreatedAt() const { return createdAt; }

void AdminActionLog::setId(int id) { this->id = id; }
void AdminActionLog::setUserId(int userId) { this->userId = userId; }
void AdminActionLog::setActionType(const std::string& actionType) { this->actionType = actionType; }
void AdminActionLog::setEntityType(const std::string& entityType) { this->entityType = entityType; }
void AdminActionLog::setEntityId(int entityId) { this->entityId = entityId; }
void AdminActionLog::setDescription(const std::string& description) { this->description = description; }
void AdminActionLog::setIpAddress(const std::string& ipAddress) { this->ipAddress = ipAddress; }
void AdminActionLog::setCreatedAt(const std::string& createdAt) { this->createdAt = createdAt; }

