cmake_minimum_required(VERSION 3.0.0)
project(render VERSION 0.0.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_models DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(SOURCES Model.cpp)
add_executable(render main.cpp ${SOURCES})