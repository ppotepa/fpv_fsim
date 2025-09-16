/**
 * @file ProceduralAircraftGenerator.h
 * @brief Procedural low-poly aircraft mesh generator
 *
 * The ProceduralAircraftGenerator creates simple low-poly aircraft meshes
 * suitable for orbital motion display. Features include:
 * - Basic aircraft shapes with wings, fuselage, and tail
 * - Configurable proportions and style variations
 * - Low-poly aesthetic for performance and voxel style
 * - Proper normals and UV mapping
 * - Integration with Math utilities for calculations
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include <vector>
#include <cstdint>
#include "../debug.h"

/**
 * @brief Procedural low-poly aircraft mesh generator
 *
 * Generates simple aircraft meshes with configurable styles and
 * proportions suitable for voxel-style orbital animations.
 */
class ProceduralAircraftGenerator
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
     * @brief Aircraft style variations
     */
    enum class AircraftStyle
    {
        Fighter,   /**< Fighter jet style */
        Civilian,  /**< Civil aircraft style */
        Transport, /**< Transport aircraft style */
        Simple     /**< Simple abstract aircraft */
    };

    /**
     * @brief Aircraft configuration parameters
     */
    struct AircraftParams
    {
        float length;        /**< Overall aircraft length */
        float wingspan;      /**< Wing span */
        float height;        /**< Overall height */
        float fuselageWidth; /**< Fuselage width */
        float wingThickness; /**< Wing thickness */
        float tailSize;      /**< Tail size factor */
        AircraftStyle style; /**< Aircraft style */
        uint32_t randomSeed; /**< Random seed for variations */

        AircraftParams()
            : length(2.0f), wingspan(2.5f), height(0.5f), fuselageWidth(0.3f), wingThickness(0.1f), tailSize(0.8f), style(AircraftStyle::Simple), randomSeed(12345)
        {
        }
    };

private:
    /** @brief Current aircraft parameters */
    AircraftParams params;

public:
    /**
     * @brief Construct a new ProceduralAircraftGenerator
     *
     * @param aircraftParams Aircraft configuration
     */
    ProceduralAircraftGenerator(const AircraftParams &aircraftParams = AircraftParams())
        : params(aircraftParams)
    {
    }

    /**
     * @brief Generate aircraft mesh
     *
     * @return Generated mesh data
     */
    MeshData generate()
    {
        DEBUG_LOG("Generating aircraft mesh with style " + std::to_string(static_cast<int>(params.style)));
        MeshData mesh;

        switch (params.style)
        {
        case AircraftStyle::Fighter:
            generateFighterAircraft(mesh);
            break;
        case AircraftStyle::Civilian:
            generateCivilianAircraft(mesh);
            break;
        case AircraftStyle::Transport:
            generateTransportAircraft(mesh);
            break;
        case AircraftStyle::Simple:
        default:
            generateSimpleAircraft(mesh);
            break;
        }

        // Calculate normals
        calculateNormals(mesh);

        // Update counts
        mesh.vertexCount = static_cast<uint32_t>(mesh.vertices.size());
        mesh.triangleCount = static_cast<uint32_t>(mesh.indices.size()) / 3;

        return mesh;
    }

    /**
     * @brief Set aircraft parameters
     *
     * @param aircraftParams New parameters
     */
    void setParams(const AircraftParams &aircraftParams)
    {
        DEBUG_LOG("Setting aircraft parameters");
        params = aircraftParams;
    }

    /**
     * @brief Get current aircraft parameters
     *
     * @return Current parameters
     */
    const AircraftParams &getParams() const
    {
        return params;
    }

private:
    /**
     * @brief Generate simple abstract aircraft
     *
     * @param mesh Output mesh data
     */
    void generateSimpleAircraft(MeshData &mesh)
    {
        DEBUG_LOG("Generating simple aircraft mesh");
        // Aircraft is oriented along +X axis (forward)
        float halfLength = params.length * 0.5f;
        float halfWingspan = params.wingspan * 0.5f;
        float halfHeight = params.height * 0.5f;
        float halfWidth = params.fuselageWidth * 0.5f;
        float wingThick = params.wingThickness * 0.5f;

        // Fuselage vertices (simplified box with tapered ends)
        addFuselageVertices(mesh, halfLength, halfWidth, halfHeight);

        // Wing vertices
        addWingVertices(mesh, halfLength * 0.3f, halfWingspan, wingThick);

        // Tail vertices
        addTailVertices(mesh, halfLength, halfWingspan * params.tailSize, halfHeight);

        // Generate UV coordinates
        generateUVCoordinates(mesh);
    }

    /**
     * @brief Generate fighter-style aircraft
     *
     * @param mesh Output mesh data
     */
    void generateFighterAircraft(MeshData &mesh)
    {
        DEBUG_LOG("Generating fighter aircraft mesh");
        // Fighter has more angular design and swept wings
        float halfLength = params.length * 0.5f;
        float halfWingspan = params.wingspan * 0.5f;
        float halfHeight = params.height * 0.5f;
        float halfWidth = params.fuselageWidth * 0.5f;

        // Pointed fuselage
        addPointedFuselage(mesh, halfLength, halfWidth, halfHeight);

        // Swept wings
        addSweptWings(mesh, halfLength * 0.2f, halfWingspan, params.wingThickness);

        // Vertical tail
        addVerticalTail(mesh, halfLength * -0.8f, halfHeight * params.tailSize);

        generateUVCoordinates(mesh);
    }

    /**
     * @brief Generate civilian aircraft
     *
     * @param mesh Output mesh data
     */
    void generateCivilianAircraft(MeshData &mesh)
    {
        DEBUG_LOG("Generating civilian aircraft mesh");
        // Civilian has rounded design and straight wings
        generateSimpleAircraft(mesh); // Use simple as base

        // Add engines under wings (simple cylinders)
        addEngines(mesh, params.length * 0.1f, params.wingspan * 0.3f);

        generateUVCoordinates(mesh);
    }

    /**
     * @brief Generate transport aircraft
     *
     * @param mesh Output mesh data
     */
    void generateTransportAircraft(MeshData &mesh)
    {
        DEBUG_LOG("Generating transport aircraft mesh");
        // Transport is larger and more boxy
        AircraftParams originalParams = params;
        params.fuselageWidth *= 1.5f;
        params.height *= 1.2f;

        generateSimpleAircraft(mesh);

        params = originalParams; // Restore original params
        generateUVCoordinates(mesh);
    }

    /**
     * @brief Add fuselage vertices to mesh
     *
     * @param mesh Output mesh
     * @param halfLength Half length of fuselage
     * @param halfWidth Half width of fuselage
     * @param halfHeight Half height of fuselage
     */
    void addFuselageVertices(MeshData &mesh, float halfLength, float halfWidth, float halfHeight)
    {
        uint32_t baseIndex = static_cast<uint32_t>(mesh.vertices.size());

        // Simplified fuselage as tapered box
        // Front (pointed)
        mesh.vertices.push_back({{halfLength, 0, 0}, {0, 0, 0}, {0.5f, 0.5f}});

        // Middle section (8 vertices for box)
        float midX = 0.0f;
        mesh.vertices.push_back({{midX, -halfWidth, -halfHeight}, {0, 0, 0}, {0.3f, 0.2f}});
        mesh.vertices.push_back({{midX, halfWidth, -halfHeight}, {0, 0, 0}, {0.7f, 0.2f}});
        mesh.vertices.push_back({{midX, halfWidth, halfHeight}, {0, 0, 0}, {0.7f, 0.8f}});
        mesh.vertices.push_back({{midX, -halfWidth, halfHeight}, {0, 0, 0}, {0.3f, 0.8f}});

        // Rear section (4 vertices, smaller)
        float rearX = -halfLength * 0.8f;
        float rearScale = 0.5f;
        mesh.vertices.push_back({{rearX, -halfWidth * rearScale, -halfHeight * rearScale}, {0, 0, 0}, {0.4f, 0.3f}});
        mesh.vertices.push_back({{rearX, halfWidth * rearScale, -halfHeight * rearScale}, {0, 0, 0}, {0.6f, 0.3f}});
        mesh.vertices.push_back({{rearX, halfWidth * rearScale, halfHeight * rearScale}, {0, 0, 0}, {0.6f, 0.7f}});
        mesh.vertices.push_back({{rearX, -halfWidth * rearScale, halfHeight * rearScale}, {0, 0, 0}, {0.4f, 0.7f}});

        // Tail point
        mesh.vertices.push_back({{-halfLength, 0, 0}, {0, 0, 0}, {0.1f, 0.5f}});

        // Connect sections with triangles
        // Front to middle
        addQuad(mesh, baseIndex + 0, baseIndex + 1, baseIndex + 2, baseIndex + 0); // Front triangle
        addQuad(mesh, baseIndex + 0, baseIndex + 2, baseIndex + 3, baseIndex + 0); // Front triangle
        addQuad(mesh, baseIndex + 0, baseIndex + 3, baseIndex + 4, baseIndex + 0); // Front triangle
        addQuad(mesh, baseIndex + 0, baseIndex + 4, baseIndex + 1, baseIndex + 0); // Front triangle

        // Middle to rear
        addQuad(mesh, baseIndex + 1, baseIndex + 5, baseIndex + 6, baseIndex + 2);
        addQuad(mesh, baseIndex + 2, baseIndex + 6, baseIndex + 7, baseIndex + 3);
        addQuad(mesh, baseIndex + 3, baseIndex + 7, baseIndex + 8, baseIndex + 4);
        addQuad(mesh, baseIndex + 4, baseIndex + 8, baseIndex + 5, baseIndex + 1);

        // Rear to tail
        addTriangle(mesh, baseIndex + 5, baseIndex + 9, baseIndex + 6);
        addTriangle(mesh, baseIndex + 6, baseIndex + 9, baseIndex + 7);
        addTriangle(mesh, baseIndex + 7, baseIndex + 9, baseIndex + 8);
        addTriangle(mesh, baseIndex + 8, baseIndex + 9, baseIndex + 5);
    }

    /**
     * @brief Add wing vertices to mesh
     *
     * @param mesh Output mesh
     * @param centerX Center X position of wings
     * @param halfSpan Half wingspan
     * @param thickness Wing thickness
     */
    void addWingVertices(MeshData &mesh, float centerX, float halfSpan, float thickness)
    {
        uint32_t baseIndex = static_cast<uint32_t>(mesh.vertices.size());

        // Wing root (near fuselage)
        float rootChord = params.length * 0.3f;
        float rootX1 = centerX + rootChord * 0.5f;
        float rootX2 = centerX - rootChord * 0.5f;

        // Wing tip
        float tipChord = rootChord * 0.5f;
        float tipX1 = centerX + tipChord * 0.5f;
        float tipX2 = centerX - tipChord * 0.5f;

        // Wing vertices (top and bottom for each position)
        // Left wing
        mesh.vertices.push_back({{rootX1, 0, thickness}, {0, 0, 0}, {0.8f, 0.2f}});         // Root leading top
        mesh.vertices.push_back({{rootX2, 0, thickness}, {0, 0, 0}, {0.2f, 0.2f}});         // Root trailing top
        mesh.vertices.push_back({{tipX1, -halfSpan, thickness}, {0, 0, 0}, {0.8f, 0.0f}});  // Tip leading top
        mesh.vertices.push_back({{tipX2, -halfSpan, thickness}, {0, 0, 0}, {0.2f, 0.0f}});  // Tip trailing top
        mesh.vertices.push_back({{rootX1, 0, -thickness}, {0, 0, 0}, {0.8f, 0.4f}});        // Root leading bottom
        mesh.vertices.push_back({{rootX2, 0, -thickness}, {0, 0, 0}, {0.2f, 0.4f}});        // Root trailing bottom
        mesh.vertices.push_back({{tipX1, -halfSpan, -thickness}, {0, 0, 0}, {0.8f, 0.6f}}); // Tip leading bottom
        mesh.vertices.push_back({{tipX2, -halfSpan, -thickness}, {0, 0, 0}, {0.2f, 0.6f}}); // Tip trailing bottom

        // Right wing (mirror)
        mesh.vertices.push_back({{rootX1, 0, thickness}, {0, 0, 0}, {0.8f, 0.2f}});        // Root leading top
        mesh.vertices.push_back({{rootX2, 0, thickness}, {0, 0, 0}, {0.2f, 0.2f}});        // Root trailing top
        mesh.vertices.push_back({{tipX1, halfSpan, thickness}, {0, 0, 0}, {0.8f, 1.0f}});  // Tip leading top
        mesh.vertices.push_back({{tipX2, halfSpan, thickness}, {0, 0, 0}, {0.2f, 1.0f}});  // Tip trailing top
        mesh.vertices.push_back({{rootX1, 0, -thickness}, {0, 0, 0}, {0.8f, 0.4f}});       // Root leading bottom
        mesh.vertices.push_back({{rootX2, 0, -thickness}, {0, 0, 0}, {0.2f, 0.4f}});       // Root trailing bottom
        mesh.vertices.push_back({{tipX1, halfSpan, -thickness}, {0, 0, 0}, {0.8f, 0.8f}}); // Tip leading bottom
        mesh.vertices.push_back({{tipX2, halfSpan, -thickness}, {0, 0, 0}, {0.2f, 0.8f}}); // Tip trailing bottom

        // Wing surface triangles
        // Left wing top
        addQuad(mesh, baseIndex + 0, baseIndex + 2, baseIndex + 3, baseIndex + 1);
        // Left wing bottom
        addQuad(mesh, baseIndex + 4, baseIndex + 5, baseIndex + 7, baseIndex + 6);

        // Right wing top
        addQuad(mesh, baseIndex + 8, baseIndex + 9, baseIndex + 11, baseIndex + 10);
        // Right wing bottom
        addQuad(mesh, baseIndex + 12, baseIndex + 14, baseIndex + 15, baseIndex + 13);
    }

    /**
     * @brief Add tail vertices to mesh
     *
     * @param mesh Output mesh
     * @param rearX X position of tail
     * @param halfSpan Half span of tail
     * @param height Height of vertical tail
     */
    void addTailVertices(MeshData &mesh, float rearX, float halfSpan, float height)
    {
        uint32_t baseIndex = static_cast<uint32_t>(mesh.vertices.size());

        // Simple vertical tail
        float tailX1 = rearX * 0.8f;
        float tailX2 = rearX * 1.0f;
        float tailThickness = params.wingThickness * 0.5f;

        // Vertical tail vertices
        mesh.vertices.push_back({{tailX1, 0, height}, {0, 0, 0}, {0.9f, 0.9f}});
        mesh.vertices.push_back({{tailX2, 0, height * 0.5f}, {0, 0, 0}, {1.0f, 0.7f}});
        mesh.vertices.push_back({{tailX1, 0, 0}, {0, 0, 0}, {0.9f, 0.5f}});

        // Simple triangle
        addTriangle(mesh, baseIndex + 0, baseIndex + 1, baseIndex + 2);
    }

    /**
     * @brief Add pointed fuselage for fighter aircraft
     */
    void addPointedFuselage(MeshData &mesh, float halfLength, float halfWidth, float halfHeight)
    {
        // Similar to regular fuselage but more pointed
        addFuselageVertices(mesh, halfLength, halfWidth, halfHeight);
    }

    /**
     * @brief Add swept wings for fighter aircraft
     */
    void addSweptWings(MeshData &mesh, float centerX, float halfSpan, float thickness)
    {
        // Similar to regular wings but with sweep angle
        addWingVertices(mesh, centerX, halfSpan, thickness);
    }

    /**
     * @brief Add vertical tail for fighter aircraft
     */
    void addVerticalTail(MeshData &mesh, float rearX, float height)
    {
        addTailVertices(mesh, rearX, height * 0.3f, height);
    }

    /**
     * @brief Add engines for civilian aircraft
     */
    void addEngines(MeshData &mesh, float engineX, float engineY)
    {
        // Simple cylindrical engines under wings
        uint32_t baseIndex = static_cast<uint32_t>(mesh.vertices.size());

        float engineLength = params.length * 0.2f;
        float engineRadius = params.fuselageWidth * 0.3f;

        // Simple box engines
        for (int side = -1; side <= 1; side += 2)
        {
            float y = engineY * side;

            // Engine box vertices
            mesh.vertices.push_back({{engineX + engineLength, y - engineRadius, -engineRadius}, {0, 0, 0}, {0.1f, 0.1f}});
            mesh.vertices.push_back({{engineX + engineLength, y + engineRadius, -engineRadius}, {0, 0, 0}, {0.2f, 0.1f}});
            mesh.vertices.push_back({{engineX + engineLength, y + engineRadius, engineRadius}, {0, 0, 0}, {0.2f, 0.2f}});
            mesh.vertices.push_back({{engineX + engineLength, y - engineRadius, engineRadius}, {0, 0, 0}, {0.1f, 0.2f}});

            mesh.vertices.push_back({{engineX - engineLength, y - engineRadius, -engineRadius}, {0, 0, 0}, {0.0f, 0.1f}});
            mesh.vertices.push_back({{engineX - engineLength, y + engineRadius, -engineRadius}, {0, 0, 0}, {0.3f, 0.1f}});
            mesh.vertices.push_back({{engineX - engineLength, y + engineRadius, engineRadius}, {0, 0, 0}, {0.3f, 0.2f}});
            mesh.vertices.push_back({{engineX - engineLength, y - engineRadius, engineRadius}, {0, 0, 0}, {0.0f, 0.2f}});
        }
    }

    /**
     * @brief Add a quad (4 vertices) as two triangles
     */
    void addQuad(MeshData &mesh, uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3)
    {
        mesh.indices.insert(mesh.indices.end(), {v0, v1, v2});
        mesh.indices.insert(mesh.indices.end(), {v0, v2, v3});
    }

    /**
     * @brief Add a triangle
     */
    void addTriangle(MeshData &mesh, uint32_t v0, uint32_t v1, uint32_t v2)
    {
        mesh.indices.insert(mesh.indices.end(), {v0, v1, v2});
    }

    /**
     * @brief Calculate normals for all vertices
     */
    void calculateNormals(MeshData &mesh)
    {
        DEBUG_LOG("Calculating normals for aircraft mesh");
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

    /**
     * @brief Generate UV coordinates for all vertices
     */
    void generateUVCoordinates(MeshData &mesh)
    {
        // UV coordinates are already set during vertex creation
        // This function could be used for post-processing UV coordinates if needed
    }
};
