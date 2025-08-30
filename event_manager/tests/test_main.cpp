#include <iostream>
#include <cassert>
#include <fstream>
#include <chrono>
#include "../src/EventManager.h"

void createTestFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
    file.close();
}

int main() {
    std::cout << "=== Running EventManager Tests ===" << std::endl;
    
    // Тест 1: Загрузка файла
    std::cout << "\n1. Testing file loading..." << std::endl;
    try {
        createTestFile("test_file.txt", "01.01.2030 Test event\n"); // Будущая дата
        
        EventManager manager("test_file.txt");
        
        // Должно работать без ошибок
        std::cout << "✓ File loading test PASSED" << std::endl;
        
        std::remove("test_file.txt");
        
    } catch (const std::exception& e) {
        std::cout << "✗ Test FAILED: " << e.what() << std::endl;
        return 1;
    }
    
    // Тест 2: Получение событий
    std::cout << "\n2. Testing events retrieval..." << std::endl;
    try {
        createTestFile("test_events.txt", "01.01.2030 Event 1\n02.01.2030 Event 2\n");
        
        EventManager manager("test_events.txt");
        auto events = manager.getUpcomingEvents(std::chrono::system_clock::now());
        
        std::cout << "Found " << events.size() << " upcoming events" << std::endl;
        std::cout << "✓ Events retrieval test PASSED" << std::endl;
        
        std::remove("test_events.txt");
        
    } catch (const std::exception& e) {
        std::cout << "✗ Test FAILED: " << e.what() << std::endl;
        return 1;
    }
    
    // Тест 3: Обработка ошибок
    std::cout << "\n3. Testing error handling..." << std::endl;
    try {
        try {
            EventManager manager("non_existent_file.txt");
            std::cout << "✗ Error handling test FAILED: Should have thrown exception" << std::endl;
            return 1;
        } catch (const std::exception& e) {
            std::cout << "✓ Error handling test PASSED: " << e.what() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "✗ Test FAILED: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n=== All tests PASSED ===" << std::endl;
    return 0;
}