#pragma once

#include <string>
#include <chrono>

class Event {
public:
    Event(std::chrono::system_clock::time_point date, const std::string& description);

    std::chrono::system_clock::time_point getDate() const;
    std::string getDescription() const;

    bool operator<(const Event& other) const;

private:
    std::chrono::system_clock::time_point date_;
    std::string description_;
};