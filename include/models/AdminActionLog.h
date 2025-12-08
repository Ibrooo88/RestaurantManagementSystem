#ifndef ADMINACTIONLOG_H
#define ADMINACTIONLOG_H

#include <string>

class AdminActionLog {
private:
    int id;
    int userId;
    std::string actionType;
    std::string entityType;
    int entityId;
    std::string description;
    std::string ipAddress;
    std::string createdAt;

public:
    AdminActionLog();
    AdminActionLog(int id, int userId, const std::string& actionType,
                   const std::string& entityType = "", int entityId = 0,
                   const std::string& description = "");
    
    int getId() const;
    int getUserId() const;
    std::string getActionType() const;
    std::string getEntityType() const;
    int getEntityId() const;
    std::string getDescription() const;
    std::string getIpAddress() const;
    std::string getCreatedAt() const;
    
    void setId(int id);
    void setUserId(int userId);
    void setActionType(const std::string& actionType);
    void setEntityType(const std::string& entityType);
    void setEntityId(int entityId);
    void setDescription(const std::string& description);
    void setIpAddress(const std::string& ipAddress);
    void setCreatedAt(const std::string& createdAt);
};

#endif // ADMINACTIONLOG_H

