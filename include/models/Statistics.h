#ifndef STATISTICS_H
#define STATISTICS_H

#include <string>

class Statistics {
private:
    int id;
    std::string date;
    int totalOrders;
    double totalRevenue;
    int totalCustomers;
    double averageOrderValue;
    int mostPopularItemId;
    std::string createdAt;

public:
    Statistics();
    Statistics(int id, const std::string& date, int totalOrders = 0,
               double totalRevenue = 0.0, int totalCustomers = 0);
    
    int getId() const;
    std::string getDate() const;
    int getTotalOrders() const;
    double getTotalRevenue() const;
    int getTotalCustomers() const;
    double getAverageOrderValue() const;
    int getMostPopularItemId() const;
    std::string getCreatedAt() const;
    
    void setId(int id);
    void setDate(const std::string& date);
    void setTotalOrders(int totalOrders);
    void setTotalRevenue(double totalRevenue);
    void setTotalCustomers(int totalCustomers);
    void setAverageOrderValue(double averageOrderValue);
    void setMostPopularItemId(int mostPopularItemId);
    void setCreatedAt(const std::string& createdAt);
};

#endif // STATISTICS_H

