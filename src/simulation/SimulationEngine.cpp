#include "../../include/simulation/SimulationEngine.h"
#include "../../include/simulation/ArrivalEvent.h"
#include "../../include/simulation/CancelEvent.h"
#include "../../include/simulation/PromoteEvent.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

SimulationEngine::SimulationEngine()
    : currentTimestep(0), autoPromoteTimesteps(10), totalOrders(0),
      normalOrderCount(0), veganOrderCount(0), vipOrderCount(0),
      autoPromotedCount(0), totalWaitingTime(0), totalServiceTime(0),
      alpha(1.0), beta(1.0), interactiveMode(false) {}

SimulationEngine::~SimulationEngine() {
    // Clean up events
    while (!eventQueue.empty()) {
        delete eventQueue.front();
        eventQueue.pop();
    }
    
    // Clean up orders
    for (auto order : allOrders) {
        delete order;
    }
    
    // Clean up chefs
    while (!availableNormalChefs.empty()) {
        delete availableNormalChefs.front();
        availableNormalChefs.pop();
    }
    while (!availableVeganChefs.empty()) {
        delete availableVeganChefs.front();
        availableVeganChefs.pop();
    }
    while (!availableVIPChefs.empty()) {
        delete availableVIPChefs.front();
        availableVIPChefs.pop();
    }
    for (auto chef : busyChefs) {
        delete chef;
    }
    for (auto chef : breakChefs) {
        delete chef;
    }
}

void SimulationEngine::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open input file " << filename << std::endl;
        return;
    }
    
    int normalChefs, veganChefs, vipChefs;
    int speedN, speedV, speedG;
    int ordersBeforeBreak;
    int breakN, breakV, breakG;
    int eventCount;
    
    // Read chef counts
    file >> normalChefs >> veganChefs >> vipChefs;
    
    // Read speeds
    file >> speedN >> speedV >> speedG;
    
    // Read break info
    file >> ordersBeforeBreak >> breakN >> breakV >> breakG;
    
    // Read auto-promote timesteps
    file >> autoPromoteTimesteps;
    
    // Read event count
    file >> eventCount;
    
    // Create chefs
    int chefId = 1;
    for (int i = 0; i < normalChefs; i++) {
        Chef* chef = new Chef(chefId++, ChefType::NORMAL_CHEF, speedN, ordersBeforeBreak, breakN);
        availableNormalChefs.push(chef);
    }
    for (int i = 0; i < veganChefs; i++) {
        Chef* chef = new Chef(chefId++, ChefType::VEGAN_CHEF, speedV, ordersBeforeBreak, breakV);
        availableVeganChefs.push(chef);
    }
    for (int i = 0; i < vipChefs; i++) {
        Chef* chef = new Chef(chefId++, ChefType::VIP_CHEF, speedG, ordersBeforeBreak, breakG);
        availableVIPChefs.push(chef);
    }
    
    // Read events
    for (int i = 0; i < eventCount; i++) {
        char eventType;
        file >> eventType;
        
        if (eventType == 'R') {
            char orderTypeChar;
            int ts, id, size;
            double money;
            file >> orderTypeChar >> ts >> id >> size >> money;
            
            OrderType orderType;
            if (orderTypeChar == 'N') orderType = OrderType::NORMAL;
            else if (orderTypeChar == 'V') orderType = OrderType::VEGAN;
            else orderType = OrderType::VIP;
            
            eventQueue.push(new ArrivalEvent(ts, id, orderType, size, money));
        }
        else if (eventType == 'X') {
            int ts, id;
            file >> ts >> id;
            eventQueue.push(new CancelEvent(ts, id));
        }
        else if (eventType == 'P') {
            int ts, id;
            double extraMoney;
            file >> ts >> id >> extraMoney;
            eventQueue.push(new PromoteEvent(ts, id, extraMoney));
        }
    }
    
    file.close();
}

void SimulationEngine::addChef(Chef* chef) {
    switch (chef->getChefType()) {
        case ChefType::NORMAL_CHEF:
            availableNormalChefs.push(chef);
            break;
        case ChefType::VEGAN_CHEF:
            availableVeganChefs.push(chef);
            break;
        case ChefType::VIP_CHEF:
            availableVIPChefs.push(chef);
            break;
    }
}

void SimulationEngine::addEvent(Event* event) {
    eventQueue.push(event);
}

void SimulationEngine::setAutoPromoteTimesteps(int timesteps) {
    autoPromoteTimesteps = timesteps;
}

void SimulationEngine::setInteractiveMode(bool interactive) {
    interactiveMode = interactive;
}

void SimulationEngine::setPriorityWeights(double a, double b) {
    alpha = a;
    beta = b;
}

void SimulationEngine::run() {
    while (!isFinished()) {
        step();
    }
    printStatistics();
}

void SimulationEngine::step() {
    currentTimestep++;
    
    if (interactiveMode) {
        printCurrentState();
    }
    
    // Process events for this timestep
    processEvents();
    
    // Check for auto-promotions
    checkAutoPromotions();
    
    // Update chef breaks
    updateChefBreaks();
    
    // Check completed orders
    checkCompletedOrders();
    
    // Assign orders to available chefs
    assignOrders();
}

bool SimulationEngine::isFinished() const {
    return eventQueue.empty() && 
           vipOrders.empty() && 
           veganOrders.empty() && 
           normalOrders.empty() &&
           busyChefs.empty();
}

void SimulationEngine::processEvents() {
    while (!eventQueue.empty() && eventQueue.front()->getTimestep() == currentTimestep) {
        Event* event = eventQueue.front();
        eventQueue.pop();
        
        switch (event->getType()) {
            case EventType::ARRIVAL: {
                ArrivalEvent* arrival = static_cast<ArrivalEvent*>(event);
                processArrival(arrival->getOrderId(), arrival->getOrderType(),
                              arrival->getOrderSize(), arrival->getMoney());
                break;
            }
            case EventType::CANCEL: {
                processCancel(event->getOrderId());
                break;
            }
            case EventType::PROMOTE: {
                PromoteEvent* promote = static_cast<PromoteEvent*>(event);
                processPromote(promote->getOrderId(), promote->getExtraMoney());
                break;
            }
        }
        
        delete event;
    }
}

void SimulationEngine::processArrival(int orderId, OrderType type, int size, double money) {
    Order* order = new Order(orderId, type, currentTimestep, size, money);
    allOrders.push_back(order);
    totalOrders++;
    
    switch (type) {
        case OrderType::VIP:
            order->calculatePriority(currentTimestep, alpha, beta);
            vipOrders.push(order);
            vipOrderCount++;
            break;
        case OrderType::VEGAN:
            veganOrders.push(order);
            veganOrderCount++;
            break;
        case OrderType::NORMAL:
            normalOrders.push(order);
            normalOrderCount++;
            break;
    }
}

void SimulationEngine::processCancel(int orderId) {
    // Can only cancel waiting Normal orders
    std::queue<Order*> temp;
    bool found = false;
    
    while (!normalOrders.empty()) {
        Order* order = normalOrders.front();
        normalOrders.pop();
        
        if (order->getId() == orderId && !found) {
            order->setStatus(OrderStatus::CANCELLED);
            found = true;
            // Don't add to done orders - just remove
        } else {
            temp.push(order);
        }
    }
    
    normalOrders = temp;
}

void SimulationEngine::processPromote(int orderId, double extraMoney) {
    // Find and promote Normal order to VIP
    std::queue<Order*> temp;
    
    while (!normalOrders.empty()) {
        Order* order = normalOrders.front();
        normalOrders.pop();
        
        if (order->getId() == orderId) {
            order->promoteToVIP(extraMoney);
            order->calculatePriority(currentTimestep, alpha, beta);
            vipOrders.push(order);
            normalOrderCount--;
            vipOrderCount++;
        } else {
            temp.push(order);
        }
    }
    
    normalOrders = temp;
}

void SimulationEngine::assignOrders() {
    assignVIPOrders();
    assignVeganOrders();
    assignNormalOrders();
}

void SimulationEngine::assignVIPOrders() {
    while (!vipOrders.empty()) {
        Chef* chef = findAvailableChef(OrderType::VIP);
        if (!chef) break;
        
        Order* order = vipOrders.top();
        vipOrders.pop();
        
        int serviceTime = chef->calculateServiceTime(order->getOrderSize());
        order->setAssignmentTimestep(currentTimestep);
        order->calculateWaitingTime();
        order->setServiceTime(serviceTime);
        order->calculateFinishTime();
        order->setChefId(chef->getId());
        order->setStatus(OrderStatus::IN_PROGRESS);
        
        chef->assignOrder(order->getId(), currentTimestep + serviceTime);
        busyChefs.push_back(chef);
    }
}

void SimulationEngine::assignVeganOrders() {
    while (!veganOrders.empty() && !availableVeganChefs.empty()) {
        Chef* chef = availableVeganChefs.front();
        availableVeganChefs.pop();
        
        Order* order = veganOrders.front();
        veganOrders.pop();
        
        int serviceTime = chef->calculateServiceTime(order->getOrderSize());
        order->setAssignmentTimestep(currentTimestep);
        order->calculateWaitingTime();
        order->setServiceTime(serviceTime);
        order->calculateFinishTime();
        order->setChefId(chef->getId());
        order->setStatus(OrderStatus::IN_PROGRESS);
        
        chef->assignOrder(order->getId(), currentTimestep + serviceTime);
        busyChefs.push_back(chef);
    }
}

void SimulationEngine::assignNormalOrders() {
    while (!normalOrders.empty()) {
        Chef* chef = findAvailableChef(OrderType::NORMAL);
        if (!chef) break;
        
        Order* order = normalOrders.front();
        normalOrders.pop();
        
        int serviceTime = chef->calculateServiceTime(order->getOrderSize());
        order->setAssignmentTimestep(currentTimestep);
        order->calculateWaitingTime();
        order->setServiceTime(serviceTime);
        order->calculateFinishTime();
        order->setChefId(chef->getId());
        order->setStatus(OrderStatus::IN_PROGRESS);
        
        chef->assignOrder(order->getId(), currentTimestep + serviceTime);
        busyChefs.push_back(chef);
    }
}

Chef* SimulationEngine::findAvailableChef(OrderType orderType) {
    Chef* chef = nullptr;
    
    switch (orderType) {
        case OrderType::VIP:
            // Prefer VIP, then Normal, then Vegan
            if (!availableVIPChefs.empty()) {
                chef = availableVIPChefs.front();
                availableVIPChefs.pop();
            } else if (!availableNormalChefs.empty()) {
                chef = availableNormalChefs.front();
                availableNormalChefs.pop();
            } else if (!availableVeganChefs.empty()) {
                chef = availableVeganChefs.front();
                availableVeganChefs.pop();
            }
            break;
            
        case OrderType::VEGAN:
            // Only Vegan chefs
            if (!availableVeganChefs.empty()) {
                chef = availableVeganChefs.front();
                availableVeganChefs.pop();
            }
            break;
            
        case OrderType::NORMAL:
            // Prefer Normal, then VIP
            if (!availableNormalChefs.empty()) {
                chef = availableNormalChefs.front();
                availableNormalChefs.pop();
            } else if (!availableVIPChefs.empty()) {
                chef = availableVIPChefs.front();
                availableVIPChefs.pop();
            }
            break;
    }
    
    return chef;
}

void SimulationEngine::checkCompletedOrders() {
    auto it = busyChefs.begin();
    while (it != busyChefs.end()) {
        Chef* chef = *it;
        
        if (chef->getOrderFinishTime() == currentTimestep) {
            Order* order = findOrderById(chef->getCurrentOrderId());
            if (order) {
                completeOrder(chef, order);
            }
            
            chef->completeOrder();
            
            // Check if chef needs break
            if (chef->getOrdersCompleted() >= chef->getOrdersBeforeBreak()) {
                chef->startBreak();
                breakChefs.push_back(chef);
            } else {
                // Return to available queue
                addChef(chef);
            }
            
            it = busyChefs.erase(it);
        } else {
            ++it;
        }
    }
}

void SimulationEngine::completeOrder(Chef* chef, Order* order) {
    order->setStatus(OrderStatus::COMPLETED);
    doneOrders.push_back(order);
    
    totalWaitingTime += order->getWaitingTime();
    totalServiceTime += order->getServiceTime();
}

void SimulationEngine::checkAutoPromotions() {
    std::queue<Order*> temp;
    
    while (!normalOrders.empty()) {
        Order* order = normalOrders.front();
        normalOrders.pop();
        
        int waitTime = currentTimestep - order->getRequestTimestep();
        if (waitTime >= autoPromoteTimesteps) {
            order->promoteToVIP(0);  // No extra money for auto-promotion
            order->calculatePriority(currentTimestep, alpha, beta);
            vipOrders.push(order);
            normalOrderCount--;
            vipOrderCount++;
            autoPromotedCount++;
        } else {
            temp.push(order);
        }
    }
    
    normalOrders = temp;
}

void SimulationEngine::updateChefBreaks() {
    auto it = breakChefs.begin();
    while (it != breakChefs.end()) {
        Chef* chef = *it;
        chef->updateBreak();
        
        if (chef->getRemainingBreakTime() <= 0) {
            chef->setOrdersCompleted(0);
            addChef(chef);
            it = breakChefs.erase(it);
        } else {
            ++it;
        }
    }
}

void SimulationEngine::writeOutput(const std::string& filename) {
    // Sort done orders by finish time
    std::sort(doneOrders.begin(), doneOrders.end(),
              [](Order* a, Order* b) { return a->getFinishTime() < b->getFinishTime(); });
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open output file " << filename << std::endl;
        return;
    }
    
    // Write each completed order
    for (Order* order : doneOrders) {
        file << order->getFinishTime() << " "
             << order->getId() << " "
             << order->getRequestTimestep() << " "
             << order->getWaitingTime() << " "
             << order->getServiceTime() << std::endl;
    }
    
    file << std::endl;
    
    // Write statistics
    int totalChefs = availableNormalChefs.size() + availableVeganChefs.size() + 
                     availableVIPChefs.size() + busyChefs.size() + breakChefs.size();
    
    file << "Orders: " << totalOrders << " [N:" << normalOrderCount 
         << ", V:" << veganOrderCount << ", G:" << vipOrderCount << "]" << std::endl;
    file << "Chefs: " << totalChefs << std::endl;
    file << "Avg Wait: " << (doneOrders.empty() ? 0 : totalWaitingTime / doneOrders.size()) << std::endl;
    file << "Avg Service: " << (doneOrders.empty() ? 0 : totalServiceTime / doneOrders.size()) << std::endl;
    file << "Auto-promoted: " << (totalOrders == 0 ? 0 : (autoPromotedCount * 100.0 / totalOrders)) << "%" << std::endl;
    
    file.close();
}

void SimulationEngine::printStatistics() {
    std::cout << "\n=== Simulation Complete ===" << std::endl;
    std::cout << "Total Orders: " << totalOrders << std::endl;
    std::cout << "  Normal: " << normalOrderCount << std::endl;
    std::cout << "  Vegan: " << veganOrderCount << std::endl;
    std::cout << "  VIP: " << vipOrderCount << std::endl;
    std::cout << "Completed: " << doneOrders.size() << std::endl;
    std::cout << "Avg Waiting Time: " << (doneOrders.empty() ? 0 : totalWaitingTime / doneOrders.size()) << std::endl;
    std::cout << "Avg Service Time: " << (doneOrders.empty() ? 0 : totalServiceTime / doneOrders.size()) << std::endl;
    std::cout << "Auto-promoted: " << autoPromotedCount << " (" 
              << (totalOrders == 0 ? 0 : (autoPromotedCount * 100.0 / totalOrders)) << "%)" << std::endl;
}

void SimulationEngine::printCurrentState() {
    std::cout << "\n--- Timestep " << currentTimestep << " ---" << std::endl;
    std::cout << "Waiting: VIP=" << vipOrders.size() 
              << " Vegan=" << veganOrders.size() 
              << " Normal=" << normalOrders.size() << std::endl;
    std::cout << "Busy Chefs: " << busyChefs.size() << std::endl;
    std::cout << "Chefs on Break: " << breakChefs.size() << std::endl;
    std::cout << "Completed: " << doneOrders.size() << std::endl;
}

int SimulationEngine::getCurrentTimestep() const { return currentTimestep; }
int SimulationEngine::getTotalOrders() const { return totalOrders; }
int SimulationEngine::getDoneOrdersCount() const { return doneOrders.size(); }

Order* SimulationEngine::findOrderById(int orderId) {
    for (Order* order : allOrders) {
        if (order->getId() == orderId) {
            return order;
        }
    }
    return nullptr;
}

