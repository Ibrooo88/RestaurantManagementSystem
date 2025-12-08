#ifndef STATISTICSREPOSITORY_H
#define STATISTICSREPOSITORY_H

#include "../models/Statistics.h"
#include <vector>
#include <string>

class StatisticsRepository {
public:
    Statistics* getById(int id);
    Statistics* getByDate(const std::string& date);
    std::vector<Statistics*> getAll();
    std::vector<Statistics*> getByDateRange(const std::string& startDate, const std::string& endDate);
    bool insert(Statistics* statistics);
    bool update(Statistics* statistics);
    bool deleteById(int id);
};

#endif // STATISTICSREPOSITORY_H

