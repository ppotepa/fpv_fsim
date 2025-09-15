cmake_minimum_required(VERSION 3.10)

project(codegen)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
)

add_executable(codegen ${SOURCES})
