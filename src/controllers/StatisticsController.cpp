#include "../../include/controllers/StatisticsController.h"
#include "../../include/services/StatisticsService.h"
#include "../../include/repositories/TableRepository.h"
#include "../../include/repositories/OrderRepository.h"
#include "../../include/enums/TableStatus.h"
#include "../../include/enums/OrderStatus.h"
#include "../../include/utils/Logger.h"

StatisticsData StatisticsController::getDailyStatistics(const std::string& date) {
    return StatisticsService::getDailyStatistics(date);
}

StatisticsData StatisticsController::getOverallStatistics() {
    return StatisticsService::getOverallStatistics();
}

double StatisticsController::getTotalRevenue() {
    return StatisticsService::getTotalRevenue();
}

double StatisticsController::getTotalRevenueByDateRange(const std::string& startDate, const std::string& endDate) {
    return StatisticsService::getTotalRevenueByDateRange(startDate, endDate);
}

int StatisticsController::getTotalOrders() {
    return StatisticsService::getTotalOrders();
}

int StatisticsController::getTotalOrdersByDate(const std::string& date) {
    return StatisticsService::getTotalOrdersByDate(date);
}

double StatisticsController::getAverageOrderValue() {
    return StatisticsService::getAverageOrderValue();
}

std::map<std::string, int> StatisticsController::getOrdersByStatus() {
    return StatisticsService::getOrdersByStatus();
}

int StatisticsController::getMostPopularMenuItem() {
    return StatisticsService::getMostPopularMenuItem();
}

int StatisticsController::getActiveTablesCount() {
    TableRepository tableRepo;
    auto tables = tableRepo.getAll();
    
    int count = 0;
    for (auto* table : tables) {
        if (table->getStatus() == TableStatus::OCCUPIED || 
            table->getStatus() == TableStatus::RESERVED) {
            count++;
        }
        delete table;
    }
    
    return count;
}

int StatisticsController::getPendingOrdersCount() {
    OrderRepository orderRepo;
    auto orders = orderRepo.getByStatus(OrderStatus::PENDING);
    int count = static_cast<int>(orders.size());
    
    for (auto* order : orders) {
        delete order;
    }
    
    return count;
}

