cmake_minimum_required(VERSION 3.16)

# Build Tools Project
project(FPVSim_BuildTools)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
# Try to find pugixml via find_package first, then try manual search
find_package(pugixml QUIET)

if(NOT pugixml_FOUND)
    # Manual search for pugixml headers
    find_path(PUGIXML_INCLUDE_DIRS
        NAMES pugixml.hpp
        PATHS
            # Common paths where pugixml might be installed
            ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/pugixml/src
            ${CMAKE_CURRENT_SOURCE_DIR}/../deps/pugixml/src
            /usr/include
            /usr/local/include
            "C:/vcpkg/installed/x64-windows/include"
            "C:/dev/vcpkg/installed/x64-windows/include"
    )
    
    find_library(PUGIXML_LIBRARIES
        NAMES pugixml
        PATHS
            ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/pugixml
            ${CMAKE_CURRENT_SOURCE_DIR}/../deps/pugixml
            /usr/lib
            /usr/local/lib
            "C:/vcpkg/installed/x64-windows/lib"
            "C:/dev/vcpkg/installed/x64-windows/lib"
    )
    
    if(PUGIXML_INCLUDE_DIRS)
        message(STATUS "Found pugixml headers at: ${PUGIXML_INCLUDE_DIRS}")
    else()
        # If not found, we'll build our tools without pugixml for now
        message(WARNING "pugixml not found - XML parsing features will be limited")
        set(PUGIXML_INCLUDE_DIRS "")
        set(PUGIXML_LIBRARIES "")
    endif()
else()
    message(STATUS "Found pugixml via find_package")
    get_target_property(PUGIXML_INCLUDE_DIRS pugixml INTERFACE_INCLUDE_DIRECTORIES)
    set(PUGIXML_LIBRARIES pugixml)
endif()

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
    ${PUGIXML_INCLUDE_DIRS}
)

# Add subdirectories for each tool
add_subdirectory(asset_compiler)
add_subdirectory(codegen)

# Optional: Create a target that builds all tools
add_custom_target(build_all_tools
    DEPENDS asset_compiler codegen
    COMMENT "Building all asset pipeline tools"
)
