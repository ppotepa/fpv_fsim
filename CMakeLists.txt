cmake_minimum_required(VERSION 3.10)
project(fpv_fsim VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)

# Include directories
include_directories(src)
include_directories(src/components)

# Source files
set(SOURCES
    src/main.cpp
    src/core/EventBus.cpp
    src/core/Entity.cpp
    src/core/World.cpp
    src/core/SimClock.cpp
    src/core/AssetRegistry.cpp
    src/core/AssetPackLoader.cpp
    src/physics/ExponentialAirDensityModel.cpp
    src/physics/PerlinWindModel.cpp
    src/physics/ImpulseCollisionResolver.cpp
    src/vehicles/DroneBuilder.cpp
    src/utils/PugiXmlParser.cpp
    src/systems/PhysicsSystem.cpp
    src/systems/InputSystem.cpp
    src/systems/VehicleControlSystem.cpp
    src/systems/BootstrapSystem.cpp
    src/systems/WorldGenSystem.cpp
    src/systems/ConsoleSystem.cpp
    src/systems/VisualizationSystem.cpp
    src/systems/AssetHotReloadSystem.cpp
    src/platform/WinInputDevice.cpp
    # Add more source files as implemented
)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries (uncomment when SDL2 and OpenGL are available)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
