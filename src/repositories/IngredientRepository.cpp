#include "../../include/repositories/IngredientRepository.h"
#include "../../include/database/DatabaseConnection.h"
#include "../../include/utils/Logger.h"
#include <sqlite3.h>
#include <sstream>

Ingredient* IngredientRepository::getById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, name, unit, quantity_in_stock, min_quantity, supplier, created_at, updated_at "
          << "FROM ingredients WHERE id = " << id << ";";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in IngredientRepository::getById");
        return nullptr;
    }
    
    Ingredient* ingredient = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        ingredient = new Ingredient();
        ingredient->setId(sqlite3_column_int(stmt, 0));
        ingredient->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        ingredient->setUnit(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        ingredient->setQuantityInStock(sqlite3_column_double(stmt, 3));
        ingredient->setMinQuantity(sqlite3_column_double(stmt, 4));
        ingredient->setSupplier(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        ingredient->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        ingredient->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
    }
    
    sqlite3_finalize(stmt);
    return ingredient;
}

Ingredient* IngredientRepository::getByName(const std::string& name) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return nullptr;
    }
    
    std::ostringstream query;
    query << "SELECT id, name, unit, quantity_in_stock, min_quantity, supplier, created_at, updated_at "
          << "FROM ingredients WHERE name = '" << name << "';";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in IngredientRepository::getByName");
        return nullptr;
    }
    
    Ingredient* ingredient = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        ingredient = new Ingredient();
        ingredient->setId(sqlite3_column_int(stmt, 0));
        ingredient->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        ingredient->setUnit(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        ingredient->setQuantityInStock(sqlite3_column_double(stmt, 3));
        ingredient->setMinQuantity(sqlite3_column_double(stmt, 4));
        ingredient->setSupplier(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        ingredient->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        ingredient->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
    }
    
    sqlite3_finalize(stmt);
    return ingredient;
}

std::vector<Ingredient*> IngredientRepository::getAll() {
    std::vector<Ingredient*> ingredients;
    if (!DatabaseConnection::getInstance().isConnected()) {
        return ingredients;
    }
    
    std::string query = "SELECT id, name, unit, quantity_in_stock, min_quantity, supplier, created_at, updated_at FROM ingredients;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in IngredientRepository::getAll");
        return ingredients;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Ingredient* ingredient = new Ingredient();
        ingredient->setId(sqlite3_column_int(stmt, 0));
        ingredient->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        ingredient->setUnit(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        ingredient->setQuantityInStock(sqlite3_column_double(stmt, 3));
        ingredient->setMinQuantity(sqlite3_column_double(stmt, 4));
        ingredient->setSupplier(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        ingredient->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        ingredient->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        ingredients.push_back(ingredient);
    }
    
    sqlite3_finalize(stmt);
    return ingredients;
}

std::vector<Ingredient*> IngredientRepository::getLowStock() {
    std::vector<Ingredient*> ingredients;
    if (!DatabaseConnection::getInstance().isConnected()) {
        return ingredients;
    }
    
    std::string query = "SELECT id, name, unit, quantity_in_stock, min_quantity, supplier, created_at, updated_at "
                       "FROM ingredients WHERE quantity_in_stock <= min_quantity;";
    
    sqlite3_stmt* stmt;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().error("Failed to prepare query in IngredientRepository::getLowStock");
        return ingredients;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Ingredient* ingredient = new Ingredient();
        ingredient->setId(sqlite3_column_int(stmt, 0));
        ingredient->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        ingredient->setUnit(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        ingredient->setQuantityInStock(sqlite3_column_double(stmt, 3));
        ingredient->setMinQuantity(sqlite3_column_double(stmt, 4));
        ingredient->setSupplier(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        ingredient->setCreatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        ingredient->setUpdatedAt(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        ingredients.push_back(ingredient);
    }
    
    sqlite3_finalize(stmt);
    return ingredients;
}

bool IngredientRepository::insert(Ingredient* ingredient) {
    if (!DatabaseConnection::getInstance().isConnected() || !ingredient) {
        return false;
    }
    
    std::ostringstream query;
    query << "INSERT INTO ingredients (name, unit, quantity_in_stock, min_quantity, supplier) VALUES ("
          << "'" << ingredient->getName() << "', "
          << "'" << ingredient->getUnit() << "', "
          << ingredient->getQuantityInStock() << ", "
          << ingredient->getMinQuantity() << ", "
          << "'" << ingredient->getSupplier() << "');";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("Ingredient inserted: " + ingredient->getName());
    }
    return result;
}

bool IngredientRepository::update(Ingredient* ingredient) {
    if (!DatabaseConnection::getInstance().isConnected() || !ingredient) {
        return false;
    }
    
    std::ostringstream query;
    query << "UPDATE ingredients SET "
          << "name = '" << ingredient->getName() << "', "
          << "unit = '" << ingredient->getUnit() << "', "
          << "quantity_in_stock = " << ingredient->getQuantityInStock() << ", "
          << "min_quantity = " << ingredient->getMinQuantity() << ", "
          << "supplier = '" << ingredient->getSupplier() << "', "
          << "updated_at = CURRENT_TIMESTAMP "
          << "WHERE id = " << ingredient->getId() << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("Ingredient updated: " + ingredient->getName());
    }
    return result;
}

bool IngredientRepository::deleteById(int id) {
    if (!DatabaseConnection::getInstance().isConnected()) {
        return false;
    }
    
    std::ostringstream query;
    query << "DELETE FROM ingredients WHERE id = " << id << ";";
    
    bool result = DatabaseConnection::getInstance().executeQuery(query.str());
    if (result) {
        Logger::getInstance().info("Ingredient deleted: " + std::to_string(id));
    }
    return result;
}

