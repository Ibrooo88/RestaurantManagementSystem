#ifndef STATISTICSDTO_H
#define STATISTICSDTO_H

#include <string>
#include <vector>

struct StatisticsDTO {
    std::string date;
    int totalOrders;
    double totalRevenue;
    int totalCustomers;
    double averageOrderValue;
    int mostPopularItemId;
    std::string mostPopularItemName;
    
    StatisticsDTO() : totalOrders(0), totalRevenue(0.0), totalCustomers(0),
                     averageOrderValue(0.0), mostPopularItemId(0) {}
    
    StatisticsDTO(const std::string& date) : date(date), totalOrders(0),
                                            totalRevenue(0.0), totalCustomers(0),
                                            averageOrderValue(0.0), mostPopularItemId(0) {}
};

struct StatisticsSummaryDTO {
    std::string startDate;
    std::string endDate;
    int totalOrders;
    double totalRevenue;
    int totalCustomers;
    double averageOrderValue;
    std::vector<std::pair<int, int>> topMenuItems; // itemId -> count
    std::vector<StatisticsDTO> dailyStats;
    
    StatisticsSummaryDTO() : totalOrders(0), totalRevenue(0.0), totalCustomers(0),
                            averageOrderValue(0.0) {}
};

#endif // STATISTICSDTO_H

