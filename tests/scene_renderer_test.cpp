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

// Test we have 3 cubes in the scene
TEST_F(SceneRendererTest, HasThreeGreenCubes) {
    // Initialize the renderer
    sceneRenderer.initialize("scene.green_cubes", assetManager);
    
    // Get access to the private members for testing
    auto& objects = *reinterpret_cast<std::vector<SceneRenderer::RenderObject>*>(
        reinterpret_cast<char*>(&sceneRenderer) + offsetof(SceneRenderer, objects_)
    );
    
    // Check we have exactly 3 objects
    EXPECT_EQ(objects.size(), 3);
    
    // Check they all use the green material
    for (const auto& obj : objects) {
        EXPECT_EQ(obj.materialId, "material.green");
    }
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
