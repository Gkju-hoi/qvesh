#include "Event.h"

Event::Event(std::chrono::system_clock::time_point date, const std::string& description)
    : date_(date), description_(description) {}

std::chrono::system_clock::time_point Event::getDate() const {
    return date_;
}

std::string Event::getDescription() const {
    return description_;
}

bool Event::operator<(const Event& other) const {
    return date_ < other.date_;
}