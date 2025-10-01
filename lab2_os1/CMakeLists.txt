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
 "src/utils.h")
target_include_directories(lab2_core PUBLIC src)

# EXECUTABLE (главная программа)
add_executable(lab2_exec
    src/lab2_os1.cpp
 "src/utils.h")
target_link_libraries(lab2_exec PRIVATE lab2_core)

