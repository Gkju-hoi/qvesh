@echo off
echo Running tests...
cd /d d:\games\qvesh\build

echo Checking for test executable...
if exist tests\Debug\event_manager_tests.exe (
    echo Running Debug tests...
    tests\Debug\event_manager_tests.exe
) else if exist tests\Release\event_manager_tests.exe (
    echo Running Release tests...
    tests\Release\event_manager_tests.exe
) else if exist tests\event_manager_tests.exe (
    echo Running tests...
    tests\event_manager_tests.exe
) else (
    echo Test executable not found!
    echo Available files in tests folder:
    dir tests\
    pause
)