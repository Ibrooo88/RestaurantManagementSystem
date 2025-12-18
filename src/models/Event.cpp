#include "../../include/models/Event.h"

Event::Event() : id(0), numberOfGuests(0) {}

Event::Event(int id, const std::string& name, const std::string& eventDate,
             const std::string& eventTime, int numberOfGuests)
    : id(id), name(name), eventDate(eventDate), eventTime(eventTime), numberOfGuests(numberOfGuests) {}

int Event::getId() const { return id; }
std::string Event::getName() const { return name; }
std::string Event::getDescription() const { return description; }
std::string Event::getEventDate() const { return eventDate; }
std::string Event::getEventTime() const { return eventTime; }
int Event::getNumberOfGuests() const { return numberOfGuests; }
std::string Event::getSpecialRequirements() const { return specialRequirements; }
std::string Event::getCreatedAt() const { return createdAt; }

void Event::setId(int id) { this->id = id; }
void Event::setName(const std::string& name) { this->name = name; }
void Event::setDescription(const std::string& description) { this->description = description; }
void Event::setEventDate(const std::string& eventDate) { this->eventDate = eventDate; }
void Event::setEventTime(const std::string& eventTime) { this->eventTime = eventTime; }
void Event::setNumberOfGuests(int numberOfGuests) { this->numberOfGuests = numberOfGuests; }
void Event::setSpecialRequirements(const std::string& specialRequirements) { this->specialRequirements = specialRequirements; }
void Event::setCreatedAt(const std::string& createdAt) { this->createdAt = createdAt; }

