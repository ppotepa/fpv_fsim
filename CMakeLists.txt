cmake_minimum_required(VERSION 3.10)
project(fpv_fsim VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(src)

# Source files
set(SOURCES
    src/main.cpp
    src/core/EventBus.cpp
    src/core/World.cpp
    src/core/SimClock.cpp
    # Add more source files as implemented
)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries (uncomment when SDL2 and OpenGL are available)
# target_link_libraries(${PROJECT_NAME} SDL2::SDL2 OpenGL::GL)
