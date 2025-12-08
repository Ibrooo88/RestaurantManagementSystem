#ifndef ADMINACTIONLOGREPOSITORY_H
#define ADMINACTIONLOGREPOSITORY_H

#include "../models/AdminActionLog.h"
#include <vector>
#include <string>

class AdminActionLogRepository {
public:
    AdminActionLog* getById(int id);
    std::vector<AdminActionLog*> getAll();
    std::vector<AdminActionLog*> getByUserId(int userId);
    std::vector<AdminActionLog*> getByActionType(const std::string& actionType);
    bool insert(AdminActionLog* log);
    bool deleteById(int id);
};

#endif // ADMINACTIONLOGREPOSITORY_H

