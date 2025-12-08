#ifndef STATISTICSCONTROLLER_H
#define STATISTICSCONTROLLER_H

#include <string>
#include <map>

struct StatisticsData {
    int totalOrders;
    double totalRevenue;
    int completedOrders;
    double averageOrderValue;
    int activeTables;
    int pendingOrders;
    std::map<std::string, int> ordersByStatus;
    std::map<std::string, double> revenueByDate;
};

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

