#ifndef DATABASEMIGRATION_H
#define DATABASEMIGRATION_H

#include <string>

class DatabaseMigration {
public:
    static bool createTables();
    static bool dropTables();
    static bool migrate();
    
private:
    static bool createUsersTable();
    static bool createRolesTable();
    static bool createPermissionsTable();
    static bool createRolePermissionsTable();
    static bool createAccessScopesTable();
    static bool createRoleAccessScopesTable();
    static bool createAdminActionLogsTable();
    static bool createChefsTable();
    static bool createMenuItemsTable();
    static bool createIngredientsTable();
    static bool createMenuItemIngredientsTable();
    static bool createTablesTable();
    static bool createReservationsTable();
    static bool createOrdersTable();
    static bool createOrderItemsTable();
    static bool createOrderQueueTable();
    static bool createPaymentsTable();
    static bool createEventsTable();
    static bool createStatisticsTable();
};

#endif // DATABASEMIGRATION_H

