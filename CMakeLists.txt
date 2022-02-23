cmake_minimum_required(VERSION 3.21)
project(FDBS)

set(CMAKE_CXX_STANDARD 14)

add_executable(FDBS heapTable.cpp seq_rand_access.h cPointerTable.h)
