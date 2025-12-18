#include "../../include/database/DatabaseMigration.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include <vector>

bool DatabaseMigration::migrate() {
    Logger::getInstance().info("Starting database migration...");
    return createTables();
}

bool DatabaseMigration::createTables() {
    bool success = true;
    
    success &= createUsersTable();
    success &= createRolesTable();
    success &= createPermissionsTable();
    success &= createRolePermissionsTable();
    success &= createAccessScopesTable();
    success &= createRoleAccessScopesTable();
    success &= createAdminActionLogsTable();
    success &= createChefsTable();
    success &= createMenuItemsTable();
    success &= createIngredientsTable();
    success &= createMenuItemIngredientsTable();
    success &= createTablesTable();
    success &= createReservationsTable();
    success &= createReservationMenuItemsTable();
    success &= createOrdersTable();
    success &= createOrderItemsTable();
    success &= createOrderQueueTable();
    success &= createPaymentsTable();
    success &= createEventsTable();
    success &= createStatisticsTable();
    
    if (success) {
        Logger::getInstance().info("All tables created successfully");
    } else {
        Logger::getInstance().error("Some tables failed to create");
    }
    
    return success;
}

bool DatabaseMigration::createUsersTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL,
            email TEXT,
            full_name TEXT,
            role_id INTEGER,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP,
            updated_at TEXT DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (role_id) REFERENCES roles(id)
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createRolesTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS roles (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT UNIQUE NOT NULL,
            description TEXT,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createPermissionsTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS permissions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT UNIQUE NOT NULL,
            description TEXT,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createRolePermissionsTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS role_permissions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            role_id INTEGER NOT NULL,
            permission_id INTEGER NOT NULL,
            FOREIGN KEY (role_id) REFERENCES roles(id),
            FOREIGN KEY (permission_id) REFERENCES permissions(id),
            UNIQUE(role_id, permission_id)
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createAccessScopesTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS access_scopes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT UNIQUE NOT NULL,
            description TEXT,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createRoleAccessScopesTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS role_access_scopes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            role_id INTEGER NOT NULL,
            access_scope_id INTEGER NOT NULL,
            FOREIGN KEY (role_id) REFERENCES roles(id),
            FOREIGN KEY (access_scope_id) REFERENCES access_scopes(id),
            UNIQUE(role_id, access_scope_id)
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createAdminActionLogsTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS admin_action_logs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            action_type TEXT NOT NULL,
            entity_type TEXT,
            entity_id INTEGER,
            description TEXT,
            ip_address TEXT,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (user_id) REFERENCES users(id)
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createChefsTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS chefs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            chef_type TEXT NOT NULL,
            status TEXT NOT NULL DEFAULT 'AVAILABLE',
            skill_level INTEGER DEFAULT 1,
            current_workload INTEGER DEFAULT 0,
            specialization TEXT,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (user_id) REFERENCES users(id)
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createMenuItemsTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS menu_items (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            description TEXT,
            price REAL NOT NULL,
            category TEXT,
            preparation_time INTEGER,
            is_available BOOLEAN DEFAULT 1,
            image_path TEXT,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP,
            updated_at TEXT DEFAULT CURRENT_TIMESTAMP
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createIngredientsTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS ingredients (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT UNIQUE NOT NULL,
            unit TEXT,
            quantity_in_stock REAL DEFAULT 0,
            min_quantity REAL DEFAULT 0,
            supplier TEXT,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP,
            updated_at TEXT DEFAULT CURRENT_TIMESTAMP
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createMenuItemIngredientsTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS menu_item_ingredients (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            menu_item_id INTEGER NOT NULL,
            ingredient_id INTEGER NOT NULL,
            quantity_required REAL NOT NULL,
            FOREIGN KEY (menu_item_id) REFERENCES menu_items(id),
            FOREIGN KEY (ingredient_id) REFERENCES ingredients(id),
            UNIQUE(menu_item_id, ingredient_id)
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createTablesTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS tables (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            table_number INTEGER UNIQUE NOT NULL,
            capacity INTEGER NOT NULL,
            status TEXT NOT NULL DEFAULT 'AVAILABLE',
            location TEXT,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP,
            updated_at TEXT DEFAULT CURRENT_TIMESTAMP
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createReservationsTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS reservations (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            customer_name TEXT NOT NULL,
            customer_phone TEXT,
            customer_email TEXT,
            table_id INTEGER NOT NULL,
            reservation_date TEXT NOT NULL,
            reservation_time TEXT NOT NULL,
            number_of_guests INTEGER NOT NULL,
            status TEXT NOT NULL DEFAULT 'PENDING',
            special_requests TEXT,
            order_id INTEGER,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP,
            updated_at TEXT DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (table_id) REFERENCES tables(id),
            FOREIGN KEY (order_id) REFERENCES orders(id)
        );
    )";
    bool result = DatabaseConnection::getInstance().executeQuery(query);
    
    // Add order_id column if it doesn't exist (for existing databases)
    std::string alterQuery = "ALTER TABLE reservations ADD COLUMN order_id INTEGER REFERENCES orders(id);";
    DatabaseConnection::getInstance().executeQuery(alterQuery); // Ignore error if column exists
    
    return result;
}

bool DatabaseMigration::createReservationMenuItemsTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS reservation_menu_items (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            reservation_id INTEGER NOT NULL,
            menu_item_id INTEGER NOT NULL,
            quantity INTEGER NOT NULL DEFAULT 1,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (reservation_id) REFERENCES reservations(id) ON DELETE CASCADE,
            FOREIGN KEY (menu_item_id) REFERENCES menu_items(id),
            UNIQUE(reservation_id, menu_item_id)
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createOrdersTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS orders (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            order_number TEXT UNIQUE NOT NULL,
            table_id INTEGER,
            order_type TEXT NOT NULL,
            status TEXT NOT NULL DEFAULT 'PENDING',
            total_amount REAL DEFAULT 0,
            chef_id INTEGER,
            customer_name TEXT,
            customer_phone TEXT,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP,
            updated_at TEXT DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (table_id) REFERENCES tables(id),
            FOREIGN KEY (chef_id) REFERENCES chefs(id)
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createOrderItemsTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS order_items (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            order_id INTEGER NOT NULL,
            menu_item_id INTEGER NOT NULL,
            quantity INTEGER NOT NULL DEFAULT 1,
            price REAL NOT NULL,
            special_instructions TEXT,
            status TEXT NOT NULL DEFAULT 'PENDING',
            created_at TEXT DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (order_id) REFERENCES orders(id),
            FOREIGN KEY (menu_item_id) REFERENCES menu_items(id)
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createOrderQueueTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS order_queue (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            order_id INTEGER NOT NULL,
            priority INTEGER DEFAULT 0,
            estimated_completion_time TEXT,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (order_id) REFERENCES orders(id)
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createPaymentsTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS payments (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            order_id INTEGER NOT NULL,
            amount REAL NOT NULL,
            payment_method TEXT NOT NULL,
            status TEXT NOT NULL DEFAULT 'PENDING',
            transaction_id TEXT,
            payment_date TEXT DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (order_id) REFERENCES orders(id)
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createEventsTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS events (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            description TEXT,
            event_date TEXT NOT NULL,
            event_time TEXT,
            number_of_guests INTEGER,
            special_requirements TEXT,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::createStatisticsTable() {
    std::string query = R"(
        CREATE TABLE IF NOT EXISTS statistics (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            date TEXT NOT NULL,
            total_orders INTEGER DEFAULT 0,
            total_revenue REAL DEFAULT 0,
            total_customers INTEGER DEFAULT 0,
            average_order_value REAL DEFAULT 0,
            most_popular_item_id INTEGER,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (most_popular_item_id) REFERENCES menu_items(id)
        );
    )";
    return DatabaseConnection::getInstance().executeQuery(query);
}

bool DatabaseMigration::dropTables() {
    // Drop in reverse order to handle foreign keys
    std::vector<std::string> tables = {
        "statistics", "events", "payments", "order_queue", "order_items",
        "orders", "reservation_menu_items", "reservations", "tables", "menu_item_ingredients",
        "ingredients", "menu_items", "chefs", "admin_action_logs",
        "role_access_scopes", "access_scopes", "role_permissions",
        "permissions", "roles", "users"
    };
    
    bool success = true;
    for (const auto& table : tables) {
        std::string query = "DROP TABLE IF EXISTS " + table + ";";
        success &= DatabaseConnection::getInstance().executeQuery(query);
    }
    
    return success;
}

