/**
 * @file CubeGenerator.h
 * @brief Procedural cube mesh generator with variations
 *
 * The CubeGenerator creates cube meshes with configurable variations
 * for voxel-style rendering. Features include:
 * - Basic cube generation with proper normals and UVs
 * - Size variations for organic feel
 * - Corner rounding for softer appearance
 * - Texture coordinate mapping options
 * - Integration with Math utilities for calculations
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include <vector>
#include <cstdint>

/**
 * @brief Procedural cube mesh generator
 *
 * Generates cube meshes with various modifications for voxel-style
 * rendering including size variations and corner rounding.
 */
class CubeGenerator
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

    /**
     * @brief UV mapping mode for cube faces
     */
    enum class UVMode
    {
        PerFace,  /**< Each face gets full UV space [0,1] */
        Atlas,    /**< All faces share UV space in atlas layout */
        Projected /**< Projected mapping from one direction */
    };

private:
    /** @brief Cube size */
    Math::float3 size;

    /** @brief Corner rounding radius (0 = sharp corners) */
    float cornerRadius;

    /** @brief Corner rounding subdivision level */
    int cornerSubdivisions;

    /** @brief UV mapping mode */
    UVMode uvMode;

    /** @brief Random seed for variations */
    uint32_t randomSeed;

public:
    /**
     * @brief Construct a new CubeGenerator
     *
     * @param cubeSize Size of the cube (can be non-uniform)
     * @param rounding Corner rounding radius
     * @param subdivisions Corner subdivision level for rounding
     * @param uvMapping UV mapping mode
     * @param seed Random seed for variations
     */
    CubeGenerator(const Math::float3 &cubeSize = {1, 1, 1},
                  float rounding = 0.0f,
                  int subdivisions = 1,
                  UVMode uvMapping = UVMode::PerFace,
                  uint32_t seed = 12345)
        : size(cubeSize), cornerRadius(rounding), cornerSubdivisions(subdivisions), uvMode(uvMapping), randomSeed(seed)
    {
    }

    /**
     * @brief Generate cube mesh
     *
     * @return Generated mesh data
     */
    MeshData generate()
    {
        MeshData mesh;

        if (cornerRadius > 0.0f)
        {
            generateRoundedCube(mesh);
        }
        else
        {
            generateBasicCube(mesh);
        }

        // Update counts
        mesh.vertexCount = static_cast<uint32_t>(mesh.vertices.size());
        mesh.triangleCount = static_cast<uint32_t>(mesh.indices.size()) / 3;

        return mesh;
    }

    /**
     * @brief Generate basic cube with random variations
     *
     * @param variations Amount of random size variation per vertex
     * @return Generated mesh data with variations
     */
    MeshData generateWithVariations(float variations = 0.1f)
    {
        MeshData mesh = generate();

        // Apply random variations to vertices
        uint32_t state = randomSeed;
        for (auto &vertex : mesh.vertices)
        {
            float variation = 1.0f + variations * (Math::rand01(state) - 0.5f);
            vertex.position = Math::scale(vertex.position, variation);
        }

        // Recalculate normals after variation
        recalculateNormals(mesh);

        return mesh;
    }

    /**
     * @brief Set cube size
     *
     * @param cubeSize New cube size
     */
    void setSize(const Math::float3 &cubeSize)
    {
        size = cubeSize;
    }

    /**
     * @brief Set corner rounding
     *
     * @param radius Rounding radius
     * @param subdivisions Subdivision level
     */
    void setCornerRounding(float radius, int subdivisions = 1)
    {
        cornerRadius = Math::clamp(radius, 0.0f, Math::min({size.x, size.y, size.z}) * 0.5f);
        cornerSubdivisions = Math::clamp(subdivisions, 1, 5);
    }

    /**
     * @brief Set UV mapping mode
     *
     * @param mode New UV mapping mode
     */
    void setUVMode(UVMode mode)
    {
        uvMode = mode;
    }

private:
    /**
     * @brief Generate basic cube mesh
     *
     * @param mesh Output mesh data
     */
    void generateBasicCube(MeshData &mesh)
    {
        // Half sizes for convenience
        float hx = size.x * 0.5f;
        float hy = size.y * 0.5f;
        float hz = size.z * 0.5f;

        // Face vertices (position, normal, uv)
        std::vector<std::vector<Vertex>> faces = {
            // Front face (+Z)
            {{{{-hx, -hy, hz}, {0, 0, 1}, {0, 0}},
              {{hx, -hy, hz}, {0, 0, 1}, {1, 0}},
              {{hx, hy, hz}, {0, 0, 1}, {1, 1}},
              {{-hx, hy, hz}, {0, 0, 1}, {0, 1}}}},
            // Back face (-Z)
            {{{{hx, -hy, -hz}, {0, 0, -1}, {0, 0}},
              {{-hx, -hy, -hz}, {0, 0, -1}, {1, 0}},
              {{-hx, hy, -hz}, {0, 0, -1}, {1, 1}},
              {{hx, hy, -hz}, {0, 0, -1}, {0, 1}}}},
            // Left face (-X)
            {{{{-hx, -hy, -hz}, {-1, 0, 0}, {0, 0}},
              {{-hx, -hy, hz}, {-1, 0, 0}, {1, 0}},
              {{-hx, hy, hz}, {-1, 0, 0}, {1, 1}},
              {{-hx, hy, -hz}, {-1, 0, 0}, {0, 1}}}},
            // Right face (+X)
            {{{{hx, -hy, hz}, {1, 0, 0}, {0, 0}},
              {{hx, -hy, -hz}, {1, 0, 0}, {1, 0}},
              {{hx, hy, -hz}, {1, 0, 0}, {1, 1}},
              {{hx, hy, hz}, {1, 0, 0}, {0, 1}}}},
            // Bottom face (-Y)
            {{{{-hx, -hy, -hz}, {0, -1, 0}, {0, 0}},
              {{hx, -hy, -hz}, {0, -1, 0}, {1, 0}},
              {{hx, -hy, hz}, {0, -1, 0}, {1, 1}},
              {{-hx, -hy, hz}, {0, -1, 0}, {0, 1}}}},
            // Top face (+Y)
            {{{{-hx, hy, hz}, {0, 1, 0}, {0, 0}},
              {{hx, hy, hz}, {0, 1, 0}, {1, 0}},
              {{hx, hy, -hz}, {0, 1, 0}, {1, 1}},
              {{-hx, hy, -hz}, {0, 1, 0}, {0, 1}}}}};

        // Add vertices and indices for each face
        for (size_t faceIndex = 0; faceIndex < faces.size(); ++faceIndex)
        {
            uint32_t baseIndex = static_cast<uint32_t>(mesh.vertices.size());

            // Add face vertices with UV mapping
            for (size_t vertIndex = 0; vertIndex < 4; ++vertIndex)
            {
                Vertex vertex = faces[faceIndex][vertIndex];
                vertex.uv = calculateUV(vertex.position, faceIndex, vertIndex);
                mesh.vertices.push_back(vertex);
            }

            // Add face indices (two triangles per face)
            mesh.indices.insert(mesh.indices.end(), {baseIndex, baseIndex + 1, baseIndex + 2,
                                                     baseIndex, baseIndex + 2, baseIndex + 3});
        }
    }

    /**
     * @brief Generate rounded cube mesh
     *
     * @param mesh Output mesh data
     */
    void generateRoundedCube(MeshData &mesh)
    {
        // For rounded cubes, we create a more complex mesh
        // This is a simplified version - full implementation would be quite complex

        // Start with basic cube
        generateBasicCube(mesh);

        // Apply corner rounding by moving vertices towards sphere
        float maxRadius = Math::min({size.x, size.y, size.z}) * 0.5f;
        float clampedRadius = Math::clamp(cornerRadius, 0.0f, maxRadius);

        for (auto &vertex : mesh.vertices)
        {
            // Calculate distance from center
            float distance = Math::len(vertex.position);
            if (distance > clampedRadius)
            {
                // Blend between cube and sphere based on corner radius
                Math::float3 spherePos = Math::scale(Math::norm(vertex.position), clampedRadius);
                float blendFactor = cornerRadius / maxRadius;
                vertex.position = Math::lerp3(vertex.position, spherePos, blendFactor);
            }
        }

        // Recalculate normals after rounding
        recalculateNormals(mesh);
    }

    /**
     * @brief Calculate UV coordinates based on mapping mode
     *
     * @param position Vertex position
     * @param faceIndex Face index (0-5)
     * @param vertexIndex Vertex index within face (0-3)
     * @return UV coordinates
     */
    Math::float2 calculateUV(const Math::float3 &position, size_t faceIndex, size_t vertexIndex)
    {
        switch (uvMode)
        {
        case UVMode::PerFace:
            return calculatePerFaceUV(vertexIndex);

        case UVMode::Atlas:
            return calculateAtlasUV(faceIndex, vertexIndex);

        case UVMode::Projected:
            return calculateProjectedUV(position);

        default:
            return {0, 0};
        }
    }

    /**
     * @brief Calculate per-face UV coordinates
     *
     * @param vertexIndex Vertex index within face
     * @return UV coordinates
     */
    Math::float2 calculatePerFaceUV(size_t vertexIndex)
    {
        switch (vertexIndex)
        {
        case 0:
            return {0, 0};
        case 1:
            return {1, 0};
        case 2:
            return {1, 1};
        case 3:
            return {0, 1};
        default:
            return {0, 0};
        }
    }

    /**
     * @brief Calculate atlas UV coordinates
     *
     * @param faceIndex Face index
     * @param vertexIndex Vertex index within face
     * @return UV coordinates
     */
    Math::float2 calculateAtlasUV(size_t faceIndex, size_t vertexIndex)
    {
        // Simple 3x2 atlas layout
        float faceWidth = 1.0f / 3.0f;
        float faceHeight = 1.0f / 2.0f;

        int atlasX = static_cast<int>(faceIndex % 3);
        int atlasY = static_cast<int>(faceIndex / 3);

        Math::float2 localUV = calculatePerFaceUV(vertexIndex);

        return {
            atlasX * faceWidth + localUV.x * faceWidth,
            atlasY * faceHeight + localUV.y * faceHeight};
    }

    /**
     * @brief Calculate projected UV coordinates
     *
     * @param position Vertex position
     * @return UV coordinates
     */
    Math::float2 calculateProjectedUV(const Math::float3 &position)
    {
        // Simple planar projection from top
        float hx = size.x * 0.5f;
        float hz = size.z * 0.5f;

        return {
            (position.x + hx) / size.x,
            (position.z + hz) / size.z};
    }

    /**
     * @brief Recalculate normals for the mesh
     *
     * @param mesh Mesh to recalculate normals for
     */
    void recalculateNormals(MeshData &mesh)
    {
        // Reset all normals
        for (auto &vertex : mesh.vertices)
        {
            vertex.normal = {0, 0, 0};
        }

        // Calculate face normals and accumulate
        for (size_t i = 0; i < mesh.indices.size(); i += 3)
        {
            uint32_t i0 = mesh.indices[i];
            uint32_t i1 = mesh.indices[i + 1];
            uint32_t i2 = mesh.indices[i + 2];

            const Math::float3 &p0 = mesh.vertices[i0].position;
            const Math::float3 &p1 = mesh.vertices[i1].position;
            const Math::float3 &p2 = mesh.vertices[i2].position;

            // Calculate face normal
            Math::float3 edge1 = Math::sub(p1, p0);
            Math::float3 edge2 = Math::sub(p2, p0);
            Math::float3 faceNormal = Math::norm(Math::cross(edge1, edge2));

            // Accumulate to vertex normals
            mesh.vertices[i0].normal = Math::add(mesh.vertices[i0].normal, faceNormal);
            mesh.vertices[i1].normal = Math::add(mesh.vertices[i1].normal, faceNormal);
            mesh.vertices[i2].normal = Math::add(mesh.vertices[i2].normal, faceNormal);
        }

        // Normalize all vertex normals
        for (auto &vertex : mesh.vertices)
        {
            vertex.normal = Math::norm(vertex.normal);
        }
    }
};

