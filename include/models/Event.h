#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
private:
    int id;
    std::string name;
    std::string description;
    std::string eventDate;
    std::string eventTime;
    int numberOfGuests;
    std::string specialRequirements;
    std::string createdAt;

public:
    Event();
    Event(int id, const std::string& name, const std::string& eventDate,
          const std::string& eventTime = "", int numberOfGuests = 0);
    
    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    std::string getEventDate() const;
    std::string getEventTime() const;
    int getNumberOfGuests() const;
    std::string getSpecialRequirements() const;
    std::string getCreatedAt() const;
    
    void setId(int id);
    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void setEventDate(const std::string& eventDate);
    void setEventTime(const std::string& eventTime);
    void setNumberOfGuests(int numberOfGuests);
    void setSpecialRequirements(const std::string& specialRequirements);
    void setCreatedAt(const std::string& createdAt);
};

#endif // EVENT_H

