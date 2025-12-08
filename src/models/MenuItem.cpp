#include "../../include/models/MenuItem.h"

MenuItem::MenuItem() : id(0), price(0.0), preparationTime(0), isAvailable(true) {}

MenuItem::MenuItem(int id, const std::string& name, double price, const std::string& category,
                   const std::string& description, int preparationTime, bool isAvailable)
    : id(id), name(name), description(description), price(price), category(category),
      preparationTime(preparationTime), isAvailable(isAvailable) {}

int MenuItem::getId() const { return id; }
std::string MenuItem::getName() const { return name; }
std::string MenuItem::getDescription() const { return description; }
double MenuItem::getPrice() const { return price; }
std::string MenuItem::getCategory() const { return category; }
int MenuItem::getPreparationTime() const { return preparationTime; }
bool MenuItem::getIsAvailable() const { return isAvailable; }
std::string MenuItem::getImagePath() const { return imagePath; }
std::string MenuItem::getCreatedAt() const { return createdAt; }
std::string MenuItem::getUpdatedAt() const { return updatedAt; }

void MenuItem::setId(int id) { this->id = id; }
void MenuItem::setName(const std::string& name) { this->name = name; }
void MenuItem::setDescription(const std::string& description) { this->description = description; }
void MenuItem::setPrice(double price) { this->price = price; }
void MenuItem::setCategory(const std::string& category) { this->category = category; }
void MenuItem::setPreparationTime(int preparationTime) { this->preparationTime = preparationTime; }
void MenuItem::setIsAvailable(bool isAvailable) { this->isAvailable = isAvailable; }
void MenuItem::setImagePath(const std::string& imagePath) { this->imagePath = imagePath; }
void MenuItem::setCreatedAt(const std::string& createdAt) { this->createdAt = createdAt; }
void MenuItem::setUpdatedAt(const std::string& updatedAt) { this->updatedAt = updatedAt; }

