cmake_minimum_required(VERSION 3.20)
project(task3)

set(CMAKE_CXX_STANDARD 14)

add_library(lib Config.h Config.cpp Fabric.h Fabric.cpp)
add_executable(task3 main.cpp)
target_link_libraries(task3 lib)