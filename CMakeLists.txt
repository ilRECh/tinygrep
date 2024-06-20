cmake_minimum_required(VERSION 3.5)

project(tinygrep)

set(CMAKE_CXX_STANDARD 17)

include_directories(inc)
file(GLOB SOURCES src/*.cpp)

add_executable(tinygrep main.cpp ${SOURCES})
