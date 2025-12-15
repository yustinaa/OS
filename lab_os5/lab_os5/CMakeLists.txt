cmake_minimum_required(VERSION 3.12)
project(lab_os5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Server server.cpp lab_os5.h)


add_executable(Client client.cpp lab_os5.h)
