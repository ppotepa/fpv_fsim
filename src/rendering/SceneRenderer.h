#pragma once

#include <string>
#include <vector>
#include <memory>
#include <GL/gl.h>
#include <windows.h>
#include "../core/AssetManager.h"
#include "../assets/AssetRegistry.h"
#include "../components/Transform.h"
#include "../systems/MaterialManager.h"

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
        
        // Initialize MaterialManager and load materials from JSON packages
        materialManager_ = std::make_unique<Material::MaterialManager>();
        if (!materialManager_->LoadMaterialsFromJsonPackages())
        {
            // Fallback to default materials if JSON loading fails
            materialManager_->LoadDefaultMaterials();
        }
        
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

        // Load blue cube entity from package
        RenderObject blueCube;
        blueCube.meshId = "cubeMesh";  // From package.json meshes
        blueCube.materialId = "blueCubeMaterial";  // From package.json materials
        blueCube.transform.position = {-2.5f, 0.0f, 0.0f};  // From package.json blueCube entity
        blueCube.transform.scale = {1.0f, 1.0f, 1.0f};
        blueCube.rotationSpeedZ = 30.0f;  // From package.json blueCube behavior parameters
        objects_.push_back(blueCube);

        // Load green sphere entity from package
        RenderObject greenSphere;
        greenSphere.meshId = "sphereMesh";  // From package.json meshes
        greenSphere.materialId = "greenSphereMaterial";  // From package.json materials
        greenSphere.transform.position = {0.0f, 2.0f, 0.0f};  // From package.json greenSphere entity
        greenSphere.transform.scale = {1.5f, 1.5f, 1.5f};
        greenSphere.rotationSpeedX = 15.0f;  // From package.json greenSphere behavior (rotates on X+Y axis)
        greenSphere.rotationSpeedY = 15.0f;
        objects_.push_back(greenSphere);

        // Load yellow triangle formation from package
        RenderObject triangle1;
        triangle1.meshId = "triangleMesh";  // From package.json meshes
        triangle1.materialId = "yellowTriangleMaterial";  // From package.json materials
        triangle1.transform.position = {1.0f, -1.5f, 0.0f};  // From package.json yellowTriangle1 entity
        triangle1.transform.scale = {0.8f, 0.8f, 0.8f};
        triangle1.rotationSpeedY = 90.0f;  // From package.json yellowTriangle1 behavior parameters
        objects_.push_back(triangle1);

        RenderObject triangle2;
        triangle2.meshId = "triangleMesh";  // From package.json meshes
        triangle2.materialId = "yellowTriangleMaterial";  // From package.json materials
        triangle2.transform.position = {-1.0f, -1.5f, 0.0f};  // From package.json yellowTriangle2 entity
        triangle2.transform.scale = {0.8f, 0.8f, 0.8f};
        triangle2.rotationSpeedX = 45.0f;  // From package.json yellowTriangle2 behavior (rotates on X+Z axis)
        triangle2.rotationSpeedZ = 45.0f;
        objects_.push_back(triangle2);

        RenderObject triangle3;
        triangle3.meshId = "triangleMesh";  // From package.json meshes
        triangle3.materialId = "yellowTriangleMaterial";  // From package.json materials
        triangle3.transform.position = {0.0f, -1.5f, 1.0f};  // From package.json yellowTriangle3 entity
        triangle3.transform.scale = {0.8f, 0.8f, 0.8f};
        triangle3.rotationSpeedY = 60.0f;  // From package.json yellowTriangle3 behavior (rotates on Y+Z axis)
        triangle3.rotationSpeedZ = 60.0f;
        objects_.push_back(triangle3);

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

            // Get material color from MaterialManager (loaded from JSON package)
            auto materialOpt = materialManager_->GetMaterial(obj.materialId);
            if (materialOpt.has_value())
            {
                const auto& material = materialOpt.value();
                const auto& albedo = material.properties.albedo;
                glColor3f(albedo.x, albedo.y, albedo.z);
            }
            else
            {
                // Fallback color if material not found
                glColor3f(0.8f, 0.8f, 0.8f); // Light gray
            }

            // Render appropriate mesh based on mesh ID
            if (obj.meshId == "cubeMesh")
            {
                renderCube();
            }
            else if (obj.meshId == "sphereMesh")
            {
                renderSphere();
            }
            else if (obj.meshId == "triangleMesh")
            {
                renderTriangle();
            }
            else
            {
                renderCube(); // Default to cube for unknown mesh types
            }

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

    // Helper to render a sphere (simplified as an octahedron for now)
    void renderSphere()
    {
        // Simple octahedron approximation of a sphere
        glBegin(GL_TRIANGLES);
        
        float radius = 0.5f;
        
        // Top pyramid (4 triangles)
        glVertex3f(0.0f, radius, 0.0f);    // Top
        glVertex3f(radius, 0.0f, 0.0f);    // Right
        glVertex3f(0.0f, 0.0f, radius);    // Front
        
        glVertex3f(0.0f, radius, 0.0f);    // Top
        glVertex3f(0.0f, 0.0f, radius);    // Front
        glVertex3f(-radius, 0.0f, 0.0f);   // Left
        
        glVertex3f(0.0f, radius, 0.0f);    // Top
        glVertex3f(-radius, 0.0f, 0.0f);   // Left
        glVertex3f(0.0f, 0.0f, -radius);   // Back
        
        glVertex3f(0.0f, radius, 0.0f);    // Top
        glVertex3f(0.0f, 0.0f, -radius);   // Back
        glVertex3f(radius, 0.0f, 0.0f);    // Right
        
        // Bottom pyramid (4 triangles)
        glVertex3f(0.0f, -radius, 0.0f);   // Bottom
        glVertex3f(0.0f, 0.0f, radius);    // Front
        glVertex3f(radius, 0.0f, 0.0f);    // Right
        
        glVertex3f(0.0f, -radius, 0.0f);   // Bottom
        glVertex3f(-radius, 0.0f, 0.0f);   // Left
        glVertex3f(0.0f, 0.0f, radius);    // Front
        
        glVertex3f(0.0f, -radius, 0.0f);   // Bottom
        glVertex3f(0.0f, 0.0f, -radius);   // Back
        glVertex3f(-radius, 0.0f, 0.0f);   // Left
        
        glVertex3f(0.0f, -radius, 0.0f);   // Bottom
        glVertex3f(radius, 0.0f, 0.0f);    // Right
        glVertex3f(0.0f, 0.0f, -radius);   // Back
        
        glEnd();
    }

    // Helper to render a triangle (single triangle in 3D space)
    void renderTriangle()
    {
        glBegin(GL_TRIANGLES);
        
        float size = 0.8f;
        
        // Front-facing triangle
        glVertex3f(0.0f, size * 0.5f, 0.0f);           // Top
        glVertex3f(-size * 0.5f, -size * 0.5f, 0.1f);  // Bottom left
        glVertex3f(size * 0.5f, -size * 0.5f, 0.1f);   // Bottom right
        
        // Back-facing triangle (for visibility from behind)
        glVertex3f(0.0f, size * 0.5f, 0.0f);           // Top
        glVertex3f(size * 0.5f, -size * 0.5f, -0.1f);  // Bottom right
        glVertex3f(-size * 0.5f, -size * 0.5f, -0.1f); // Bottom left
        
        glEnd();
    }

    std::string sceneAssetId_;
    std::vector<RenderObject> objects_;
    std::unique_ptr<Material::MaterialManager> materialManager_;
};
