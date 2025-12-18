#include "../../include/database/DatabaseSeeder.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/database/DatabaseMigration.h"
#include "../../include/repositories/RoleRepository.h"
#include "../../include/repositories/PermissionRepository.h"
#include "../../include/repositories/AccessScopeRepository.h"
#include "../../include/repositories/UserRepository.h"
#include "../../include/repositories/ChefRepository.h"
#include "../../include/repositories/MenuItemRepository.h"
#include "../../include/repositories/IngredientRepository.h"
#include "../../include/repositories/TableRepository.h"
#include "../../include/models/Role.h"
#include "../../include/models/Permission.h"
#include "../../include/models/AccessScope.h"
#include "../../include/models/User.h"
#include "../../include/models/Chef.h"
#include "../../include/models/MenuItem.h"
#include "../../include/models/Ingredient.h"
#include "../../include/models/Table.h"
#include "../../include/enums/ChefType.h"
#include "../../include/enums/ChefStatus.h"
#include "../../include/enums/TableStatus.h"
#include "../../include/utils/Logger.h"
#include <vector>

bool DatabaseSeeder::seed() {
    Logger::getInstance().info("Starting database seeding...");
    
    bool success = true;
    success &= seedRoles();
    success &= seedPermissions();
    success &= seedAccessScopes();
    success &= seedUsers();
    success &= seedChefs();
    success &= seedMenuItems();
    success &= seedIngredients();
    success &= seedTables();
    
    if (success) {
        Logger::getInstance().info("Database seeding completed successfully");
    } else {
        Logger::getInstance().error("Database seeding completed with errors");
    }
    
    return success;
}

bool DatabaseSeeder::seedRoles() {
    Logger::getInstance().info("Seeding roles...");
    
    RoleRepository roleRepo;
    std::vector<std::pair<std::string, std::string>> roles = {
        {"ADMIN", "Administrator with full access"},
        {"MANAGER", "Manager with management privileges"},
        {"CHEF", "Chef with kitchen access"},
        {"WAITER", "Waiter with order management"},
        {"CASHIER", "Cashier with payment access"}
    };
    
    for (const auto& [name, description] : roles) {
        Role* existing = roleRepo.getByName(name);
        if (!existing) {
            Role* role = new Role(0, name, description);
            if (!roleRepo.insert(role)) {
                delete role;
                return false;
            }
            delete role;
        } else {
            delete existing;
        }
    }
    
    return true;
}

bool DatabaseSeeder::seedPermissions() {
    Logger::getInstance().info("Seeding permissions...");
    
    PermissionRepository permRepo;
    std::vector<std::pair<std::string, std::string>> permissions = {
        {"CREATE_ORDER", "Create new orders"},
        {"UPDATE_ORDER", "Update existing orders"},
        {"DELETE_ORDER", "Delete orders"},
        {"VIEW_ORDERS", "View all orders"},
        {"MANAGE_MENU", "Manage menu items"},
        {"MANAGE_USERS", "Manage users"},
        {"VIEW_STATISTICS", "View statistics"},
        {"MANAGE_RESERVATIONS", "Manage reservations"},
        {"PROCESS_PAYMENTS", "Process payments"}
    };
    
    for (const auto& [name, description] : permissions) {
        Permission* existing = permRepo.getByName(name);
        if (!existing) {
            Permission* perm = new Permission(0, name, description);
            if (!permRepo.insert(perm)) {
                delete perm;
                return false;
            }
            delete perm;
        } else {
            delete existing;
        }
    }
    
    return true;
}

bool DatabaseSeeder::seedAccessScopes() {
    Logger::getInstance().info("Seeding access scopes...");
    
    AccessScopeRepository scopeRepo;
    std::vector<std::pair<std::string, std::string>> scopes = {
        {"KITCHEN", "Kitchen area access"},
        {"DINING", "Dining area access"},
        {"ADMIN", "Administrative area access"},
        {"REPORTS", "Reports and statistics access"}
    };
    
    for (const auto& [name, description] : scopes) {
        AccessScope* existing = scopeRepo.getByName(name);
        if (!existing) {
            AccessScope* scope = new AccessScope(0, name, description);
            if (!scopeRepo.insert(scope)) {
                delete scope;
                return false;
            }
            delete scope;
        } else {
            delete existing;
        }
    }
    
    return true;
}

bool DatabaseSeeder::seedUsers() {
    Logger::getInstance().info("Seeding users...");
    
    UserRepository userRepo;
    RoleRepository roleRepo;
    
    Role* adminRole = roleRepo.getByName("ADMIN");
    if (!adminRole) {
        return false;
    }
    
    User* existing = userRepo.getByUsername("admin");
    if (!existing) {
        User* admin = new User();
        admin->setUsername("admin");
        admin->setPassword("admin123");
        admin->setEmail("admin@restaurant.com");
        admin->setFullName("Administrator");
        admin->setRoleId(adminRole->getId());
        
        if (!userRepo.insert(admin)) {
            delete admin;
            delete adminRole;
            return false;
        }
        delete admin;
    } else {
        delete existing;
    }
    
    delete adminRole;
    return true;
}

bool DatabaseSeeder::seedChefs() {
    Logger::getInstance().info("Seeding chefs...");
    
    ChefRepository chefRepo;
    UserRepository userRepo;
    RoleRepository roleRepo;
    
    Role* chefRole = roleRepo.getByName("CHEF");
    if (!chefRole) {
        return false;
    }
    
    User* chefUser = userRepo.getByUsername("chef1");
    if (!chefUser) {
        User* user = new User();
        user->setUsername("chef1");
        user->setPassword("chef123");
        user->setEmail("chef1@restaurant.com");
        user->setFullName("Head Chef");
        user->setRoleId(chefRole->getId());
        
        if (!userRepo.insert(user)) {
            delete user;
            delete chefRole;
            return false;
        }
        
        Chef* chef = new Chef();
        chef->setUserId(user->getId());
        chef->setChefType(ChefType::VIP_CHEF);
        chef->setStatus(ChefStatus::AVAILABLE);
        chef->setSkillLevel(5);
        chef->setCurrentWorkload(0);
        chef->setSpecialization("Main Courses");
        
        if (!chefRepo.insert(chef)) {
            delete chef;
            delete user;
            delete chefRole;
            return false;
        }
        
        delete chef;
        delete user;
    } else {
        delete chefUser;
    }
    
    delete chefRole;
    return true;
}

bool DatabaseSeeder::seedMenuItems() {
    Logger::getInstance().info("Seeding menu items...");
    
    MenuItemRepository menuRepo;
    
    std::vector<std::tuple<std::string, double, std::string, std::string, int>> items = {
        {"Grilled Chicken", 25.99, "Main Course", "Tender grilled chicken breast", 20},
        {"Caesar Salad", 12.99, "Salad", "Fresh romaine lettuce with caesar dressing", 10},
        {"Beef Steak", 35.99, "Main Course", "Premium beef steak", 25},
        {"Fish & Chips", 18.99, "Main Course", "Crispy fish with french fries", 15},
        {"Chocolate Cake", 8.99, "Dessert", "Rich chocolate cake", 5}
    };
    
    // Note: MenuItemRepository doesn't have getByName, so we'll just insert
    // In a real scenario, you'd want to check for duplicates
    for (const auto& [name, price, category, description, prepTime] : items) {
        MenuItem* item = new MenuItem(0, name, price, category, description, prepTime, true);
        if (!menuRepo.insert(item)) {
            delete item;
            return false;
        }
        delete item;
    }
    
    return true;
}

bool DatabaseSeeder::seedIngredients() {
    Logger::getInstance().info("Seeding ingredients...");
    
    IngredientRepository ingRepo;
    
    std::vector<std::tuple<std::string, std::string, double, double>> ingredients = {
        {"Chicken Breast", "kg", 50.0, 10.0},
        {"Beef", "kg", 30.0, 15.0},
        {"Fish", "kg", 40.0, 12.0},
        {"Lettuce", "kg", 20.0, 5.0},
        {"Flour", "kg", 100.0, 20.0}
    };
    
    for (const auto& [name, unit, quantity, minQty] : ingredients) {
        Ingredient* existing = ingRepo.getByName(name);
        if (!existing) {
            Ingredient* ing = new Ingredient(0, name, unit, quantity, minQty);
            if (!ingRepo.insert(ing)) {
                delete ing;
                return false;
            }
            delete ing;
        } else {
            delete existing;
        }
    }
    
    return true;
}

bool DatabaseSeeder::seedTables() {
    Logger::getInstance().info("Seeding tables...");
    
    TableRepository tableRepo;
    
    for (int i = 1; i <= 10; i++) {
        Table* existing = tableRepo.getByTableNumber(i);
        if (!existing) {
            Table* table = new Table();
            table->setTableNumber(i);
            table->setCapacity((i <= 5) ? 4 : 6);
            table->setStatus(TableStatus::AVAILABLE);
            table->setLocation((i <= 5) ? "Indoor" : "Outdoor");
            
            if (!tableRepo.insert(table)) {
                delete table;
                return false;
            }
            delete table;
        } else {
            delete existing;
        }
    }
    
    return true;
}

bool DatabaseSeeder::clearAll() {
    Logger::getInstance().warning("Clearing all seeded data...");
    return DatabaseMigration::dropTables() && DatabaseMigration::createTables();
}

