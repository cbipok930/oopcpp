cmake_minimum_required(VERSION 3.20)
project(task4)

set(CMAKE_CXX_STANDARD 17)

find_library(GDIPLUS_LIBRARY NAMES libgdiplus gdiplus)

add_library(c controller/Controller.cpp controller/Controller.h)
add_library(m model/Model.cpp model/Model.h)
add_library(v view/View.cpp view/View.cpp)
target_link_libraries(c m v)

add_executable(task4 main.cpp)
target_link_libraries(task4 c gdiplus)
