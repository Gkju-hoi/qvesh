if(BUILD_TESTS)
    message(STATUS "Building tests...")
    
    # Создаем тестовый исполняемый файл
    add_executable(event_manager_tests
        test_main.cpp
        ../src/Event.cpp
        ../src/EventManager.cpp
    )
    
    # Подключаем директории
    target_include_directories(event_manager_tests PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
    )
    
    # Правильное добавление теста для многоконфигурационных генераторов
    if(CMAKE_CONFIGURATION_TYPES)
        # Для Multi-Config генераторов (Visual Studio)
        add_test(NAME EventManagerTests 
                 COMMAND $<TARGET_FILE:event_manager_tests>
                 CONFIGURATIONS Debug Release
                 WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    else()
        # Для single-config генераторов (Makefile, Ninja)
        add_test(NAME EventManagerTests 
                 COMMAND $<TARGET_FILE:event_manager_tests>
                 WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    endif()
    
    message(STATUS "Test executable: event_manager_tests")
endif()