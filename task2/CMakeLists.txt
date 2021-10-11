cmake_minimum_required(VERSION 3.14)
project(task2)

set(CMAKE_CXX_STANDARD 14)

add_library(lib HashTable.cpp HashTable.h)
add_executable(task2 main.cpp)
target_link_libraries(task2 lib)
