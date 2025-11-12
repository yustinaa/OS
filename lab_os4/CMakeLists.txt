cmake_minimum_required(VERSION 3.12)
project(lab_os4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(lab_os4_core
    sync_manager.cpp
    sync_manager.h
 )
target_include_directories(lab_os4_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(lab_os4
    lab_os4.cpp
 )
target_link_libraries(lab_os4 PRIVATE lab_os4_core)

add_executable(sender
    sender.cpp)
target_link_libraries(sender PRIVATE lab_os4_core)

add_executable(tests
 tests.cpp)
 target_link_libraries(tests PRIVATE lab_os4_core)
