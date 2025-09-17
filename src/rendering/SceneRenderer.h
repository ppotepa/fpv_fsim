#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <GL/gl.h>
#include <windows.h>
#include "../core/AssetManager.h"
#include "../assets/AssetRegistry.h"
#include "../components/Transform.h"
#include "../systems/MaterialManager.h"
#include "../generators/TerrainGenerator.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
        
        // Initialize TerrainGenerator and load terrain config from JSON packages
        terrainGenerator_ = std::make_unique<Terrain::TerrainGenerator>();
        if (!terrainGenerator_->LoadTerrainConfig("assets/packages/core/package.json"))
        {
            // Log warning but continue - terrain generation will be disabled
            // DEBUG_LOG would be here but we'll continue without terrain
        }
        
        // TODO: In a real implementation, we would load the scene from the asset manager
        // For now, we'll load entities from the JSON package data
        // The main.cpp should eventually use WorldGenSystem to load entities from packages
        
        // Load entities from JSON package instead of hardcoded cubes
        // Create Earth rendering with ocean and land spheres
        
        // Create Ocean sphere (blue water base)
        RenderObject oceanSphere;
        oceanSphere.meshId = "earthSphereMesh";  // From package.json meshes - higher detail sphere
        oceanSphere.materialId = "earthOceanMaterial";  // From package.json materials - blue ocean
        oceanSphere.transform.position = {0.0f, 0.0f, 0.0f};  // Centered at origin
        oceanSphere.transform.scale = {1.0f, 1.0f, 1.0f};  // Base Earth size
        oceanSphere.rotationSpeedY = 10.0f;  // Slow rotation to show Earth spinning
        objects_.push_back(oceanSphere);
        
        // Create Land sphere (green continents with noise)
        RenderObject landSphere;
        landSphere.meshId = "earthSphereMesh";  // From package.json meshes - same high detail sphere
        landSphere.materialId = "earthLandMaterial";  // From package.json materials - green land
        landSphere.transform.position = {0.0f, 0.0f, 0.0f};  // Same position as ocean
        landSphere.transform.scale = {1.01f, 1.01f, 1.01f};  // Slightly larger to appear above water
        landSphere.rotationSpeedY = 10.0f;  // Same rotation as ocean for synchronized spinning
        objects_.push_back(landSphere);

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
            else if (obj.meshId == "earthSphereMesh")
            {
                // Check if this is the land sphere (needs irregular terrain)
                if (obj.materialId == "earthLandMaterial")
                {
                    renderEarthLandSphere();
                }
                else
                {
                    renderEarthOceanSphere();
                }
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

    // Helper to render a perfect sphere for Earth's ocean
    void renderEarthOceanSphere()
    {
        // Render a smooth, perfect sphere for ocean
        const int latSegments = 24;  // Vertical segments
        const int lonSegments = 32;  // Horizontal segments
        const float radius = 1.0f;   // Will be scaled by transform
        
        glBegin(GL_TRIANGLES);
        
        for (int lat = 0; lat < latSegments; ++lat) {
            float lat0 = (float)lat / latSegments * M_PI - M_PI/2;
            float lat1 = (float)(lat + 1) / latSegments * M_PI - M_PI/2;
            
            float y0 = radius * sin(lat0);
            float y1 = radius * sin(lat1);
            float r0 = radius * cos(lat0);
            float r1 = radius * cos(lat1);
            
            for (int lon = 0; lon < lonSegments; ++lon) {
                float lon0 = (float)lon / lonSegments * 2 * M_PI;
                float lon1 = (float)(lon + 1) / lonSegments * 2 * M_PI;
                
                float x00 = r0 * cos(lon0);
                float z00 = r0 * sin(lon0);
                float x01 = r0 * cos(lon1);
                float z01 = r0 * sin(lon1);
                float x10 = r1 * cos(lon0);
                float z10 = r1 * sin(lon0);
                float x11 = r1 * cos(lon1);
                float z11 = r1 * sin(lon1);
                
                // First triangle
                glVertex3f(x00, y0, z00);
                glVertex3f(x10, y1, z10);
                glVertex3f(x01, y0, z01);
                
                // Second triangle
                glVertex3f(x01, y0, z01);
                glVertex3f(x10, y1, z10);
                glVertex3f(x11, y1, z11);
            }
        }
        
        glEnd();
    }

    // Helper to render an irregular sphere for Earth's land with terrain noise
    void renderEarthLandSphere()
    {
        // Render an irregular sphere with noise for land terrain
        const int latSegments = 24;  // Vertical segments
        const int lonSegments = 32;  // Horizontal segments
        const float baseRadius = 1.0f;   // Base radius
        
        // Get noise amplitude from terrain generator config
        float noiseAmplitude = 0.15f;  // Default fallback
        if (terrainGenerator_ && terrainGenerator_->IsConfigLoaded())
        {
            noiseAmplitude = 0.15f; // Use default for now, terrain generation in GenerateTerrainNoise
        }
        
        glBegin(GL_TRIANGLES);
        
        for (int lat = 0; lat < latSegments; ++lat) {
            float lat0 = (float)lat / latSegments * M_PI - M_PI/2;
            float lat1 = (float)(lat + 1) / latSegments * M_PI - M_PI/2;
            
            for (int lon = 0; lon < lonSegments; ++lon) {
                float lon0 = (float)lon / lonSegments * 2 * M_PI;
                float lon1 = (float)(lon + 1) / lonSegments * 2 * M_PI;
                
                // Generate terrain noise for each vertex using TerrainGenerator
                float noise00 = 0.0f;
                float noise01 = 0.0f;
                float noise10 = 0.0f;
                float noise11 = 0.0f;
                
                if (terrainGenerator_ && terrainGenerator_->IsConfigLoaded())
                {
                    noise00 = terrainGenerator_->GenerateTerrainNoise(lat0, lon0);
                    noise01 = terrainGenerator_->GenerateTerrainNoise(lat0, lon1);
                    noise10 = terrainGenerator_->GenerateTerrainNoise(lat1, lon0);
                    noise11 = terrainGenerator_->GenerateTerrainNoise(lat1, lon1);
                }
                
                // Apply noise to radius for terrain variation
                float radius00 = baseRadius + noise00 * noiseAmplitude;
                float radius01 = baseRadius + noise01 * noiseAmplitude;
                float radius10 = baseRadius + noise10 * noiseAmplitude;
                float radius11 = baseRadius + noise11 * noiseAmplitude;
                
                // Calculate positions with terrain-modified radius
                float y0 = sin(lat0);
                float y1 = sin(lat1);
                float r0_base = cos(lat0);
                float r1_base = cos(lat1);
                
                float x00 = radius00 * r0_base * cos(lon0);
                float z00 = radius00 * r0_base * sin(lon0);
                float y00 = radius00 * y0;
                
                float x01 = radius01 * r0_base * cos(lon1);
                float z01 = radius01 * r0_base * sin(lon1);
                float y01 = radius01 * y0;
                
                float x10 = radius10 * r1_base * cos(lon0);
                float z10 = radius10 * r1_base * sin(lon0);
                float y10 = radius10 * y1;
                
                float x11 = radius11 * r1_base * cos(lon1);
                float z11 = radius11 * r1_base * sin(lon1);
                float y11 = radius11 * y1;
                
                // First triangle
                glVertex3f(x00, y00, z00);
                glVertex3f(x10, y10, z10);
                glVertex3f(x01, y01, z01);
                
                // Second triangle
                glVertex3f(x01, y01, z01);
                glVertex3f(x10, y10, z10);
                glVertex3f(x11, y11, z11);
            }
        }
        
        glEnd();
    }
    
    std::string sceneAssetId_;
    std::vector<RenderObject> objects_;
    std::unique_ptr<Material::MaterialManager> materialManager_;
    std::unique_ptr<Terrain::TerrainGenerator> terrainGenerator_;
};
