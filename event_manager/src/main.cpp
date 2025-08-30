#include "EventManager.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>

int main(int argc, char* argv[]) {
    try {
        std::string filename = "events.txt";
        if (argc > 1) {
            filename = argv[1];
        }

        std::cout << "Using file: " << filename << std::endl;
        
        EventManager manager(filename);

        auto today = std::chrono::system_clock::now();

        auto upcoming = manager.getUpcomingEvents(today);

        if (upcoming.empty()) {
            std::cout << "No upcoming events." << std::endl;
        } else {
            for (const auto& e : upcoming) {
                std::time_t time = std::chrono::system_clock::to_time_t(e.getDate());
                std::tm* tm = std::localtime(&time);
                
                std::cout << std::setw(2) << std::setfill('0') << tm->tm_mday << "."
                          << std::setw(2) << std::setfill('0') << (tm->tm_mon + 1) << "."
                          << std::setw(4) << std::setfill('0') << (tm->tm_year + 1900)
                          << " " << e.getDescription() << "\n";
            }
        }

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
}