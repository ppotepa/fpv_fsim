cmake_minimum_required(VERSION 3.10)
project(fpv_fsim VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable optimization flags for better performance
if(CMAKE_GENERATOR MATCHES "MinGW Makefiles")
    # Optimization flags for better performance
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native -mtune=native")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
endif()

# Add DEBUG macro for debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

# Force DEBUG macro for testing
add_definitions(-DDEBUG)

find_package(OpenGL REQUIRED)
# SDL2 will be linked via vcpkg target

# Include directories
include_directories(src)
include_directories(src/components)
include_directories(src/behaviors)

# Minimal package system with OpenGL visualization
set(SOURCES
    src/main.cpp
    # Core systems needed for package demo
    src/core/EventBus.cpp
    src/core/Entity.cpp
    src/core/World.cpp
    src/core/SimClock.cpp
    # Enhanced Package System
    src/core/IoContainer.cpp
    src/core/PackageBootstrap.cpp
    src/assets/AssetRegistry.cpp
    src/assets/Package.cpp
    src/assets/PackageManager.cpp
    src/assets/PackageParser.cpp
    # Dual Asset System
    src/core/AssetManager.cpp
    src/core/AssetManager_Integration.cpp
    # Behavior system
    src/systems/BehaviorSystem.cpp
    src/factory/BehaviorRegistry.cpp
    src/behaviors/SpinBehavior.cpp
    src/behaviors/DebugOverlayBehavior.cpp
    # Platform
    src/platform/PugiXmlParser.cpp
)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
# Windows specific libraries for Engine
if(WIN32)
    target_link_libraries(${PROJECT_NAME} user32 gdi32 shell32 winmm)
endif()
# Add SDL2 when properly configured
if(TARGET SDL2::SDL2)
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2)
endif()

# Copy assets folder to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    COMMENT "Copying assets to build directory"
)

# Copy internal_assets folder to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/internal_assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/internal_assets
    COMMENT "Copying internal_assets to build directory"
)
