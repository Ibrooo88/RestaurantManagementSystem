#ifndef EVENTREPOSITORY_H
#define EVENTREPOSITORY_H

#include "../models/Event.h"
#include <vector>
#include <string>

class EventRepository {
public:
    Event* getById(int id);
    std::vector<Event*> getAll();
    std::vector<Event*> getByDate(const std::string& date);
    bool insert(Event* event);
    bool update(Event* event);
    bool deleteById(int id);
};

#endif // EVENTREPOSITORY_H

