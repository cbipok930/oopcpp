cmake_minimum_required(VERSION 3.14)
project(task2)


include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(CMAKE_CXX_STANDARD 14)

add_library(lib HashTable.cpp HashTable.h)

set(MYDEBUG "OFF")

if(MYDEBUG MATCHES "ON")
    add_executable(task2 debug.cpp)
else()
    add_executable(task2 test.cpp)
    target_link_libraries(task2 gtest_main)
    #target_link_libraries(task2 string_times)
endif()
target_link_libraries(task2 lib)
