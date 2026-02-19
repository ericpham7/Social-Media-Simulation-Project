cmake_minimum_required(VERSION 4.0)
project(socialNetworkSim)

set(CMAKE_CXX_STANDARD 23)
include_directories(include)
add_executable(socialNetworkSim
        src/main.cpp
        src/server.hpp


)
