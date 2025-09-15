#include "VoxelMeshGenerator.h"
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <array>

// ============================================================================
// Public Generation Methods
// ============================================================================

VoxelMesh::MeshData VoxelMeshGenerator::generatePrimitive(const VoxelMesh::VoxelParams &params)
{
    switch (params.type)
    {
    case VoxelMesh::VoxelType::Cube:
        return generateCube(params);
    case VoxelMesh::VoxelType::Sphere:
        return generateSphere(params);
    case VoxelMesh::VoxelType::Cylinder:
        return generateCylinder(params);
    case VoxelMesh::VoxelType::Plane:
        return generatePlane(params);
    default:
        return generateCube(params); // Default fallback
    }
}

VoxelMesh::MeshData VoxelMeshGenerator::generateCompound(const VoxelMesh::CompoundParams &params)
{
    std::vector<VoxelMesh::MeshData> meshes;
    meshes.reserve(params.parts.size());

    for (const auto &part : params.parts)
    {
        auto mesh = generatePrimitive(part.primitive);
        transformMesh(mesh, part.offset, part.scale);
        meshes.push_back(std::move(mesh));
    }

    auto result = mergeMeshes(meshes);
    result.name = params.name;
    optimizeMesh(result);
    return result;
}

VoxelMesh::MeshData VoxelMeshGenerator::generateFromParameters(const std::string &type,
                                                               const std::map<std::string, std::string> &parameters)
{
    VoxelMesh::VoxelParams params;
    params.type = parseVoxelType(type);

    // Parse common parameters
    auto it = parameters.find("size");
    if (it != parameters.end())
    {
        params.size = std::stof(it->second);
    }

    it = parameters.find("radius");
    if (it != parameters.end())
    {
        params.radius = std::stof(it->second);
    }

    it = parameters.find("height");
    if (it != parameters.end())
    {
        params.height = std::stof(it->second);
    }

    it = parameters.find("subdivisions");
    if (it != parameters.end())
    {
        params.subdivisions = static_cast<uint32_t>(std::stoi(it->second));
    }

    return generatePrimitive(params);
}

// ============================================================================
// Utility Methods
// ============================================================================

VoxelMesh::VoxelType VoxelMeshGenerator::parseVoxelType(const std::string &typeStr)
{
    if (typeStr == "cube")
        return VoxelMesh::VoxelType::Cube;
    if (typeStr == "sphere")
        return VoxelMesh::VoxelType::Sphere;
    if (typeStr == "cylinder")
        return VoxelMesh::VoxelType::Cylinder;
    if (typeStr == "plane")
        return VoxelMesh::VoxelType::Plane;
    return VoxelMesh::VoxelType::Cube; // Default fallback
}

std::string VoxelMeshGenerator::voxelTypeToString(VoxelMesh::VoxelType type)
{
    switch (type)
    {
    case VoxelMesh::VoxelType::Cube:
        return "cube";
    case VoxelMesh::VoxelType::Sphere:
        return "sphere";
    case VoxelMesh::VoxelType::Cylinder:
        return "cylinder";
    case VoxelMesh::VoxelType::Plane:
        return "plane";
    default:
        return "cube";
    }
}

uint32_t VoxelMeshGenerator::estimateVertexCount(const VoxelMesh::VoxelParams &params)
{
    switch (params.type)
    {
    case VoxelMesh::VoxelType::Cube:
        return 24; // 6 faces * 4 vertices
    case VoxelMesh::VoxelType::Sphere:
        return params.subdivisions * params.subdivisions * 6; // Approximation for icosphere
    case VoxelMesh::VoxelType::Cylinder:
        return params.subdivisions * 4 + 2; // Side faces + top/bottom
    case VoxelMesh::VoxelType::Plane:
        return 4;
    default:
        return 24;
    }
}

// ============================================================================
// Primitive Generation Implementation
// ============================================================================

VoxelMesh::MeshData VoxelMeshGenerator::generateCube(const VoxelMesh::VoxelParams &params)
{
    VoxelMesh::MeshData mesh;
    mesh.name = "cube";

    const float halfSize = params.size * 0.5f;
    const Math::float3 center = params.center;

    // Define cube faces with normals
    struct Face
    {
        Math::float3 vertices[4];
        Math::float3 normal;
    };

    Face faces[6] = {
        // Front face (+Z)
        {{{-halfSize, -halfSize, halfSize}, {halfSize, -halfSize, halfSize}, {halfSize, halfSize, halfSize}, {-halfSize, halfSize, halfSize}},
         {0, 0, 1}},
        // Back face (-Z)
        {{{halfSize, -halfSize, -halfSize}, {-halfSize, -halfSize, -halfSize}, {-halfSize, halfSize, -halfSize}, {halfSize, halfSize, -halfSize}},
         {0, 0, -1}},
        // Right face (+X)
        {{{halfSize, -halfSize, halfSize}, {halfSize, -halfSize, -halfSize}, {halfSize, halfSize, -halfSize}, {halfSize, halfSize, halfSize}},
         {1, 0, 0}},
        // Left face (-X)
        {{{-halfSize, -halfSize, -halfSize}, {-halfSize, -halfSize, halfSize}, {-halfSize, halfSize, halfSize}, {-halfSize, halfSize, -halfSize}},
         {-1, 0, 0}},
        // Top face (+Y)
        {{{-halfSize, halfSize, halfSize}, {halfSize, halfSize, halfSize}, {halfSize, halfSize, -halfSize}, {-halfSize, halfSize, -halfSize}},
         {0, 1, 0}},
        // Bottom face (-Y)
        {{{-halfSize, -halfSize, -halfSize}, {halfSize, -halfSize, -halfSize}, {halfSize, -halfSize, halfSize}, {-halfSize, -halfSize, halfSize}},
         {0, -1, 0}}};

    // Generate vertices and indices for each face
    for (int face = 0; face < 6; ++face)
    {
        Math::float3 v0 = Math::add(faces[face].vertices[0], center);
        Math::float3 v1 = Math::add(faces[face].vertices[1], center);
        Math::float3 v2 = Math::add(faces[face].vertices[2], center);
        Math::float3 v3 = Math::add(faces[face].vertices[3], center);

        addQuad(mesh, v0, v1, v2, v3, faces[face].normal);
    }

    return mesh;
}

VoxelMesh::MeshData VoxelMeshGenerator::generateSphere(const VoxelMesh::VoxelParams &params)
{
    VoxelMesh::MeshData mesh;
    mesh.name = "sphere";

    if (params.subdivisions <= 1)
    {
        // Generate basic icosphere for low subdivision
        generateIcosphere(mesh, params);
    }
    else
    {
        // Generate UV sphere for higher subdivisions
        const uint32_t rings = params.subdivisions;
        const uint32_t sectors = params.subdivisions * 2;
        const float radius = params.radius;
        const Math::float3 center = params.center;

        mesh.vertices.reserve((rings + 1) * (sectors + 1));
        mesh.indices.reserve(rings * sectors * 6);

        // Generate vertices
        for (uint32_t r = 0; r <= rings; ++r)
        {
            float y = radius * std::cos(Math::PI * r / rings);
            float ringRadius = radius * std::sin(Math::PI * r / rings);

            for (uint32_t s = 0; s <= sectors; ++s)
            {
                float x = ringRadius * std::cos(2.0f * Math::PI * s / sectors);
                float z = ringRadius * std::sin(2.0f * Math::PI * s / sectors);

                Math::float3 position = Math::add(Math::float3{x, y, z}, center);
                Math::float3 normal = Math::normalize(Math::float3{x, y, z});
                Math::float2 uv = {static_cast<float>(s) / sectors, static_cast<float>(r) / rings};

                mesh.vertices.emplace_back(position, normal, uv);
            }
        }

        // Generate indices
        for (uint32_t r = 0; r < rings; ++r)
        {
            for (uint32_t s = 0; s < sectors; ++s)
            {
                uint32_t current = r * (sectors + 1) + s;
                uint32_t next = current + sectors + 1;

                // Two triangles per quad
                mesh.indices.push_back(current);
                mesh.indices.push_back(next);
                mesh.indices.push_back(current + 1);

                mesh.indices.push_back(current + 1);
                mesh.indices.push_back(next);
                mesh.indices.push_back(next + 1);
            }
        }
    }

    return mesh;
}

VoxelMesh::MeshData VoxelMeshGenerator::generateCylinder(const VoxelMesh::VoxelParams &params)
{
    VoxelMesh::MeshData mesh;
    mesh.name = "cylinder";

    const float radius = params.radius;
    const float height = params.height;
    const float halfHeight = height * 0.5f;
    const uint32_t segments = std::max(3u, params.subdivisions * 8);
    const Math::float3 center = params.center;

    mesh.vertices.reserve(segments * 4 + 2);
    mesh.indices.reserve(segments * 12);

    // Generate side vertices
    for (uint32_t i = 0; i < segments; ++i)
    {
        float angle = 2.0f * Math::PI * i / segments;
        float x = radius * std::cos(angle);
        float z = radius * std::sin(angle);

        Math::float3 bottomPos = Math::add(Math::float3{x, -halfHeight, z}, center);
        Math::float3 topPos = Math::add(Math::float3{x, halfHeight, z}, center);
        Math::float3 normal = Math::normalize(Math::float3{x, 0, z});
        Math::float2 uvBottom = {static_cast<float>(i) / segments, 0.0f};
        Math::float2 uvTop = {static_cast<float>(i) / segments, 1.0f};

        mesh.vertices.emplace_back(bottomPos, normal, uvBottom);
        mesh.vertices.emplace_back(topPos, normal, uvTop);
    }

    // Add center vertices for caps
    uint32_t bottomCenterIdx = mesh.vertices.size();
    mesh.vertices.emplace_back(Math::add(Math::float3{0, -halfHeight, 0}, center), Math::float3{0, -1, 0}, Math::float2{0.5f, 0.5f});
    uint32_t topCenterIdx = mesh.vertices.size();
    mesh.vertices.emplace_back(Math::add(Math::float3{0, halfHeight, 0}, center), Math::float3{0, 1, 0}, Math::float2{0.5f, 0.5f});

    // Generate side faces
    for (uint32_t i = 0; i < segments; ++i)
    {
        uint32_t current = i * 2;
        uint32_t next = ((i + 1) % segments) * 2;

        // Two triangles per side quad
        mesh.indices.push_back(current);
        mesh.indices.push_back(next);
        mesh.indices.push_back(current + 1);

        mesh.indices.push_back(current + 1);
        mesh.indices.push_back(next);
        mesh.indices.push_back(next + 1);
    }

    // Generate cap faces
    for (uint32_t i = 0; i < segments; ++i)
    {
        uint32_t current = i * 2;
        uint32_t next = ((i + 1) % segments) * 2;

        // Bottom cap
        mesh.indices.push_back(bottomCenterIdx);
        mesh.indices.push_back(next);
        mesh.indices.push_back(current);

        // Top cap
        mesh.indices.push_back(topCenterIdx);
        mesh.indices.push_back(current + 1);
        mesh.indices.push_back(next + 1);
    }

    return mesh;
}

VoxelMesh::MeshData VoxelMeshGenerator::generatePlane(const VoxelMesh::VoxelParams &params)
{
    VoxelMesh::MeshData mesh;
    mesh.name = "plane";

    const float halfSize = params.size * 0.5f;
    const Math::float3 center = params.center;

    Math::float3 v0 = Math::add({-halfSize, 0, -halfSize}, center);
    Math::float3 v1 = Math::add({halfSize, 0, -halfSize}, center);
    Math::float3 v2 = Math::add({halfSize, 0, halfSize}, center);
    Math::float3 v3 = Math::add({-halfSize, 0, halfSize}, center);

    addQuad(mesh, v0, v1, v2, v3, {0, 1, 0});

    return mesh;
}

// ============================================================================
// Helper Methods Implementation
// ============================================================================

void VoxelMeshGenerator::addQuad(VoxelMesh::MeshData &mesh,
                                 const Math::float3 &v0, const Math::float3 &v1,
                                 const Math::float3 &v2, const Math::float3 &v3,
                                 const Math::float3 &normal)
{
    uint32_t startIdx = mesh.vertices.size();

    // Add vertices with UVs
    mesh.vertices.emplace_back(v0, normal, Math::float2{0, 0});
    mesh.vertices.emplace_back(v1, normal, Math::float2{1, 0});
    mesh.vertices.emplace_back(v2, normal, Math::float2{1, 1});
    mesh.vertices.emplace_back(v3, normal, Math::float2{0, 1});

    // Add indices for two triangles
    mesh.indices.push_back(startIdx);
    mesh.indices.push_back(startIdx + 1);
    mesh.indices.push_back(startIdx + 2);

    mesh.indices.push_back(startIdx);
    mesh.indices.push_back(startIdx + 2);
    mesh.indices.push_back(startIdx + 3);
}

void VoxelMeshGenerator::addTriangle(VoxelMesh::MeshData &mesh,
                                     const Math::float3 &v0, const Math::float3 &v1, const Math::float3 &v2,
                                     const Math::float3 &normal)
{
    uint32_t startIdx = mesh.vertices.size();

    mesh.vertices.emplace_back(v0, normal, Math::float2{0, 0});
    mesh.vertices.emplace_back(v1, normal, Math::float2{1, 0});
    mesh.vertices.emplace_back(v2, normal, Math::float2{0.5f, 1});

    mesh.indices.push_back(startIdx);
    mesh.indices.push_back(startIdx + 1);
    mesh.indices.push_back(startIdx + 2);
}

Math::float2 VoxelMeshGenerator::calculateSphericalUV(const Math::float3 &position)
{
    Math::float3 normalized = Math::normalize(position);
    float u = 0.5f + std::atan2(normalized.z, normalized.x) / (2.0f * Math::PI);
    float v = 0.5f - std::asin(normalized.y) / Math::PI;
    return {u, v};
}

Math::float2 VoxelMeshGenerator::calculateCubicUV(const Math::float3 &position, int faceIndex)
{
    // Simple planar projection based on face
    switch (faceIndex)
    {
    case 0:
    case 1: // Front/Back
        return {(position.x + 1.0f) * 0.5f, (position.y + 1.0f) * 0.5f};
    case 2:
    case 3: // Right/Left
        return {(position.z + 1.0f) * 0.5f, (position.y + 1.0f) * 0.5f};
    case 4:
    case 5: // Top/Bottom
        return {(position.x + 1.0f) * 0.5f, (position.z + 1.0f) * 0.5f};
    default:
        return {0.5f, 0.5f};
    }
}

void VoxelMeshGenerator::generateIcosphere(VoxelMesh::MeshData &mesh, const VoxelMesh::VoxelParams &params)
{
    // Basic icosphere implementation for low-poly spheres
    const float t = (1.0f + std::sqrt(5.0f)) / 2.0f; // Golden ratio
    const float radius = params.radius;
    const Math::float3 center = params.center;

    // Create icosahedron vertices
    std::vector<Math::float3> vertices = {
        {-1, t, 0}, {1, t, 0}, {-1, -t, 0}, {1, -t, 0}, {0, -1, t}, {0, 1, t}, {0, -1, -t}, {0, 1, -t}, {t, 0, -1}, {t, 0, 1}, {-t, 0, -1}, {-t, 0, 1}};

    // Normalize and scale
    for (auto &v : vertices)
    {
        v = Math::mul(Math::normalize(v), radius);
        v = Math::add(v, center);
    }

    // Create faces (20 triangles)
    std::vector<std::array<uint32_t, 3>> faces;
    faces.push_back(std::array<uint32_t, 3>{0, 11, 5});
    faces.push_back(std::array<uint32_t, 3>{0, 5, 1});
    faces.push_back(std::array<uint32_t, 3>{0, 1, 7});
    faces.push_back(std::array<uint32_t, 3>{0, 7, 10});
    faces.push_back(std::array<uint32_t, 3>{0, 10, 11});
    faces.push_back(std::array<uint32_t, 3>{1, 5, 9});
    faces.push_back(std::array<uint32_t, 3>{5, 11, 4});
    faces.push_back(std::array<uint32_t, 3>{11, 10, 2});
    faces.push_back(std::array<uint32_t, 3>{10, 7, 6});
    faces.push_back(std::array<uint32_t, 3>{7, 1, 8});
    faces.push_back(std::array<uint32_t, 3>{3, 9, 4});
    faces.push_back(std::array<uint32_t, 3>{3, 4, 2});
    faces.push_back(std::array<uint32_t, 3>{3, 2, 6});
    faces.push_back(std::array<uint32_t, 3>{3, 6, 8});
    faces.push_back(std::array<uint32_t, 3>{3, 8, 9});
    faces.push_back(std::array<uint32_t, 3>{4, 9, 5});
    faces.push_back(std::array<uint32_t, 3>{2, 4, 11});
    faces.push_back(std::array<uint32_t, 3>{6, 2, 10});
    faces.push_back(std::array<uint32_t, 3>{8, 6, 7});
    faces.push_back(std::array<uint32_t, 3>{9, 8, 1});

    // Add vertices and indices
    for (const auto &vertex : vertices)
    {
        Math::float3 normal = Math::normalize(Math::sub(vertex, center));
        Math::float2 uv = calculateSphericalUV(normal);
        mesh.vertices.emplace_back(vertex, normal, uv);
    }

    for (const auto &face : faces)
    {
        mesh.indices.push_back(face[0]);
        mesh.indices.push_back(face[1]);
        mesh.indices.push_back(face[2]);
    }
}

VoxelMesh::MeshData VoxelMeshGenerator::mergeMeshes(const std::vector<VoxelMesh::MeshData> &meshes)
{
    VoxelMesh::MeshData result;

    if (meshes.empty())
    {
        return result;
    }

    // Calculate total size
    uint32_t totalVertices = 0;
    uint32_t totalIndices = 0;
    for (const auto &mesh : meshes)
    {
        totalVertices += mesh.vertices.size();
        totalIndices += mesh.indices.size();
    }

    result.vertices.reserve(totalVertices);
    result.indices.reserve(totalIndices);

    // Merge meshes
    uint32_t vertexOffset = 0;
    for (const auto &mesh : meshes)
    {
        // Copy vertices
        result.vertices.insert(result.vertices.end(), mesh.vertices.begin(), mesh.vertices.end());

        // Copy indices with offset
        for (uint32_t index : mesh.indices)
        {
            result.indices.push_back(index + vertexOffset);
        }

        vertexOffset += mesh.vertices.size();
    }

    result.name = "compound";
    return result;
}

void VoxelMeshGenerator::transformMesh(VoxelMesh::MeshData &mesh, const Math::float3 &offset, const Math::float3 &scale)
{
    for (auto &vertex : mesh.vertices)
    {
        // Apply scale
        vertex.position.x *= scale.x;
        vertex.position.y *= scale.y;
        vertex.position.z *= scale.z;

        // Apply offset
        vertex.position = Math::add(vertex.position, offset);
    }
}

void VoxelMeshGenerator::calculateNormals(VoxelMesh::MeshData &mesh)
{
    // Calculate face normals and accumulate vertex normals
    for (size_t i = 0; i < mesh.indices.size(); i += 3)
    {
        uint32_t i0 = mesh.indices[i];
        uint32_t i1 = mesh.indices[i + 1];
        uint32_t i2 = mesh.indices[i + 2];

        Math::float3 v0 = mesh.vertices[i0].position;
        Math::float3 v1 = mesh.vertices[i1].position;
        Math::float3 v2 = mesh.vertices[i2].position;

        Math::float3 edge1 = Math::sub(v1, v0);
        Math::float3 edge2 = Math::sub(v2, v0);
        Math::float3 normal = Math::normalize(Math::cross(edge1, edge2));

        mesh.vertices[i0].normal = Math::add(mesh.vertices[i0].normal, normal);
        mesh.vertices[i1].normal = Math::add(mesh.vertices[i1].normal, normal);
        mesh.vertices[i2].normal = Math::add(mesh.vertices[i2].normal, normal);
    }

    // Normalize accumulated normals
    for (auto &vertex : mesh.vertices)
    {
        vertex.normal = Math::normalize(vertex.normal);
    }
}

void VoxelMeshGenerator::optimizeMesh(VoxelMesh::MeshData &mesh)
{
    // Simple optimization: remove unused vertices
    // More sophisticated optimization could be added here
    if (mesh.vertices.empty() || mesh.indices.empty())
    {
        return;
    }

    // For now, just ensure normals are properly calculated
    calculateNormals(mesh);
}
