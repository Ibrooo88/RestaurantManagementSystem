#include "../../include/services/StatisticsService.h"
#include "../../include/repositories/OrderRepository.h"
#include "../../include/repositories/PaymentRepository.h"
#include "../../include/repositories/TableRepository.h"
#include "../../include/repositories/MenuItemRepository.h"
#include "../../include/repositories/OrderItemRepository.h"
#include "../../include/enums/OrderStatus.h"
#include "../../include/enums/PaymentStatus.h"
#include "../../include/enums/TableStatus.h"
#include "../../include/utils/TimeUtils.h"
#include <algorithm>
#include <map>

StatisticsData StatisticsService::getDailyStatistics(const std::string& date) {
    StatisticsData stats;
    stats.totalOrders = 0;
    stats.totalRevenue = 0.0;
    stats.completedOrders = 0;
    stats.averageOrderValue = 0.0;
    stats.activeTables = 0;
    stats.pendingOrders = 0;
    
    OrderRepository orderRepo;
    PaymentRepository paymentRepo;
    TableRepository tableRepo;
    
    auto allOrders = orderRepo.getAll();
    auto allPayments = paymentRepo.getAll();
    auto allTables = tableRepo.getAll();
    
    // Calculate orders statistics
    for (auto* order : allOrders) {
        std::string orderDate = order->getCreatedAt().substr(0, 10);
        if (orderDate == date) {
            stats.totalOrders++;
            
            if (order->getStatus() == OrderStatus::COMPLETED) {
                stats.completedOrders++;
            } else if (order->getStatus() == OrderStatus::PENDING) {
                stats.pendingOrders++;
            }
            
            std::string statusStr = "PENDING";
            switch (order->getStatus()) {
                case OrderStatus::IN_PROGRESS: statusStr = "IN_PROGRESS"; break;
                case OrderStatus::READY: statusStr = "READY"; break;
                case OrderStatus::SERVED: statusStr = "SERVED"; break;
                case OrderStatus::COMPLETED: statusStr = "COMPLETED"; break;
                case OrderStatus::CANCELLED: statusStr = "CANCELLED"; break;
            }
            stats.ordersByStatus[statusStr]++;
        }
        delete order;
    }
    
    // Calculate revenue
    for (auto* payment : allPayments) {
        std::string paymentDate = payment->getPaymentDate().substr(0, 10);
        if (paymentDate == date && payment->getStatus() == PaymentStatus::COMPLETED) {
            stats.totalRevenue += payment->getAmount();
        }
        delete payment;
    }
    
    // Calculate active tables
    for (auto* table : allTables) {
        if (table->getStatus() == TableStatus::OCCUPIED || 
            table->getStatus() == TableStatus::RESERVED) {
            stats.activeTables++;
        }
        delete table;
    }
    
    // Calculate average order value
    if (stats.totalOrders > 0) {
        stats.averageOrderValue = stats.totalRevenue / stats.totalOrders;
    }
    
    return stats;
}

StatisticsData StatisticsService::getOverallStatistics() {
    StatisticsData stats;
    stats.totalOrders = 0;
    stats.totalRevenue = 0.0;
    stats.completedOrders = 0;
    stats.averageOrderValue = 0.0;
    stats.activeTables = 0;
    stats.pendingOrders = 0;
    
    OrderRepository orderRepo;
    PaymentRepository paymentRepo;
    TableRepository tableRepo;
    
    auto allOrders = orderRepo.getAll();
    auto allPayments = paymentRepo.getAll();
    auto allTables = tableRepo.getAll();
    
    // Calculate orders statistics
    for (auto* order : allOrders) {
        stats.totalOrders++;
        
        if (order->getStatus() == OrderStatus::COMPLETED) {
            stats.completedOrders++;
        } else if (order->getStatus() == OrderStatus::PENDING) {
            stats.pendingOrders++;
        }
        
        std::string statusStr = "PENDING";
        switch (order->getStatus()) {
            case OrderStatus::IN_PROGRESS: statusStr = "IN_PROGRESS"; break;
            case OrderStatus::READY: statusStr = "READY"; break;
            case OrderStatus::SERVED: statusStr = "SERVED"; break;
            case OrderStatus::COMPLETED: statusStr = "COMPLETED"; break;
            case OrderStatus::CANCELLED: statusStr = "CANCELLED"; break;
        }
        stats.ordersByStatus[statusStr]++;
        delete order;
    }
    
    // Calculate revenue
    for (auto* payment : allPayments) {
        if (payment->getStatus() == PaymentStatus::COMPLETED) {
            stats.totalRevenue += payment->getAmount();
        }
        delete payment;
    }
    
    // Calculate active tables
    for (auto* table : allTables) {
        if (table->getStatus() == TableStatus::OCCUPIED || 
            table->getStatus() == TableStatus::RESERVED) {
            stats.activeTables++;
        }
        delete table;
    }
    
    // Calculate average order value
    if (stats.totalOrders > 0) {
        stats.averageOrderValue = stats.totalRevenue / stats.totalOrders;
    }
    
    return stats;
}

double StatisticsService::getTotalRevenue() {
    PaymentRepository paymentRepo;
    auto payments = paymentRepo.getAll();
    
    double total = 0.0;
    for (auto* payment : payments) {
        if (payment->getStatus() == PaymentStatus::COMPLETED) {
            total += payment->getAmount();
        }
        delete payment;
    }
    
    return total;
}

double StatisticsService::getTotalRevenueByDateRange(const std::string& startDate, const std::string& endDate) {
    PaymentRepository paymentRepo;
    auto payments = paymentRepo.getAll();
    
    double total = 0.0;
    for (auto* payment : payments) {
        std::string paymentDate = payment->getPaymentDate().substr(0, 10);
        if (paymentDate >= startDate && paymentDate <= endDate && 
            payment->getStatus() == PaymentStatus::COMPLETED) {
            total += payment->getAmount();
        }
        delete payment;
    }
    
    return total;
}

int StatisticsService::getTotalOrders() {
    OrderRepository orderRepo;
    auto orders = orderRepo.getAll();
    int count = orders.size();
    
    for (auto* order : orders) {
        delete order;
    }
    
    return count;
}

int StatisticsService::getTotalOrdersByDate(const std::string& date) {
    OrderRepository orderRepo;
    auto orders = orderRepo.getAll();
    
    int count = 0;
    for (auto* order : orders) {
        std::string orderDate = order->getCreatedAt().substr(0, 10);
        if (orderDate == date) {
            count++;
        }
        delete order;
    }
    
    return count;
}

double StatisticsService::getAverageOrderValue() {
    auto stats = getOverallStatistics();
    return stats.averageOrderValue;
}

std::map<std::string, int> StatisticsService::getOrdersByStatus() {
    auto stats = getOverallStatistics();
    return stats.ordersByStatus;
}

int StatisticsService::getMostPopularMenuItem() {
    OrderItemRepository orderItemRepo;
    MenuItemRepository menuItemRepo;
    OrderRepository orderRepo;
    
    auto orders = orderRepo.getAll();
    std::map<int, int> itemCount; // menuItemId -> count
    
    for (auto* order : orders) {
        auto orderItems = orderItemRepo.getByOrderId(order->getId());
        for (auto* item : orderItems) {
            itemCount[item->getMenuItemId()] += item->getQuantity();
            delete item;
        }
        delete order;
    }
    
    if (itemCount.empty()) {
        return 0;
    }
    
    // Find most popular item
    auto maxElement = std::max_element(itemCount.begin(), itemCount.end(),
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second < b.second;
        });
    
    return maxElement->first;
}

