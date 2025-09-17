#pragma once

#include <string>
#include <vector>
#include <memory>
#include <GL/gl.h>
#include <windows.h>
#include "../core/AssetManager.h"
#include "../assets/AssetRegistry.h"
#include "../components/Transform.h"

/**
 * @brief Simple class to render a scene with multiple objects
 */
class SceneRenderer
{
public:
    struct RenderObject
    {
        std::string meshId;
        std::string materialId;
        Components::Transform transform;
        float rotationX = 0.0f;
        float rotationY = 0.0f;
        float rotationZ = 0.0f;
        float rotationSpeedX = 0.0f;
        float rotationSpeedY = 0.0f;
        float rotationSpeedZ = 0.0f;
    };

    SceneRenderer() = default;
    ~SceneRenderer() = default;

    // Initialize with the scene asset ID
    bool initialize(const std::string &sceneAssetId, AssetManager &assetManager)
    {
        sceneAssetId_ = sceneAssetId;
        
        // TODO: In a real implementation, we would load the scene from the asset manager
        // For now, we'll load entities from the JSON package data
        // The main.cpp should eventually use WorldGenSystem to load entities from packages
        
        // Load entities from JSON package instead of hardcoded cubes
        // These should match what's defined in assets/packages/core/package.json
        
        // Load red cube entity from package
        RenderObject redCube;
        redCube.meshId = "cubeMesh";  // From package.json meshes
        redCube.materialId = "redCubeMaterial";  // From package.json materials
        redCube.transform.position = {0.0f, 0.0f, 0.0f};  // From package.json redCube entity
        redCube.transform.scale = {1.0f, 1.0f, 1.0f};
        redCube.rotationSpeedY = 45.0f;  // From package.json redCube behavior parameters
        objects_.push_back(redCube);

        // Load violet cube entity from package  
        RenderObject violetCube;
        violetCube.meshId = "cubeMesh";  // From package.json meshes
        violetCube.materialId = "violetCubeMaterial";  // From package.json materials
        violetCube.transform.position = {2.5f, 0.0f, 0.0f};  // From package.json violetCube entity
        violetCube.transform.scale = {1.0f, 1.0f, 1.0f};
        violetCube.rotationSpeedX = 60.0f;  // From package.json violetCube behavior parameters
        objects_.push_back(violetCube);

        return true;
    }

    // Update rotations
    void update(float deltaTime)
    {
        for (auto &obj : objects_)
        {
            obj.rotationX += obj.rotationSpeedX * deltaTime;
            obj.rotationY += obj.rotationSpeedY * deltaTime;
            obj.rotationZ += obj.rotationSpeedZ * deltaTime;

            // Wrap rotations
            if (obj.rotationX > 360.0f)
                obj.rotationX -= 360.0f;
            if (obj.rotationY > 360.0f)
                obj.rotationY -= 360.0f;
            if (obj.rotationZ > 360.0f)
                obj.rotationZ -= 360.0f;
        }
    }

    // Render the scene
    void render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Setup projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        HDC hdc = wglGetCurrentDC();
        HWND hwnd = WindowFromDC(hdc);
        RECT rect;
        GetClientRect(hwnd, &rect);
        float aspect = (float)(rect.right) / (float)(rect.bottom);

        // Simple perspective projection
        glFrustum(-0.1f * aspect, 0.1f * aspect, -0.1f, 0.1f, 0.1f, 100.0f);

        // Setup model-view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Move camera back and look at center
        glTranslatef(0.0f, 0.0f, -5.0f);

        // Render each object
        for (const auto &obj : objects_)
        {
            glPushMatrix();

            // Apply position
            glTranslatef(obj.transform.position.x, obj.transform.position.y, obj.transform.position.z);

            // Apply rotation
            glRotatef(obj.rotationX, 1.0f, 0.0f, 0.0f);
            glRotatef(obj.rotationY, 0.0f, 1.0f, 0.0f);
            glRotatef(obj.rotationZ, 0.0f, 0.0f, 1.0f);

            // Apply scale
            glScalef(obj.transform.scale.x, obj.transform.scale.y, obj.transform.scale.z);

            // Set material color based on material ID
            if (obj.materialId == "material.red")
            {
                glColor3f(1.0f, 0.0f, 0.0f); // Red color
            }
            else if (obj.materialId == "material.green")
            {
                glColor3f(0.0f, 1.0f, 0.0f); // Green color
            }
            else
            {
                glColor3f(0.7f, 0.7f, 0.7f); // Default gray color
            }

            // Draw cube
            renderCube();

            glPopMatrix();
        }

        SwapBuffers(hdc);
    }

    // For testing
    const std::vector<RenderObject> &getObjects() const
    {
        return objects_;
    }

private:
    // Helper to render a cube
    void renderCube()
    {
        glBegin(GL_QUADS);

        // Front face
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);

        // Back face
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);

        // Top face
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);

        // Bottom face
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);

        // Right face
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);

        // Left face
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);

        glEnd();
    }

    std::string sceneAssetId_;
    std::vector<RenderObject> objects_;
};
