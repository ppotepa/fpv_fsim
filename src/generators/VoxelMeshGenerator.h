#pragma once
#include "../math/MathUtils.h"
#include <vector>
#include <string>
#include <map>

/**
 * @file VoxelMeshGenerator.h
 * @brief Generic voxel-based mesh generation system
 *
 * This generator creates all mesh types using voxel primitives as building blocks.
 * Supports cubes, spheres, cylinders, and compound meshes built from multiple primitives.
 * All generation is deterministic and configurable through parameters.
 */

namespace VoxelMesh
{

    /**
     * @brief Vertex data structure for generated meshes
     */
    struct Vertex
    {
        Math::float3 position;
        Math::float3 normal;
        Math::float2 uv;

        Vertex() = default;
        Vertex(const Math::float3 &pos, const Math::float3 &norm, const Math::float2 &texCoord)
            : position(pos), normal(norm), uv(texCoord) {}
    };

    /**
     * @brief Generated mesh data
     */
    struct MeshData
    {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::string name;

        void clear()
        {
            vertices.clear();
            indices.clear();
            name.clear();
        }

        bool isEmpty() const
        {
            return vertices.empty() || indices.empty();
        }
    };

    /**
     * @brief Voxel primitive types
     */
    enum class VoxelType
    {
        Cube,
        Sphere,
        Cylinder,
        Plane
    };

    /**
     * @brief Parameters for voxel primitive generation
     */
    struct VoxelParams
    {
        VoxelType type = VoxelType::Cube;
        float size = 1.0f;            // Size for cubes/planes
        float radius = 1.0f;          // Radius for spheres/cylinders
        float height = 1.0f;          // Height for cylinders
        uint32_t subdivisions = 1;    // Level of detail
        Math::float3 center{0, 0, 0}; // Center position

        VoxelParams() = default;
        VoxelParams(VoxelType t, float s = 1.0f) : type(t), size(s), radius(s) {}
    };

    /**
     * @brief Parameters for compound mesh (multiple primitives)
     */
    struct CompoundPart
    {
        VoxelParams primitive;
        Math::float3 offset{0, 0, 0};
        Math::float3 scale{1, 1, 1};
        std::string name;

        CompoundPart() = default;
        CompoundPart(const VoxelParams &prim, const Math::float3 &pos = {0, 0, 0})
            : primitive(prim), offset(pos) {}
    };

    /**
     * @brief Parameters for compound meshes
     */
    struct CompoundParams
    {
        std::vector<CompoundPart> parts;
        std::string name;

        void addPart(const CompoundPart &part)
        {
            parts.push_back(part);
        }

        void addPart(const VoxelParams &primitive, const Math::float3 &offset = {0, 0, 0})
        {
            parts.emplace_back(primitive, offset);
        }
    };

} // namespace VoxelMesh

/**
 * @brief Generic voxel mesh generator
 *
 * Creates meshes from voxel primitives with configurable parameters.
 * All shapes are built from the same base system for consistency.
 */
class VoxelMeshGenerator
{
public:
    VoxelMeshGenerator() = default;
    ~VoxelMeshGenerator() = default;

    // ============================================================================
    // Primary Generation Methods
    // ============================================================================

    /**
     * @brief Generate a single voxel primitive
     * @param params Primitive parameters
     * @return Generated mesh data
     */
    VoxelMesh::MeshData generatePrimitive(const VoxelMesh::VoxelParams &params);

    /**
     * @brief Generate a compound mesh from multiple primitives
     * @param params Compound mesh parameters
     * @return Generated mesh data
     */
    VoxelMesh::MeshData generateCompound(const VoxelMesh::CompoundParams &params);

    /**
     * @brief Generate mesh from string parameters (for XML parsing)
     * @param type Primitive type as string
     * @param parameters Parameter map
     * @return Generated mesh data
     */
    VoxelMesh::MeshData generateFromParameters(const std::string &type,
                                               const std::map<std::string, std::string> &parameters);

    // ============================================================================
    // Utility Methods
    // ============================================================================

    /**
     * @brief Parse voxel type from string
     * @param typeStr Type string ("cube", "sphere", etc.)
     * @return Voxel type enum
     */
    static VoxelMesh::VoxelType parseVoxelType(const std::string &typeStr);

    /**
     * @brief Get voxel type as string
     * @param type Voxel type enum
     * @return Type string
     */
    static std::string voxelTypeToString(VoxelMesh::VoxelType type);

    /**
     * @brief Calculate approximate vertex count for primitive
     * @param params Primitive parameters
     * @return Estimated vertex count
     */
    static uint32_t estimateVertexCount(const VoxelMesh::VoxelParams &params);

private:
    // ============================================================================
    // Primitive Generation Methods
    // ============================================================================

    VoxelMesh::MeshData generateCube(const VoxelMesh::VoxelParams &params);
    VoxelMesh::MeshData generateSphere(const VoxelMesh::VoxelParams &params);
    VoxelMesh::MeshData generateCylinder(const VoxelMesh::VoxelParams &params);
    VoxelMesh::MeshData generatePlane(const VoxelMesh::VoxelParams &params);

    // ============================================================================
    // Helper Methods
    // ============================================================================

    /**
     * @brief Add a quad to mesh data
     */
    void addQuad(VoxelMesh::MeshData &mesh,
                 const Math::float3 &v0, const Math::float3 &v1,
                 const Math::float3 &v2, const Math::float3 &v3,
                 const Math::float3 &normal);

    /**
     * @brief Add a triangle to mesh data
     */
    void addTriangle(VoxelMesh::MeshData &mesh,
                     const Math::float3 &v0, const Math::float3 &v1, const Math::float3 &v2,
                     const Math::float3 &normal);

    /**
     * @brief Calculate UV coordinates for a vertex on a sphere
     */
    Math::float2 calculateSphericalUV(const Math::float3 &position);

    /**
     * @brief Calculate UV coordinates for a vertex on a cube face
     */
    Math::float2 calculateCubicUV(const Math::float3 &position, int faceIndex);

    /**
     * @brief Generate vertices for subdivided icosphere
     */
    void generateIcosphere(VoxelMesh::MeshData &mesh, const VoxelMesh::VoxelParams &params);

    /**
     * @brief Merge multiple mesh data objects
     */
    VoxelMesh::MeshData mergeMeshes(const std::vector<VoxelMesh::MeshData> &meshes);

    /**
     * @brief Transform mesh vertices
     */
    void transformMesh(VoxelMesh::MeshData &mesh, const Math::float3 &offset, const Math::float3 &scale);

    /**
     * @brief Calculate normals for mesh (if not provided)
     */
    void calculateNormals(VoxelMesh::MeshData &mesh);

    /**
     * @brief Optimize mesh (remove duplicates, etc.)
     */
    void optimizeMesh(VoxelMesh::MeshData &mesh);
};

