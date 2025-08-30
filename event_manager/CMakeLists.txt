cmake_minimum_required(VERSION 3.20)
project(EventManager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Правильные пути к файлам
set(SOURCE_DIR src)
set(MAIN_SOURCE ${SOURCE_DIR}/main.cpp)
set(EVENT_SOURCE ${SOURCE_DIR}/Event.cpp)
set(EVENT_MANAGER_SOURCE ${SOURCE_DIR}/EventManager.cpp)

# Проверяем существование файлов
if(NOT EXISTS ${CMAKE_SOURCE_DIR}/${MAIN_SOURCE})
    message(FATAL_ERROR "File not found: ${CMAKE_SOURCE_DIR}/${MAIN_SOURCE}")
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/${EVENT_SOURCE})
    message(FATAL_ERROR "File not found: ${CMAKE_SOURCE_DIR}/${EVENT_SOURCE}")
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/${EVENT_MANAGER_SOURCE})
    message(FATAL_ERROR "File not found: ${CMAKE_SOURCE_DIR}/${EVENT_MANAGER_SOURCE}")
endif()

message(STATUS "Main source: ${CMAKE_SOURCE_DIR}/${MAIN_SOURCE}")
message(STATUS "Event source: ${CMAKE_SOURCE_DIR}/${EVENT_SOURCE}")
message(STATUS "EventManager source: ${CMAKE_SOURCE_DIR}/${EVENT_MANAGER_SOURCE}")

# Основное приложение
add_executable(event_manager
    ${MAIN_SOURCE}
    ${EVENT_SOURCE}
    ${EVENT_MANAGER_SOURCE}
)

target_include_directories(event_manager PRIVATE ${SOURCE_DIR})

# Опция для тестов
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()
    message(STATUS "Tests enabled")
    
    # Проверяем существует ли папка tests
    if(EXISTS ${CMAKE_SOURCE_DIR}/tests)
        message(STATUS "Found tests directory")
        add_subdirectory(tests)
    else()
        message(WARNING "Tests directory not found, skipping tests")
    endif()
endif()