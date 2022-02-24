cmake_minimum_required(VERSION 3.21)
project(HeapTable)

set(CMAKE_CXX_STANDARD 14)

add_executable(FDBS test.cpp cHashTable.h cHashTableNode.h seq_rand_access.h cPointerTable.h)
