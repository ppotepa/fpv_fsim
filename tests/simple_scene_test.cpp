#include <iostream>
#include <vector>
#include "../src/rendering/SceneRenderer.h"
#include "../src/core/AssetManager.h"

// Simple test framework
#define TEST_ASSERT(condition, message) \
    if (!(condition)) { \
        std::cerr << "FAILED: " << message << std::endl; \
        return false; \
    }

// Test initialization
bool testInitialize() {
    AssetManager assetManager;
    SceneRenderer sceneRenderer;
    
    bool result = sceneRenderer.initialize("scene.green_cubes", assetManager);
    TEST_ASSERT(result, "Initialization should succeed");
    
    std::cout << "PASSED: SceneRenderer initializes correctly" << std::endl;
    return true;
}

// Test that we have 4 cubes (3 green, 1 red)
bool testHasFourCubes() {
    AssetManager assetManager;
    SceneRenderer sceneRenderer;
    sceneRenderer.initialize("scene.green_cubes", assetManager);
    
    // Get the objects using the getter method
    const auto& objects = sceneRenderer.getObjects();
    
    TEST_ASSERT(objects.size() == 4, "Should have 4 objects");
    
    // Count green and red cubes
    int greenCount = 0;
    int redCount = 0;
    
    for (const auto& obj : objects) {
        if (obj.materialId == "material.green") {
            greenCount++;
        } else if (obj.materialId == "material.red") {
            redCount++;
        }
    }
    
    TEST_ASSERT(greenCount == 3, "Should have 3 green cubes");
    TEST_ASSERT(redCount == 1, "Should have 1 red cube");
    
    std::cout << "PASSED: Scene has 3 green cubes and 1 red cube" << std::endl;
    return true;
}

// Test the red cube rotates in the opposite direction
bool testRedCubeRotatesOpposite() {
    AssetManager assetManager;
    SceneRenderer sceneRenderer;
    sceneRenderer.initialize("scene.green_cubes", assetManager);
    
    // Get the objects using the getter method
    const auto& objects = sceneRenderer.getObjects();
    
    // Find the red cube
    const SceneRenderer::RenderObject* redCube = nullptr;
    for (const auto& obj : objects) {
        if (obj.materialId == "material.red") {
            redCube = &obj;
            break;
        }
    }
    
    TEST_ASSERT(redCube != nullptr, "Red cube should exist");
    TEST_ASSERT(redCube->rotationSpeedY < 0.0f, "Red cube should rotate in opposite direction");
    
    std::cout << "PASSED: Red cube rotates in the opposite direction" << std::endl;
    return true;
}

// Test that all cubes have different positions
bool testCubesHaveDifferentPositions() {
    AssetManager assetManager;
    SceneRenderer sceneRenderer;
    sceneRenderer.initialize("scene.green_cubes", assetManager);
    
    // Get the objects using the getter method
    const auto& objects = sceneRenderer.getObjects();
    
    for (size_t i = 0; i < objects.size(); ++i) {
        for (size_t j = i + 1; j < objects.size(); ++j) {
            // Check that no two cubes have the same position
            if (objects[i].transform.position.x == objects[j].transform.position.x && 
                objects[i].transform.position.y == objects[j].transform.position.y &&
                objects[i].transform.position.z == objects[j].transform.position.z) {
                std::cerr << "FAILED: Cubes " << i << " and " << j << " have the same position" << std::endl;
                return false;
            }
        }
    }
    
    std::cout << "PASSED: All cubes have unique positions" << std::endl;
    return true;
}

int main() {
    std::cout << "=== Running Scene Renderer Tests ===" << std::endl;
    
    int passed = 0;
    int failed = 0;
    
    if (testInitialize()) passed++; else failed++;
    if (testHasFourCubes()) passed++; else failed++;
    if (testRedCubeRotatesOpposite()) passed++; else failed++;
    if (testCubesHaveDifferentPositions()) passed++; else failed++;
    
    std::cout << "\n=== Test Results ===" << std::endl;
    std::cout << "Passed: " << passed << std::endl;
    std::cout << "Failed: " << failed << std::endl;
    
    return failed;
}
