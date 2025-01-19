cmake_minimum_required(VERSION 3.30)
project(cpp-lib)

set(CMAKE_CXX_STANDARD 23)

include_directories(src/util)

add_executable(cpp_lib src/graph/dijkstra.cpp
    src/math/mint.cpp
)
