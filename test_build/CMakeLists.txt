cmake_minimum_required(VERSION 3.10)
project(math_test VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(.)

# Test executable
add_executable(math_test test_math.cpp)
