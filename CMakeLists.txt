cmake_minimum_required(VERSION 3.27)
project(CP)

set(CMAKE_CXX_STANDARD 14)

add_executable(CP
        0_999/test.cpp)

add_executable(edu edu/main.cpp
        edu/main.cpp
        edu/segment_tree/segment_tree.h)
