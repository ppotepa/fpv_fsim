/**
 * @file IcoSphereGenerator.h
 * @brief Procedural icosphere mesh generator
 *
 * The IcoSphereGenerator creates geodesic sphere meshes with uniform
 * triangle distribution using iterative subdivision of an icosahedron.
 * Features include:
 * - Configurable subdivision levels for detail control
 * - Proper UV mapping for texture application
 * - Normal calculation for lighting
 * - Vertex deduplication for efficiency
 * - Integration with Math utilities for calculations
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include <vector>
#include <map>
#include <cstdint>

/**
 * @brief Procedural icosphere mesh generator
 *
 * Generates geodesic sphere meshes by subdividing an icosahedron.
 * Provides more uniform triangle distribution than UV spheres.
 */
class IcoSphereGenerator
{
public:
    /**
     * @brief Vertex data structure
     */
    struct Vertex
    {
        Math::float3 position; /**< Vertex position */
        Math::float3 normal;   /**< Vertex normal */
        Math::float2 uv;       /**< Texture coordinates */

        Vertex() : position{0, 0, 0}, normal{0, 0, 0}, uv{0, 0} {}
        Vertex(const Math::float3 &pos, const Math::float3 &norm, const Math::float2 &texCoord)
            : position(pos), normal(norm), uv(texCoord) {}
    };

    /**
     * @brief Generated mesh data
     */
    struct MeshData
    {
        std::vector<Vertex> vertices;  /**< Vertex array */
        std::vector<uint32_t> indices; /**< Triangle indices */
        uint32_t triangleCount;        /**< Number of triangles */
        uint32_t vertexCount;          /**< Number of vertices */

        MeshData() : triangleCount(0), vertexCount(0) {}
    };

private:
    /** @brief Subdivision level (0 = icosahedron, higher = more detail) */
    int subdivisionLevel;

    /** @brief Sphere radius */
    float radius;

    /** @brief Whether to smooth normals */
    bool smoothNormals;

    /** @brief Vertex deduplication map */
    std::map<uint64_t, uint32_t> vertexMap;

    /** @brief Current mesh being generated */
    MeshData *currentMesh;

public:
    /**
     * @brief Construct a new IcoSphereGenerator
     *
     * @param subdivisions Number of subdivision levels (0-6 recommended)
     * @param sphereRadius Radius of the generated sphere
     * @param smooth Whether to smooth normals across faces
     */
    IcoSphereGenerator(int subdivisions = 2, float sphereRadius = 1.0f, bool smooth = true)
        : subdivisionLevel(subdivisions), radius(sphereRadius), smoothNormals(smooth), currentMesh(nullptr)
    {
    }

    /**
     * @brief Generate icosphere mesh
     *
     * @return Generated mesh data
     */
    MeshData generate()
    {
        MeshData mesh;
        currentMesh = &mesh;
        vertexMap.clear();

        // Create base icosahedron
        createIcosahedron();

        // Subdivide to desired level
        for (int i = 0; i < subdivisionLevel; ++i)
        {
            subdivide();
        }

        // Project vertices to sphere surface and calculate normals
        projectToSphere();

        // Generate UV coordinates
        generateUVCoordinates();

        // Update counts
        mesh.vertexCount = static_cast<uint32_t>(mesh.vertices.size());
        mesh.triangleCount = static_cast<uint32_t>(mesh.indices.size()) / 3;

        currentMesh = nullptr;
        return mesh;
    }

    /**
     * @brief Set subdivision level
     *
     * @param level New subdivision level (0-6 recommended)
     */
    void setSubdivisionLevel(int level)
    {
        subdivisionLevel = Math::clamp(level, 0, 6);
    }

    /**
     * @brief Set sphere radius
     *
     * @param sphereRadius New radius
     */
    void setRadius(float sphereRadius)
    {
        radius = sphereRadius;
    }

    /**
     * @brief Set normal smoothing
     *
     * @param smooth Whether to smooth normals
     */
    void setSmoothNormals(bool smooth)
    {
        smoothNormals = smooth;
    }

private:
    /**
     * @brief Create base icosahedron
     */
    void createIcosahedron()
    {
        if (!currentMesh)
            return;

        // Golden ratio
        const float phi = (1.0f + std::sqrt(5.0f)) * 0.5f;
        const float a = 1.0f;
        const float b = 1.0f / phi;

        // Create 12 vertices of icosahedron
        std::vector<Math::float3> positions = {
            {0, b, -a}, {b, a, 0}, {-b, a, 0}, {0, b, a}, {0, -b, a}, {-a, 0, b}, {0, -b, -a}, {a, 0, -b}, {a, 0, b}, {-a, 0, -b}, {b, -a, 0}, {-b, -a, 0}};

        // Add vertices
        for (const auto &pos : positions)
        {
            addVertex(pos);
        }

        // Create 20 triangular faces
        std::vector<std::vector<uint32_t>> faces = {
            {2, 1, 0}, {1, 2, 3}, {5, 4, 3}, {4, 8, 3}, {7, 6, 0}, {6, 9, 0}, {11, 10, 4}, {10, 11, 6}, {9, 5, 2}, {5, 9, 11}, {8, 7, 1}, {7, 8, 10}, {2, 5, 3}, {8, 1, 3}, {9, 2, 0}, {1, 7, 0}, {11, 9, 6}, {7, 10, 6}, {5, 11, 4}, {10, 8, 4}};

        // Add faces
        for (const auto &face : faces)
        {
            currentMesh->indices.push_back(face[0]);
            currentMesh->indices.push_back(face[1]);
            currentMesh->indices.push_back(face[2]);
        }
    }

    /**
     * @brief Subdivide current mesh
     */
    void subdivide()
    {
        if (!currentMesh)
            return;

        std::vector<uint32_t> newIndices;

        // Process each triangle
        for (size_t i = 0; i < currentMesh->indices.size(); i += 3)
        {
            uint32_t v0 = currentMesh->indices[i];
            uint32_t v1 = currentMesh->indices[i + 1];
            uint32_t v2 = currentMesh->indices[i + 2];

            // Get midpoint vertices
            uint32_t m01 = getMidpointVertex(v0, v1);
            uint32_t m12 = getMidpointVertex(v1, v2);
            uint32_t m20 = getMidpointVertex(v2, v0);

            // Create 4 new triangles
            newIndices.insert(newIndices.end(), {v0, m01, m20});
            newIndices.insert(newIndices.end(), {v1, m12, m01});
            newIndices.insert(newIndices.end(), {v2, m20, m12});
            newIndices.insert(newIndices.end(), {m01, m12, m20});
        }

        currentMesh->indices = std::move(newIndices);
    }

    /**
     * @brief Project all vertices to sphere surface
     */
    void projectToSphere()
    {
        if (!currentMesh)
            return;

        for (auto &vertex : currentMesh->vertices)
        {
            // Normalize position to unit sphere
            vertex.position = Math::norm(vertex.position);

            // Scale to desired radius
            vertex.position = Math::scale(vertex.position, radius);

            // Normal is the same as normalized position for a sphere
            vertex.normal = Math::norm(vertex.position);
        }
    }

    /**
     * @brief Generate UV coordinates for vertices
     */
    void generateUVCoordinates()
    {
        if (!currentMesh)
            return;

        for (auto &vertex : currentMesh->vertices)
        {
            // Convert 3D position to spherical coordinates
            Math::float3 normalized = Math::norm(vertex.position);

            // Calculate UV from spherical coordinates
            float u = 0.5f + std::atan2(normalized.z, normalized.x) / (2.0f * Math::Pi);
            float v = 0.5f - std::asin(normalized.y) / Math::Pi;

            vertex.uv = {u, v};
        }

        // Fix UV seam issues
        fixUVSeams();
    }

    /**
     * @brief Fix UV coordinate seams at the sphere wrap-around
     */
    void fixUVSeams()
    {
        if (!currentMesh)
            return;

        // Process each triangle to fix UV discontinuities
        for (size_t i = 0; i < currentMesh->indices.size(); i += 3)
        {
            Vertex &v0 = currentMesh->vertices[currentMesh->indices[i]];
            Vertex &v1 = currentMesh->vertices[currentMesh->indices[i + 1]];
            Vertex &v2 = currentMesh->vertices[currentMesh->indices[i + 2]];

            // Check for UV wrap-around
            fixTriangleUVs(v0, v1, v2);
        }
    }

    /**
     * @brief Fix UV coordinates for a single triangle
     *
     * @param v0 First vertex
     * @param v1 Second vertex
     * @param v2 Third vertex
     */
    void fixTriangleUVs(Vertex &v0, Vertex &v1, Vertex &v2)
    {
        // Check for horizontal wrap-around (U coordinate)
        if (std::abs(v0.uv.x - v1.uv.x) > 0.5f)
        {
            if (v0.uv.x > v1.uv.x)
                v1.uv.x += 1.0f;
            else
                v0.uv.x += 1.0f;
        }
        if (std::abs(v1.uv.x - v2.uv.x) > 0.5f)
        {
            if (v1.uv.x > v2.uv.x)
                v2.uv.x += 1.0f;
            else
                v1.uv.x += 1.0f;
        }
        if (std::abs(v2.uv.x - v0.uv.x) > 0.5f)
        {
            if (v2.uv.x > v0.uv.x)
                v0.uv.x += 1.0f;
            else
                v2.uv.x += 1.0f;
        }
    }

    /**
     * @brief Add vertex to mesh with deduplication
     *
     * @param position Vertex position
     * @return Vertex index
     */
    uint32_t addVertex(const Math::float3 &position)
    {
        if (!currentMesh)
            return 0;

        // Create hash for vertex deduplication
        uint64_t hash = hashVertex(position);

        auto it = vertexMap.find(hash);
        if (it != vertexMap.end())
        {
            return it->second;
        }

        // Add new vertex
        uint32_t index = static_cast<uint32_t>(currentMesh->vertices.size());
        currentMesh->vertices.emplace_back(position, Math::float3{0, 0, 0}, Math::float2{0, 0});
        vertexMap[hash] = index;

        return index;
    }

    /**
     * @brief Get or create midpoint vertex between two vertices
     *
     * @param v0 First vertex index
     * @param v1 Second vertex index
     * @return Midpoint vertex index
     */
    uint32_t getMidpointVertex(uint32_t v0, uint32_t v1)
    {
        if (!currentMesh)
            return 0;

        // Calculate midpoint position
        const Math::float3 &pos0 = currentMesh->vertices[v0].position;
        const Math::float3 &pos1 = currentMesh->vertices[v1].position;
        Math::float3 midpoint = Math::scale(Math::add(pos0, pos1), 0.5f);

        return addVertex(midpoint);
    }

    /**
     * @brief Create hash for vertex position
     *
     * @param position Vertex position
     * @return Hash value
     */
    uint64_t hashVertex(const Math::float3 &position)
    {
        // Simple hash combining x, y, z coordinates
        const float precision = 1000000.0f;
        uint32_t x = static_cast<uint32_t>(position.x * precision);
        uint32_t y = static_cast<uint32_t>(position.y * precision);
        uint32_t z = static_cast<uint32_t>(position.z * precision);

        return (static_cast<uint64_t>(x) << 32) | (static_cast<uint64_t>(y) << 16) | z;
    }
};
