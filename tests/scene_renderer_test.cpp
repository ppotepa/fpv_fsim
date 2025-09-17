#include <gtest/gtest.h>
#include "../src/rendering/SceneRenderer.h"
#include "../src/core/AssetManager.h"

class SceneRendererTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up the asset manager
        assetManager.initialize("internal_assets", "assets");
    }

    AssetManager assetManager;
    SceneRenderer sceneRenderer;
};

// Test that the renderer initializes correctly
TEST_F(SceneRendererTest, InitializeWorks) {
    bool result = sceneRenderer.initialize("scene.green_cubes", assetManager);
    EXPECT_TRUE(result);
}

// Test the update method changes rotation values
TEST_F(SceneRendererTest, UpdateChangesRotation) {
    // Initialize the renderer
    sceneRenderer.initialize("scene.green_cubes", assetManager);
    
    // Get access to the private members for testing
    auto& objects = *reinterpret_cast<std::vector<SceneRenderer::RenderObject>*>(
        reinterpret_cast<char*>(&sceneRenderer) + offsetof(SceneRenderer, objects_)
    );
    
    // Store initial rotations
    std::vector<float> initialRotationsY;
    for (const auto& obj : objects) {
        initialRotationsY.push_back(obj.rotationY);
    }
    
    // Update with a time delta
    const float deltaTime = 1.0f / 60.0f; // 1/60th of a second
    sceneRenderer.update(deltaTime);
    
    // Check that rotations have changed
    for (size_t i = 0; i < objects.size(); ++i) {
        EXPECT_NE(initialRotationsY[i], objects[i].rotationY);
    }
}

// Test we have 4 cubes in the scene (3 green and 1 red)
TEST_F(SceneRendererTest, HasFourCubes) {
    // Initialize the renderer
    sceneRenderer.initialize("scene.green_cubes", assetManager);
    
    // Get access to the private members for testing
    auto& objects = *reinterpret_cast<std::vector<SceneRenderer::RenderObject>*>(
        reinterpret_cast<char*>(&sceneRenderer) + offsetof(SceneRenderer, objects_)
    );
    
    // Check we have exactly 4 objects
    EXPECT_EQ(objects.size(), 4);
    
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
    
    // Check we have 3 green cubes and 1 red cube
    EXPECT_EQ(greenCount, 3);
    EXPECT_EQ(redCount, 1);
}

// Test the red cube rotates in the opposite direction
TEST_F(SceneRendererTest, RedCubeRotatesOpposite) {
    // Initialize the renderer
    sceneRenderer.initialize("scene.green_cubes", assetManager);
    
    // Get access to the private members for testing
    auto& objects = *reinterpret_cast<std::vector<SceneRenderer::RenderObject>*>(
        reinterpret_cast<char*>(&sceneRenderer) + offsetof(SceneRenderer, objects_)
    );
    
    // Find the red cube
    const SceneRenderer::RenderObject* redCube = nullptr;
    for (const auto& obj : objects) {
        if (obj.materialId == "material.red") {
            redCube = &obj;
            break;
        }
    }
    
    // Make sure we found the red cube
    ASSERT_NE(redCube, nullptr);
    
    // Check that its rotation speed is negative (opposite direction)
    EXPECT_LT(redCube->rotationSpeedY, 0.0f);
}

// Test the objects have different positions
TEST_F(SceneRendererTest, CubesHaveDifferentPositions) {
    // Initialize the renderer
    sceneRenderer.initialize("scene.green_cubes", assetManager);
    
    // Get access to the private members for testing
    auto& objects = *reinterpret_cast<std::vector<SceneRenderer::RenderObject>*>(
        reinterpret_cast<char*>(&sceneRenderer) + offsetof(SceneRenderer, objects_)
    );
    
    // Check that each cube has a unique position
    for (size_t i = 0; i < objects.size(); ++i) {
        for (size_t j = i + 1; j < objects.size(); ++j) {
            EXPECT_NE(objects[i].transform.position.x, objects[j].transform.position.x);
        }
    }
}
