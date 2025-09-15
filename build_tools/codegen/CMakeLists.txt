cmake_minimum_required(VERSION 3.16)

# Codegen Tool
project(codegen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages - use parent definitions
# (pugixml is handled by parent CMakeLists.txt)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src
    ${PUGIXML_INCLUDE_DIRS}
)

# Codegen executable (simple version for demo)
add_executable(codegen
    main.cpp
    AssetIdGenerator.cpp
)
