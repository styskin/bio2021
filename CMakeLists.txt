# Get the problem name from the current directory
get_filename_component(problem ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Basic CMake project
cmake_minimum_required (VERSION 3.5)

# Name the project after the problem
project(${problem} CXX)

# Enable C++11 features on gcc/clang
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "(GNU|Clang)")
    set(CMAKE_CXX_FLAGS "-std=c++11")
endif()

add_subdirectory(clpr1)
add_subdirectory(clpr2)
add_subdirectory(clpr3)
add_subdirectory(f1)
add_subdirectory(f2)
add_subdirectory(f3)
add_subdirectory(f5)
