cmake_minimum_required(VERSION 3.0.0)
project(render VERSION 0.0.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic")

set(SOURCES Model.cpp ModelOBJ.cpp)
add_executable(render main.cpp ${SOURCES})