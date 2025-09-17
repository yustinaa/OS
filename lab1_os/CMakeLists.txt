# Минимальная версия CMake 
cmake_minimum_required(VERSION 3.10)

# Название проекта и язык 
project(Lab1 LANGUAGES CXX)

# стандарт C++ 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp)
add_executable(creator creator.cpp) 
add_executable(reporter reporter.cpp)

target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(creator PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(reporter PUBLIC ${CMAKE_SOURCE_DIR})

if(MSVC)
    target_compile_options(main PRIVATE "/utf-8")
    target_compile_options(creator PRIVATE "/utf-8") 
    target_compile_options(reporter PRIVATE "/utf-8")
endif()
