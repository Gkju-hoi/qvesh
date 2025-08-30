add_executable(event_manager
    main.cpp
    Event.cpp
    EventManager.cpp
    Event.h
    EventManager.h
)
target_include_directories(event_manager PRIVATE .)

if(MSVC)
    target_compile_options(event_manager PRIVATE /W4 /EHsc /std:c++20)
endif() 