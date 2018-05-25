cmake_minimum_required(VERSION 3.8)
project(hw7)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp dary-heap.h ds.h graph.h wgraph.h mlist.h)
add_executable(hw7 ${SOURCE_FILES})