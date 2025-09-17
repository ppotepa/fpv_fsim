cmake_minimum_required(VERSION 3.10)
project(scene_renderer_test VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find required packages
find_package(GTest REQUIRED)

# Include directories
include_directories(.)
include_directories(../src)
include_directories(../src/components)
include_directories(../src/behaviors)

# Add DEBUG macro for test
add_definitions(-DDEBUG)

# Test sources
set(TEST_SOURCES
    scene_renderer_test.cpp
    ../src/core/AssetManager.cpp
    ../src/core/AssetManager_Integration.cpp
    ../src/assets/AssetRegistry.cpp
)

# Test executable
add_executable(scene_renderer_test ${TEST_SOURCES})

# Link libraries
target_link_libraries(scene_renderer_test GTest::GTest GTest::Main)

# Windows specific libraries
if(WIN32)
    target_link_libraries(scene_renderer_test user32 gdi32 shell32)
endif()

# Copy assets for testing
add_custom_command(TARGET scene_renderer_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/../assets
    $<TARGET_FILE_DIR:scene_renderer_test>/assets
    COMMENT "Copying assets to test build directory"
)

# Copy internal_assets for testing
add_custom_command(TARGET scene_renderer_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/../internal_assets
    $<TARGET_FILE_DIR:scene_renderer_test>/internal_assets
    COMMENT "Copying internal_assets to test build directory"
)
