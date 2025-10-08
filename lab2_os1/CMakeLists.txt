cmake_minimum_required(VERSION 3.15)
project(lab2_os LANGUAGES CXX)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# CORE (библиотека с основной логикой)
add_library(lab2_core
    src/core.cpp
    src/wrappers/MinMaxWrapper.cpp
    src/wrappers/AverageWrapper.cpp 
    src/wrappers/AverageWrapper_th.cpp
    src/wrappers/MinMaxWrapper_th.cpp )
target_include_directories(lab2_core PUBLIC src)

# EXECUTABLE (главная программа)
add_executable(lab2_exec
    src/lab2_os1.cpp
 )
target_link_libraries(lab2_exec PRIVATE lab2_core)

# EXECUTABLE (главная программа std::thread)
add_executable(lab2_exec_th
    src/lab2_os_th.cpp
)
target_link_libraries(lab2_exec_th PRIVATE lab2_core)

# TESTS (отдельный exe для doctest)
add_executable(lab2_tests
    tests/tests_core.cpp)
target_include_directories(lab2_tests PRIVATE src doctest) 
target_link_libraries(lab2_tests PRIVATE lab2_core)

# Регистрируем тест для CTest
enable_testing()
add_test(NAME lab2_run_tests COMMAND lab2_tests)

