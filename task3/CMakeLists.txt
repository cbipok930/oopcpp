cmake_minimum_required(VERSION 3.20)
project(task3)

set(CMAKE_CXX_STANDARD 14)

add_library(cfg workflow/configuration/Config.cpp workflow/configuration/Config.h)
add_library(bf workflow/block_factory/Fabric.cpp workflow/block_factory/Fabric.h)
add_library(wf workflow/Worker.h workflow/Worker.cpp)
link_libraries(wf bf cfg)

add_library(add addons/block_append.cpp addons/block_append.h)

add_executable(task3 main.cpp)
target_link_libraries(task3 wf add)