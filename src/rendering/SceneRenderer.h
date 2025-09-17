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

        // In a real implementation, we would load the scene from the asset
        // Here we'll just create our 3 green cubes directly

        // Create cube 1
        RenderObject cube1;
        cube1.meshId = "mesh.cube";
        cube1.materialId = "material.green";
        cube1.transform.position = {-1.5f, 0.0f, 0.0f};
        cube1.transform.scale = {0.8f, 0.8f, 0.8f};
        cube1.rotationSpeedX = 15.0f;
        cube1.rotationSpeedY = 30.0f;
        objects_.push_back(cube1);

        // Create cube 2
        RenderObject cube2;
        cube2.meshId = "mesh.cube";
        cube2.materialId = "material.green";
        cube2.transform.position = {0.0f, 0.0f, 0.0f};
        cube2.transform.scale = {0.8f, 0.8f, 0.8f};
        cube2.rotationSpeedY = 45.0f;
        objects_.push_back(cube2);

        // Create cube 3
        RenderObject cube3;
        cube3.meshId = "mesh.cube";
        cube3.materialId = "material.green";
        cube3.transform.position = {1.5f, 0.0f, 0.0f};
        cube3.transform.scale = {0.8f, 0.8f, 0.8f};
        cube3.rotationSpeedY = 60.0f;
        cube3.rotationSpeedZ = 30.0f;
        objects_.push_back(cube3);

        // Create red cube (rotating in the opposite direction)
        RenderObject redCube;
        redCube.meshId = "mesh.cube";
        redCube.materialId = "material.red";
        redCube.transform.position = {0.0f, 1.5f, 0.0f};
        redCube.transform.scale = {1.0f, 1.0f, 1.0f};
        redCube.rotationSpeedX = -15.0f;
        redCube.rotationSpeedY = -45.0f; // Negative value for opposite rotation
        objects_.push_back(redCube);

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
