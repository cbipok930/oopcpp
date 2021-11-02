cmake_minimum_required(VERSION 3.20)
project(task3)

set(CMAKE_CXX_STANDARD 14)

add_library(workflow Config.h Config.cpp Fabric.h Fabric.cpp Worker.h Worker.cpp)
add_library(add addons/block_append.cpp addons/block_append.h)
add_executable(task3 main.cpp)
target_link_libraries(task3 workflow add)