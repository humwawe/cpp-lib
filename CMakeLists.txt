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
    src/str/hash.cpp
    src/graph/mcf.cpp
    src/graph/mf.cpp
    src/math/binomial.cpp
    src/math/gcd.cpp
    src/ds/trie.cpp
    src/str/z.cpp
    src/ds/segt.cpp
    src/dp/nums.cpp
)
