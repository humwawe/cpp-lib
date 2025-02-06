cmake_minimum_required(VERSION 3.27)
project(cpp-lib)

set(CMAKE_CXX_STANDARD 23)

include_directories(src/util)

add_executable(cpp_lib src/graph/dijkstra.cpp
    src/math/mint.cpp
    src/math/prime.cpp
    src/ds/dsu.cpp
    src/graph/hld.cpp
    src/bit/bo.cpp
    src/ds/fenwick.cpp
)
