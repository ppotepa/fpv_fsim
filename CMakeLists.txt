cmake_minimum_required(VERSION 3.10)
project(fpv_fsim VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
# SDL2 will be linked via vcpkg target

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
    src/core/Engine.cpp
    src/assets/AssetCompilerService.cpp
    src/physics/ExponentialAirDensityModel.cpp
    src/physics/PerlinWindModel.cpp
    src/physics/ImpulseCollisionResolver.cpp
    src/vehicles/DroneBuilder.cpp
    src/platform/PugiXmlParser.cpp
    src/generators/VoxelMeshGenerator.cpp
    src/generators/ProceduralTextureGenerator.cpp
    src/systems/PhysicsSystem.cpp
    src/systems/InputSystem.cpp
    src/systems/VehicleControlSystem.cpp
    src/systems/BootstrapSystem.cpp
    src/systems/WorldGenSystem.cpp
    src/factory/EntityFactory.cpp
    src/systems/MaterialManager.cpp
    src/config/SceneConfigParser.cpp
    src/config/PhysicsConfigParser.cpp
    src/config/RenderConfigParser.cpp
    src/config/InputConfig.cpp
    src/config/InputConfigParser.cpp
    src/config/EntityConfigParser.cpp
    src/factory/EntityFactory.cpp
    src/systems/ConsoleSystem.cpp
    src/systems/VisualizationSystem.cpp
    src/systems/AssetHotReloadSystem.cpp
    src/platform/WinInputDevice.cpp
    src/platform/OpenGLContext.cpp
    src/platform/OpenGLRenderer.cpp
    src/platform/ShaderCompiler.cpp
    # Temporarily comment out procedural generators until they're fixed
    # src/procedural/ProceduralMeshGenerators.cpp
    src/assets/ShaderAsset.cpp
    # Add more source files as implemented
)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
# Add SDL2 when properly configured
if(TARGET SDL2::SDL2)
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2)
endif()
