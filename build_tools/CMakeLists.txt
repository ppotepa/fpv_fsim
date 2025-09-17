cmake_minimum_required(VERSION 3.16)

# Build Tools Project
project(FPVSim_BuildTools)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# JSON-only configuration system - no XML dependencies needed

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

# Add subdirectories for each tool
add_subdirectory(asset_compiler)
add_subdirectory(codegen)

# Optional: Create a target that builds all tools
add_custom_target(build_all_tools
    DEPENDS asset_compiler codegen
    COMMENT "Building all asset pipeline tools"
)
