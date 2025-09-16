#pragma once
#include <vector>
#include <memory>
#include "../math/MathUtils.h"

/**
 * @file ProceduralMeshGenerators.h
 * @brief Collection of procedural mesh generation utilities.
 *
 * This file contains various mesh generators used for creating low-poly
 * geometry procedurally, including spheres, cubes, and aircraft meshes
 * for the voxel busy indicator scene.
 */

/**
 * @struct Vertex
 * @brief Basic vertex structure for procedural mesh generation.
 */
struct Vertex
{
    Vector3D position;
    Vector3D normal;
    float u, v; // UV coordinates

    Vertex(Vector3D pos = Vector3D(), Vector3D norm = Vector3D(), float texU = 0.0f, float texV = 0.0f)
        : position(pos), normal(norm), u(texU), v(texV) {}
};

/**
 * @struct ProceduralMesh
 * @brief Container for generated mesh data.
 */
struct ProceduralMesh
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    ProceduralMesh() = default;

    void clear()
    {
        vertices.clear();
        indices.clear();
    }

    size_t getVertexCount() const { return vertices.size(); }
    size_t getTriangleCount() const { return indices.size() / 3; }
};

/**
 * @class IcoSphereGenerator
 * @brief Generates low-poly icospheres with flat shading.
 *
 * Creates spherical meshes using icosahedral subdivision for consistent
 * triangle distribution. Ideal for the voxel busy indicator globe.
 */
class IcoSphereGenerator
{
public:
    /**
     * @brief Generate an icosphere mesh.
     *
     * @param radius Radius of the sphere
     * @param subdivisions Number of subdivision levels (0-3 recommended)
     * @param flatShading Whether to use flat shading (duplicate vertices)
     * @return Generated mesh data
     */
    static ProceduralMesh generate(float radius = 1.0f, int subdivisions = 2, bool flatShading = true);

private:
    static void addVertex(std::vector<Vector3D> &vertices, const Vector3D &v);
    static int getMiddlePoint(int p1, int p2, std::vector<Vector3D> &vertices, std::map<long, int> &cache, float radius);
    static void calculateUV(const Vector3D &vertex, float &u, float &v);
};

/**
 * @class CubeGenerator
 * @brief Generates simple cube meshes with flat shading.
 *
 * Creates basic cube geometry for voxel clouds and contrail elements.
 */
class CubeGenerator
{
public:
    /**
     * @brief Generate a cube mesh.
     *
     * @param size Side length of the cube
     * @param flatShading Whether to use flat shading (separate faces)
     * @return Generated mesh data
     */
    static ProceduralMesh generate(float size = 1.0f, bool flatShading = true);

private:
    static void addQuad(ProceduralMesh &mesh,
                        const Vector3D &v1, const Vector3D &v2,
                        const Vector3D &v3, const Vector3D &v4,
                        const Vector3D &normal);
};

/**
 * @class ProceduralAircraftGenerator
 * @brief Generates low-poly aircraft meshes.
 *
 * Creates simple aircraft geometry with fuselage, wings, and tail
 * suitable for the busy indicator scene.
 */
class ProceduralAircraftGenerator
{
public:
    /**
     * @brief Generate an aircraft mesh.
     *
     * @param length Fuselage length
     * @param fuselageSegments Number of fuselage segments
     * @param wingSpan Wing span distance
     * @param tailSpan Tail span distance
     * @param flatShading Whether to use flat shading
     * @return Generated mesh data
     */
    static ProceduralMesh generate(float length = 0.25f,
                                   int fuselageSegments = 6,
                                   float wingSpan = 0.22f,
                                   float tailSpan = 0.12f,
                                   bool flatShading = true);

private:
    static void addFuselage(ProceduralMesh &mesh, float length, int segments);
    static void addWings(ProceduralMesh &mesh, float span, float length);
    static void addTail(ProceduralMesh &mesh, float span, float length);
};

/**
 * @class SphericalPatchDisplaceGenerator
 * @brief Generates displaced spherical patches for terrain bumps.
 *
 * Creates land masses and rock formations on the globe surface
 * by displacing spherical patches outward.
 */
class SphericalPatchDisplaceGenerator
{
public:
    /**
     * @brief Generate displaced spherical patches.
     *
     * @param baseRadius Base sphere radius
     * @param subdivisions Sphere subdivision level
     * @param patchCount Number of displacement patches
     * @param minHeight Minimum displacement height
     * @param maxHeight Maximum displacement height
     * @param seed Random seed (-1 for random)
     * @return Generated mesh data
     */
    static ProceduralMesh generate(float baseRadius = 1.0f,
                                   int subdivisions = 2,
                                   int patchCount = 24,
                                   float minHeight = 0.03f,
                                   float maxHeight = 0.06f,
                                   int seed = -1);

private:
    static bool isInPatch(const Vector3D &vertex, const Vector3D &patchCenter, float patchRadius);
    static float calculateDisplacement(const Vector3D &vertex, const Vector3D &patchCenter,
                                       float patchRadius, float minHeight, float maxHeight);
};

