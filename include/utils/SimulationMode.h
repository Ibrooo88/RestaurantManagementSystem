#ifndef SIMULATIONMODE_H
#define SIMULATIONMODE_H

#include <string>
#include <vector>
#include <map>
#include "../models/User.h"
#include "../models/MenuItem.h"
#include "../models/Table.h"
#include "../models/Order.h"
#include "../models/Reservation.h"
#include "../models/Payment.h"

class SimulationMode {
public:
    static bool isEnabled();
    static void setEnabled(bool enabled);
    
    // Mock data
    static std::vector<User*> getMockUsers();
    static std::vector<MenuItem*> getMockMenuItems();
    static std::vector<Table*> getMockTables();
    static std::vector<Order*> getMockOrders();
    static std::vector<Reservation*> getMockReservations();
    static std::vector<Payment*> getMockPayments();
    
    // Mock authentication
    static User* authenticate(const std::string& username, const std::string& password);
    
    // Mock repositories
    static bool insertMockOrder(Order* order);
    static bool updateMockOrder(int id, Order* order);
    static bool insertMockMenuItem(MenuItem* item);
    static bool updateMockMenuItem(int id, MenuItem* item);
    static bool deleteMockMenuItem(int id);
    static bool insertMockTable(Table* table);
    static bool updateMockTable(int id, Table* table);
    static bool deleteMockTable(int id);
    static bool insertMockReservation(Reservation* reservation);
    static bool updateMockReservation(int id, Reservation* reservation);
    static bool deleteMockReservation(int id);
    static bool insertMockPayment(Payment* payment);

private:
    static bool enabled;
    static std::vector<Order*> mockOrders;
    static std::vector<MenuItem*> mockMenuItems;
    static std::vector<Table*> mockTables;
    static std::vector<Reservation*> mockReservations;
    static std::vector<Payment*> mockPayments;
    static int nextOrderId;
    static int nextMenuItemId;
    static int nextTableId;
    static int nextReservationId;
    static int nextPaymentId;
};

#endif // SIMULATIONMODE_H

