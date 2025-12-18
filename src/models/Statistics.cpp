#include "../../include/models/Statistics.h"

Statistics::Statistics() : id(0), totalOrders(0), totalRevenue(0.0), 
    totalCustomers(0), averageOrderValue(0.0), mostPopularItemId(0) {}

Statistics::Statistics(int id, const std::string& date, int totalOrders,
                       double totalRevenue, int totalCustomers)
    : id(id), date(date), totalOrders(totalOrders), totalRevenue(totalRevenue),
      totalCustomers(totalCustomers), averageOrderValue(0.0), mostPopularItemId(0) {}

int Statistics::getId() const { return id; }
std::string Statistics::getDate() const { return date; }
int Statistics::getTotalOrders() const { return totalOrders; }
double Statistics::getTotalRevenue() const { return totalRevenue; }
int Statistics::getTotalCustomers() const { return totalCustomers; }
double Statistics::getAverageOrderValue() const { return averageOrderValue; }
int Statistics::getMostPopularItemId() const { return mostPopularItemId; }
std::string Statistics::getCreatedAt() const { return createdAt; }

void Statistics::setId(int id) { this->id = id; }
void Statistics::setDate(const std::string& date) { this->date = date; }
void Statistics::setTotalOrders(int totalOrders) { this->totalOrders = totalOrders; }
void Statistics::setTotalRevenue(double totalRevenue) { this->totalRevenue = totalRevenue; }
void Statistics::setTotalCustomers(int totalCustomers) { this->totalCustomers = totalCustomers; }
void Statistics::setAverageOrderValue(double averageOrderValue) { this->averageOrderValue = averageOrderValue; }
void Statistics::setMostPopularItemId(int mostPopularItemId) { this->mostPopularItemId = mostPopularItemId; }
void Statistics::setCreatedAt(const std::string& createdAt) { this->createdAt = createdAt; }

