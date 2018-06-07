cmake_minimum_required(VERSION 3.8)
project(hw8)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp dary-heap.h digraph.h network.h wedge.h)
add_executable(hw8 ${SOURCE_FILES})