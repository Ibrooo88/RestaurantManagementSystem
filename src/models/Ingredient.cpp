#include "../../include/models/Ingredient.h"

Ingredient::Ingredient() : id(0), quantityInStock(0.0), minQuantity(0.0) {}

Ingredient::Ingredient(int id, const std::string& name, const std::string& unit,
                       double quantityInStock, double minQuantity)
    : id(id), name(name), unit(unit), quantityInStock(quantityInStock), minQuantity(minQuantity) {}

int Ingredient::getId() const { return id; }
std::string Ingredient::getName() const { return name; }
std::string Ingredient::getUnit() const { return unit; }
double Ingredient::getQuantityInStock() const { return quantityInStock; }
double Ingredient::getMinQuantity() const { return minQuantity; }
std::string Ingredient::getSupplier() const { return supplier; }
std::string Ingredient::getCreatedAt() const { return createdAt; }
std::string Ingredient::getUpdatedAt() const { return updatedAt; }

void Ingredient::setId(int id) { this->id = id; }
void Ingredient::setName(const std::string& name) { this->name = name; }
void Ingredient::setUnit(const std::string& unit) { this->unit = unit; }
void Ingredient::setQuantityInStock(double quantityInStock) { this->quantityInStock = quantityInStock; }
void Ingredient::setMinQuantity(double minQuantity) { this->minQuantity = minQuantity; }
void Ingredient::setSupplier(const std::string& supplier) { this->supplier = supplier; }
void Ingredient::setCreatedAt(const std::string& createdAt) { this->createdAt = createdAt; }
void Ingredient::setUpdatedAt(const std::string& updatedAt) { this->updatedAt = updatedAt; }

