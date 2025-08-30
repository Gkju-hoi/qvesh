#pragma once

#include "Event.h"
#include <vector>
#include <string>
#include <chrono>

class EventManager {
public:
    EventManager(const std::string& filename);
    std::chrono::system_clock::time_point 
    parseDate(const std::string& dateStr);

    void sortEvents();
    std::vector<Event> getUpcomingEvents
    (std::chrono::system_clock::time_point date, size_t count = 7);
    
    static std::chrono::system_clock::time_point 
    parseDateForTest(const std::string& dateStr);

private:
    std::vector<Event> events_;
    void loadFromFile(const std::string& filename);
};