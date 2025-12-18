#ifndef STATISTICSCONTROLLER_H
#define STATISTICSCONTROLLER_H

#include <string>
#include <map>
#include "../services/StatisticsService.h"

class StatisticsController {
public:
    static StatisticsData getDailyStatistics(const std::string& date);
    static StatisticsData getOverallStatistics();
    static double getTotalRevenue();
    static double getTotalRevenueByDateRange(const std::string& startDate, const std::string& endDate);
    static int getTotalOrders();
    static int getTotalOrdersByDate(const std::string& date);
    static double getAverageOrderValue();
    static std::map<std::string, int> getOrdersByStatus();
    static int getMostPopularMenuItem();
    static int getActiveTablesCount();
    static int getPendingOrdersCount();
};

#endif // STATISTICSCONTROLLER_H

