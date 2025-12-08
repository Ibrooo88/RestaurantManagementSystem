#include "../../include/repositories/MenuItemRepository.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include "../../include/utils/SimulationMode.h"
#include <sqlite3.h>
#include <sstream>

MenuItem* MenuItemRepository::getById(int id) {
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto items = SimulationMode::getMockMenuItems();
        for (auto* item : items) {
            if (item->getId() == id) {
                return new MenuItem(*item);
            }
        }
        return nullptr;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, name, description, price, category, preparation_time, "
          << "is_available, image_path, created_at, updated_at "
          << "FROM menu_items WHERE id = " << id << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return nullptr;
    }
    
    MenuItem* item = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        item = new MenuItem();
        item->setId(sqlite3_column_int(stmt, 0));
        item->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        item->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        item->setPrice(sqlite3_column_double(stmt, 3));
        item->setCategory(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        item->setPreparationTime(sqlite3_column_int(stmt, 5));
        item->setIsAvailable(sqlite3_column_int(stmt, 6) == 1);
        item->setImagePath(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        item->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        item->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
    }
    
    sqlite3_finalize(stmt);
    return item;
}

std::vector<MenuItem*> MenuItemRepository::getAll() {
    std::vector<MenuItem*> items;
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto mockItems = SimulationMode::getMockMenuItems();
        for (auto* item : mockItems) {
            items.push_back(new MenuItem(*item));
        }
        return items;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return items;
    }
    
    std::string query = "SELECT id, name, description, price, category, preparation_time, "
                       "is_available, image_path, created_at, updated_at FROM menu_items;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return items;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        MenuItem* item = new MenuItem();
        item->setId(sqlite3_column_int(stmt, 0));
        item->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        item->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        item->setPrice(sqlite3_column_double(stmt, 3));
        item->setCategory(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        item->setPreparationTime(sqlite3_column_int(stmt, 5));
        item->setIsAvailable(sqlite3_column_int(stmt, 6) == 1);
        item->setImagePath(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        item->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        item->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        items.push_back(item);
    }
    
    sqlite3_finalize(stmt);
    return items;
}

std::vector<MenuItem*> MenuItemRepository::getByCategory(const std::string& category) {
    std::vector<MenuItem*> items;
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        auto mockItems = SimulationMode::getMockMenuItems();
        for (auto* item : mockItems) {
            if (item->getCategory() == category) {
                items.push_back(new MenuItem(*item));
            }
        }
        return items;
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return items;
    }
    
    std::ostringstream query;
    query << "SELECT id, name, description, price, category, preparation_time, "
          << "is_available, image_path, created_at, updated_at "
          << "FROM menu_items WHERE category = '" << category << "';";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return items;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        MenuItem* item = new MenuItem();
        item->setId(sqlite3_column_int(stmt, 0));
        item->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        item->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        item->setPrice(sqlite3_column_double(stmt, 3));
        item->setCategory(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        item->setPreparationTime(sqlite3_column_int(stmt, 5));
        item->setIsAvailable(sqlite3_column_int(stmt, 6) == 1);
        item->setImagePath(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        item->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        item->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        items.push_back(item);
    }
    
    sqlite3_finalize(stmt);
    return items;
}

std::vector<MenuItem*> MenuItemRepository::getAvailable() {
    std::vector<MenuItem*> allItems = getAll();
    std::vector<MenuItem*> availableItems;
    
    for (auto* item : allItems) {
        if (item->getIsAvailable()) {
            availableItems.push_back(item);
        } else {
            delete item;
        }
    }
    
    return availableItems;
}

bool MenuItemRepository::insert(MenuItem* menuItem) {
    if (!menuItem) {
        return false;
    }
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        return SimulationMode::insertMockMenuItem(menuItem);
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "INSERT INTO menu_items (name, description, price, category, preparation_time, is_available) "
          << "VALUES ('" << menuItem->getName() << "', '" << menuItem->getDescription() << "', "
          << menuItem->getPrice() << ", '" << menuItem->getCategory() << "', "
          << menuItem->getPreparationTime() << ", " << (menuItem->getIsAvailable() ? 1 : 0) << ");";
    
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

bool MenuItemRepository::update(MenuItem* menuItem) {
    if (!menuItem) {
        return false;
    }
    
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        return SimulationMode::updateMockMenuItem(menuItem->getId(), menuItem);
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "UPDATE menu_items SET "
          << "name = '" << menuItem->getName() << "', "
          << "description = '" << menuItem->getDescription() << "', "
          << "price = " << menuItem->getPrice() << ", "
          << "category = '" << menuItem->getCategory() << "', "
          << "preparation_time = " << menuItem->getPreparationTime() << ", "
          << "is_available = " << (menuItem->getIsAvailable() ? 1 : 0) << ", "
          << "updated_at = CURRENT_TIMESTAMP "
          << "WHERE id = " << menuItem->getId() << ";";
    
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

bool MenuItemRepository::deleteById(int id) {
    // Check simulation mode
    if (SimulationMode::isEnabled()) {
        return SimulationMode::deleteMockMenuItem(id);
    }
    
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "DELETE FROM menu_items WHERE id = " << id << ";";
    return DatabaseConnection::getInstance().executeQuery(query.str());
}

