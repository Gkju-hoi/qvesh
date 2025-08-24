#include "EventManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <iostream>

EventManager::EventManager(const std::string& filename) {
    loadFromFile(filename);
    sortEvents(); 
}

void EventManager::sortEvents() {
    std::sort(events_.begin(), events_.end());
}

void EventManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::string line;
    size_t lineNumber = 0;

    while (std::getline(file, line)) {
        ++lineNumber;

        if (line.empty()) {
            std::cerr << "Warning: Empty line at line " << lineNumber << " - skipping" << std::endl;
            continue;
        }

  
        if (line.size() < 11) {
            std::cerr << "Warning: Invalid line (too short) at line " << lineNumber
                << ": " << line << " - skipping" << std::endl;
            continue;
        }

        try {
            std::string dateStr = line.substr(0, 10); 
            std::string description = line.substr(11); 

            std::chrono::sys_days date = parseDate(dateStr);
            events_.push_back(Event(date, description));
        }
        catch (const std::exception& e) {
            std::cerr << "Warning: Error parsing line " << lineNumber
                << ": " << line << " - " << e.what() << " - skipping" << std::endl;
        }
    }
}

std::chrono::sys_days EventManager::parseDate(const std::string& dateStr) {
    int d, m, y;
    char dot1, dot2;
    std::istringstream ss(dateStr);
    ss >> d >> dot1 >> m >> dot2 >> y;
    if (!ss || dot1 != '.' || dot2 != '.') {
        throw std::runtime_error("Invalid date format: " + dateStr);
    }

    std::chrono::year_month_day ymd{ std::chrono::year(y) / std::chrono::month(m) / std::chrono::day(d) };
    if (!ymd.ok()) {
        throw std::runtime_error("Invalid date: " + dateStr);
    }
    return std::chrono::sys_days{ ymd };
}

std::vector<Event> EventManager::getUpcomingEvents(std::chrono::sys_days date, size_t count) {
    std::vector<Event> upcomingEvents;
    for (const Event& e : events_) {
        if (e.getDate() >= date) {
            upcomingEvents.push_back(e);
        }
    }


    if (upcomingEvents.size() > count) {
        upcomingEvents.erase(upcomingEvents.begin() + count, upcomingEvents.end());
    }

    return upcomingEvents;
}