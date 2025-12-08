#include "../../include/utils/SimulationMode.h"
#include "../../include/models/User.h"
#include "../../include/models/MenuItem.h"
#include "../../include/models/Table.h"
#include "../../include/models/Order.h"
#include "../../include/models/Reservation.h"
#include "../../include/models/Payment.h"
#include "../../include/enums/OrderType.h"
#include "../../include/enums/OrderStatus.h"
#include "../../include/enums/TableStatus.h"
#include "../../include/enums/ReservationStatus.h"
#include "../../include/enums/PaymentMethod.h"
#include "../../include/enums/PaymentStatus.h"
#include <algorithm>

bool SimulationMode::enabled = false;
std::vector<Order*> SimulationMode::mockOrders;
std::vector<MenuItem*> SimulationMode::mockMenuItems;
std::vector<Table*> SimulationMode::mockTables;
std::vector<Reservation*> SimulationMode::mockReservations;
std::vector<Payment*> SimulationMode::mockPayments;
int SimulationMode::nextOrderId = 1;
int SimulationMode::nextMenuItemId = 1;
int SimulationMode::nextTableId = 11;
int SimulationMode::nextReservationId = 1;
int SimulationMode::nextPaymentId = 1;

bool SimulationMode::isEnabled() {
    return enabled;
}

void SimulationMode::setEnabled(bool enabled) {
    SimulationMode::enabled = enabled;
    
    // Initialize mock data when enabled
    if (enabled) {
        // Initialize mock menu items if empty
        if (mockMenuItems.empty()) {
            getMockMenuItems();
        }
        // Initialize mock tables if empty
        if (mockTables.empty()) {
            getMockTables();
        }
    }
}

std::vector<User*> SimulationMode::getMockUsers() {
    std::vector<User*> users;
    
    User* admin = new User(1, "admin", "admin123", "admin@restaurant.com", "Admin User", 1);
    users.push_back(admin);
    
    User* chef = new User(2, "chef", "chef123", "chef@restaurant.com", "Chef User", 2);
    users.push_back(chef);
    
    User* waiter = new User(3, "waiter", "waiter123", "waiter@restaurant.com", "Waiter User", 3);
    users.push_back(waiter);
    
    return users;
}

std::vector<MenuItem*> SimulationMode::getMockMenuItems() {
    if (!mockMenuItems.empty()) {
        return mockMenuItems;
    }
    
    mockMenuItems.push_back(new MenuItem(1, "Caesar Salad", 12.99, "Appetizer", "Fresh romaine lettuce with Caesar dressing", 10, true));
    mockMenuItems.push_back(new MenuItem(2, "Grilled Chicken", 18.99, "Main Course", "Tender grilled chicken breast", 25, true));
    mockMenuItems.push_back(new MenuItem(3, "Beef Steak", 24.99, "Main Course", "Premium beef steak", 30, true));
    mockMenuItems.push_back(new MenuItem(4, "Chocolate Cake", 8.99, "Dessert", "Rich chocolate cake", 5, true));
    mockMenuItems.push_back(new MenuItem(5, "Pasta Carbonara", 16.99, "Main Course", "Creamy pasta with bacon", 20, true));
    mockMenuItems.push_back(new MenuItem(6, "Fish & Chips", 15.99, "Main Course", "Battered fish with fries", 22, true));
    mockMenuItems.push_back(new MenuItem(7, "Soup of the Day", 6.99, "Appetizer", "Chef's special soup", 8, true));
    mockMenuItems.push_back(new MenuItem(8, "Tiramisu", 9.99, "Dessert", "Classic Italian dessert", 5, true));
    
    nextMenuItemId = 9;
    return mockMenuItems;
}

std::vector<Table*> SimulationMode::getMockTables() {
    if (!mockTables.empty()) {
        return mockTables;
    }
    
    for (int i = 1; i <= 10; ++i) {
        Table* table = new Table(i, i, (i <= 5) ? 4 : 6, TableStatus::AVAILABLE, "Main Hall");
        mockTables.push_back(table);
    }
    
    return mockTables;
}

std::vector<Order*> SimulationMode::getMockOrders() {
    return mockOrders;
}

User* SimulationMode::authenticate(const std::string& username, const std::string& password) {
    auto users = getMockUsers();
    for (auto* user : users) {
        if (user->getUsername() == username && user->getPassword() == password) {
            // Return a copy
            User* copy = new User(*user);
            // Clean up
            for (auto* u : users) delete u;
            return copy;
        }
    }
    
    // Clean up
    for (auto* u : users) delete u;
    return nullptr;
}

bool SimulationMode::insertMockOrder(Order* order) {
    if (!order) return false;
    
    order->setId(nextOrderId++);
    std::string orderNum = "ORD-SIM-" + std::to_string(order->getId());
    order->setOrderNumber(orderNum);
    
    mockOrders.push_back(new Order(*order));
    return true;
}

bool SimulationMode::updateMockOrder(int id, Order* order) {
    if (!order) return false;
    
    auto it = std::find_if(mockOrders.begin(), mockOrders.end(),
        [id](Order* o) { return o->getId() == id; });
    
    if (it != mockOrders.end()) {
        delete *it;
        *it = new Order(*order);
        (*it)->setId(id);
        return true;
    }
    
    return false;
}

bool SimulationMode::insertMockMenuItem(MenuItem* item) {
    if (!item) return false;
    
    item->setId(nextMenuItemId++);
    mockMenuItems.push_back(new MenuItem(*item));
    return true;
}

bool SimulationMode::updateMockMenuItem(int id, MenuItem* item) {
    if (!item) return false;
    
    auto it = std::find_if(mockMenuItems.begin(), mockMenuItems.end(),
        [id](MenuItem* m) { return m->getId() == id; });
    
    if (it != mockMenuItems.end()) {
        delete *it;
        *it = new MenuItem(*item);
        (*it)->setId(id);
        return true;
    }
    
    return false;
}

bool SimulationMode::deleteMockMenuItem(int id) {
    auto it = std::find_if(mockMenuItems.begin(), mockMenuItems.end(),
        [id](MenuItem* m) { return m->getId() == id; });
    
    if (it != mockMenuItems.end()) {
        delete *it;
        mockMenuItems.erase(it);
        return true;
    }
    
    return false;
}

bool SimulationMode::insertMockTable(Table* table) {
    if (!table) return false;
    
    table->setId(nextTableId++);
    mockTables.push_back(new Table(*table));
    return true;
}

bool SimulationMode::updateMockTable(int id, Table* table) {
    if (!table) return false;
    
    auto it = std::find_if(mockTables.begin(), mockTables.end(),
        [id](Table* t) { return t->getId() == id; });
    
    if (it != mockTables.end()) {
        delete *it;
        *it = new Table(*table);
        (*it)->setId(id);
        return true;
    }
    
    return false;
}

bool SimulationMode::deleteMockTable(int id) {
    auto it = std::find_if(mockTables.begin(), mockTables.end(),
        [id](Table* t) { return t->getId() == id; });
    
    if (it != mockTables.end()) {
        delete *it;
        mockTables.erase(it);
        return true;
    }
    
    return false;
}

bool SimulationMode::insertMockReservation(Reservation* reservation) {
    if (!reservation) return false;
    
    reservation->setId(nextReservationId++);
    mockReservations.push_back(new Reservation(*reservation));
    return true;
}

bool SimulationMode::updateMockReservation(int id, Reservation* reservation) {
    if (!reservation) return false;
    
    auto it = std::find_if(mockReservations.begin(), mockReservations.end(),
        [id](Reservation* r) { return r->getId() == id; });
    
    if (it != mockReservations.end()) {
        delete *it;
        *it = new Reservation(*reservation);
        (*it)->setId(id);
        return true;
    }
    
    return false;
}

bool SimulationMode::deleteMockReservation(int id) {
    auto it = std::find_if(mockReservations.begin(), mockReservations.end(),
        [id](Reservation* r) { return r->getId() == id; });
    
    if (it != mockReservations.end()) {
        delete *it;
        mockReservations.erase(it);
        return true;
    }
    
    return false;
}

bool SimulationMode::insertMockPayment(Payment* payment) {
    if (!payment) return false;
    
    payment->setId(nextPaymentId++);
    mockPayments.push_back(new Payment(*payment));
    return true;
}

std::vector<Reservation*> SimulationMode::getMockReservations() {
    return mockReservations;
}

std::vector<Payment*> SimulationMode::getMockPayments() {
    return mockPayments;
}

