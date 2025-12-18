#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include <queue>
#include <vector>
#include <string>
#include <functional>
#include "../models/Order.h"
#include "../models/Chef.h"
#include "Event.h"

// Comparator for VIP priority queue (higher priority first)
struct VIPOrderComparator {
    bool operator()(Order* a, Order* b) const {
        return a->getPriority() < b->getPriority();
    }
};

class SimulationEngine {
private:
    int currentTimestep;
    int autoPromoteTimesteps;  // AutoP: timesteps before auto-promotion
    
    // Event queue (sorted by timestep)
    std::queue<Event*> eventQueue;
    
    // Order queues
    std::priority_queue<Order*, std::vector<Order*>, VIPOrderComparator> vipOrders;
    std::queue<Order*> veganOrders;
    std::queue<Order*> normalOrders;
    
    // Chef queues
    std::queue<Chef*> availableNormalChefs;
    std::queue<Chef*> availableVeganChefs;
    std::queue<Chef*> availableVIPChefs;
    std::vector<Chef*> busyChefs;
    std::vector<Chef*> breakChefs;
    
    // Completed orders
    std::vector<Order*> doneOrders;
    
    // All orders (for lookup)
    std::vector<Order*> allOrders;
    
    // Statistics
    int totalOrders;
    int normalOrderCount;
    int veganOrderCount;
    int vipOrderCount;
    int autoPromotedCount;
    double totalWaitingTime;
    double totalServiceTime;
    
    // Priority calculation weights
    double alpha;
    double beta;
    
    // Mode
    bool interactiveMode;

public:
    SimulationEngine();
    ~SimulationEngine();
    
    // Initialization
    void loadFromFile(const std::string& filename);
    void addChef(Chef* chef);
    void addEvent(Event* event);
    void setAutoPromoteTimesteps(int timesteps);
    void setInteractiveMode(bool interactive);
    void setPriorityWeights(double alpha, double beta);
    
    // Simulation control
    void run();
    void step();
    bool isFinished() const;
    
    // Event processing
    void processEvents();
    void processArrival(int orderId, OrderType type, int size, double money);
    void processCancel(int orderId);
    void processPromote(int orderId, double extraMoney);
    
    // Order assignment
    void assignOrders();
    void assignVIPOrders();
    void assignVeganOrders();
    void assignNormalOrders();
    Chef* findAvailableChef(OrderType orderType);
    
    // Order completion
    void checkCompletedOrders();
    void completeOrder(Chef* chef, Order* order);
    
    // Auto-promotion check
    void checkAutoPromotions();
    
    // Chef management
    void updateChefBreaks();
    
    // Output
    void writeOutput(const std::string& filename);
    void printStatistics();
    void printCurrentState();
    
    // Getters
    int getCurrentTimestep() const;
    int getTotalOrders() const;
    int getDoneOrdersCount() const;
    
    // Find order by ID
    Order* findOrderById(int orderId);
};

#endif // SIMULATIONENGINE_H

