cmake_minimum_required(VERSION 3.21)
project(HeapTable)

set(CMAKE_CXX_STANDARD 14)

add_executable(HeapTable heapTable.cpp seq_rand_access.h cPointerTable.h)
