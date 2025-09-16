#include "ProceduralMeshGenerators.h"
#include <map>
#include <cmath>
#include <random>
#include <algorithm>

// IcoSphereGenerator Implementation
ProceduralMesh IcoSphereGenerator::generate(float radius, int subdivisions, bool flatShading)
{
    ProceduralMesh mesh;
    std::vector<Vector3D> tempVertices;

    // Create initial icosahedron vertices
    float t = (1.0f + std::sqrt(5.0f)) / 2.0f; // Golden ratio

    addVertex(tempVertices, Vector3D(-1, t, 0));
    addVertex(tempVertices, Vector3D(1, t, 0));
    addVertex(tempVertices, Vector3D(-1, -t, 0));
    addVertex(tempVertices, Vector3D(1, -t, 0));

    addVertex(tempVertices, Vector3D(0, -1, t));
    addVertex(tempVertices, Vector3D(0, 1, t));
    addVertex(tempVertices, Vector3D(0, -1, -t));
    addVertex(tempVertices, Vector3D(0, 1, -t));

    addVertex(tempVertices, Vector3D(t, 0, -1));
    addVertex(tempVertices, Vector3D(t, 0, 1));
    addVertex(tempVertices, Vector3D(-t, 0, -1));
    addVertex(tempVertices, Vector3D(-t, 0, 1));

    // Create initial faces
    std::vector<std::array<int, 3>> faces = {
        {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11}, {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8}, {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9}, {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}};

    // Subdivide faces
    std::map<long, int> middlePointIndexCache;
    for (int i = 0 i < subdivisions; i++)
    {
        std::vector<std::array<int, 3>> newFaces;

        for (const auto &face : faces)
        {
            int a = getMiddlePoint(face[0], face[1], tempVertices, middlePointIndexCache, radius);
            int b = getMiddlePoint(face[1], face[2], tempVertices, middlePointIndexCache, radius);
            int c = getMiddlePoint(face[2], face[0], tempVertices, middlePointIndexCache, radius);

            newFaces.push_back({face[0], a, c});
            newFaces.push_back({face[1], b, a});
            newFaces.push_back({face[2], c, b});
            newFaces.push_back({a, b, c});
        }

        faces = newFaces;
    }

    // Convert to final mesh format
    if (flatShading)
    {
        // Duplicate vertices for flat shading
        for (const auto &face : faces)
        {
            Vector3D v1 = tempVertices[face[0]] * radius;
            Vector3D v2 = tempVertices[face[1]] * radius;
            Vector3D v3 = tempVertices[face[2]] * radius;

            Vector3D normal = (v2 - v1).cross(v3 - v1).normalized();

            float u1, v1_uv, u2, v2_uv, u3, v3_uv;
            calculateUV(v1, u1, v1_uv);
            calculateUV(v2, u2, v2_uv);
            calculateUV(v3, u3, v3_uv);

            int baseIndex = mesh.vertices.size();
            mesh.vertices.emplace_back(v1, normal, u1, v1_uv);
            mesh.vertices.emplace_back(v2, normal, u2, v2_uv);
            mesh.vertices.emplace_back(v3, normal, u3, v3_uv);

            mesh.indices.push_back(baseIndex);
            mesh.indices.push_back(baseIndex + 1);
            mesh.indices.push_back(baseIndex + 2);
        }
    }
    else
    {
        // Shared vertices for smooth shading
        for (const auto &vertex : tempVertices)
        {
            Vector3D pos = vertex * radius;
            Vector3D normal = vertex; // For sphere, normal = normalized position
            float u, v;
            calculateUV(pos, u, v);
            mesh.vertices.emplace_back(pos, normal, u, v);
        }

        for (const auto &face : faces)
        {
            mesh.indices.push_back(face[0]);
            mesh.indices.push_back(face[1]);
            mesh.indices.push_back(face[2]);
        }
    }

    return mesh;
}

void IcoSphereGenerator::addVertex(std::vector<Vector3D> &vertices, const Vector3D &v)
{
    vertices.push_back(v.normalized());
}

int IcoSphereGenerator::getMiddlePoint(int p1, int p2, std::vector<Vector3D> &vertices,
                                       std::map<long, int> &cache, float radius)
{
    bool firstIsSmaller = p1 < p2;
    long smallerIndex = firstIsSmaller ? p1 : p2;
    long greaterIndex = firstIsSmaller ? p2 : p1;
    long key = (smallerIndex << 32) + greaterIndex;

    auto found = cache.find(key);
    if (found != cache.end())
    {
        return found->second;
    }

    Vector3D point1 = vertices[p1];
    Vector3D point2 = vertices[p2];
    Vector3D middle = Vector3D(
                          (point1.x + point2.x) / 2.0f,
                          (point1.y + point2.y) / 2.0f,
                          (point1.z + point2.z) / 2.0f)
                          .normalized();

    vertices.push_back(middle);
    int index = vertices.size() - 1;
    cache[key] = index;

    return index;
}

void IcoSphereGenerator::calculateUV(const Vector3D &vertex, float &u, float &v)
{
    u = std::atan2(vertex.x, vertex.z) / (2.0f * M_PI) + 0.5f;
    v = std::asin(vertex.y) / M_PI + 0.5f;
}

// CubeGenerator Implementation
ProceduralMesh CubeGenerator::generate(float size, bool flatShading)
{
    ProceduralMesh mesh;
    float half = size * 0.5f;

    // Define cube vertices
    std::vector<Vector3D> positions = {
        // Front face
        Vector3D(-half, -half, half), Vector3D(half, -half, half),
        Vector3D(half, half, half), Vector3D(-half, half, half),
        // Back face
        Vector3D(-half, -half, -half), Vector3D(-half, half, -half),
        Vector3D(half, half, -half), Vector3D(half, -half, -half),
        // Top face
        Vector3D(-half, half, -half), Vector3D(-half, half, half),
        Vector3D(half, half, half), Vector3D(half, half, -half),
        // Bottom face
        Vector3D(-half, -half, -half), Vector3D(half, -half, -half),
        Vector3D(half, -half, half), Vector3D(-half, -half, half),
        // Right face
        Vector3D(half, -half, -half), Vector3D(half, half, -half),
        Vector3D(half, half, half), Vector3D(half, -half, half),
        // Left face
        Vector3D(-half, -half, -half), Vector3D(-half, -half, half),
        Vector3D(-half, half, half), Vector3D(-half, half, -half)};

    std::vector<Vector3D> normals = {
        Vector3D(0, 0, 1), Vector3D(0, 0, -1), Vector3D(0, 1, 0),
        Vector3D(0, -1, 0), Vector3D(1, 0, 0), Vector3D(-1, 0, 0)};

    // Add faces
    for (int face = 0 face < 6; face++)
    {
        int baseIndex = face * 4;

        if (flatShading)
        {
            // Each face gets its own vertices
            int meshBaseIndex = mesh.vertices.size();

            for (int i = 0 i < 4; i++)
            {
                float u = (i == 1 || i == 2) ? 1.0f : 0.0f;
                float v = (i == 2 || i == 3) ? 1.0f : 0.0f;
                mesh.vertices.emplace_back(positions[baseIndex + i], normals[face], u, v);
            }

            // Two triangles per face
            mesh.indices.push_back(meshBaseIndex);
            mesh.indices.push_back(meshBaseIndex + 1);
            mesh.indices.push_back(meshBaseIndex + 2);

            mesh.indices.push_back(meshBaseIndex);
            mesh.indices.push_back(meshBaseIndex + 2);
            mesh.indices.push_back(meshBaseIndex + 3);
        }
    }

    return mesh;
}

// ProceduralAircraftGenerator Implementation
ProceduralMesh ProceduralAircraftGenerator::generate(float length, int fuselageSegments,
                                                     float wingSpan, float tailSpan, bool flatShading)
{
    ProceduralMesh mesh;

    addFuselage(mesh, length, fuselageSegments);
    addWings(mesh, wingSpan, length * 0.6f);
    addTail(mesh, tailSpan, length * 0.3f);

    return mesh;
}

void ProceduralAircraftGenerator::addFuselage(ProceduralMesh &mesh, float length, int segments)
{
    float halfLength = length * 0.5f;
    float radius = length * 0.05f; // Thin fuselage

    // Simple tapered cylinder
    for (int i = 0 i <= segments; i++)
    {
        float t = static_cast<float>(i) / segments;
        float z = -halfLength + t * length;
        float currentRadius = radius * (1.0f - std::abs(2.0f * t - 1.0f) * 0.7f); // Taper at ends

        // Add circular cross-section
        int sides = 8;
        for (int j = 0 j < sides; j++)
        {
            float angle = 2.0f * M_PI * j / sides;
            float x = currentRadius * std::cos(angle);
            float y = currentRadius * std::sin(angle);

            Vector3D pos(x, y, z);
            Vector3D normal = Vector3D(x, y, 0).normalized();

            mesh.vertices.emplace_back(pos, normal, static_cast<float>(j) / sides, t);
        }
    }

    // Add triangles between segments
    for (int i = 0 i < segments; i++)
    {
        for (int j = 0 j < 8; j++)
        {
            int current = i * 8 + j;
            int next = i * 8 + ((j + 1) % 8);
            int currentNext = (i + 1) * 8 + j;
            int nextNext = (i + 1) * 8 + ((j + 1) % 8);

            // Two triangles per quad
            mesh.indices.push_back(current);
            mesh.indices.push_back(currentNext);
            mesh.indices.push_back(next);

            mesh.indices.push_back(next);
            mesh.indices.push_back(currentNext);
            mesh.indices.push_back(nextNext);
        }
    }
}

void ProceduralAircraftGenerator::addWings(ProceduralMesh &mesh, float span, float length)
{
    float halfSpan = span * 0.5f;
    float halfLength = length * 0.5f;
    float thickness = length * 0.02f;

    int baseIndex = mesh.vertices.size();

    // Wing vertices (simple rectangular wings)
    std::vector<Vector3D> wingVerts = {
        // Top surface
        Vector3D(-halfSpan, thickness, -halfLength), Vector3D(halfSpan, thickness, -halfLength),
        Vector3D(halfSpan, thickness, halfLength), Vector3D(-halfSpan, thickness, halfLength),
        // Bottom surface
        Vector3D(-halfSpan, -thickness, -halfLength), Vector3D(-halfSpan, -thickness, halfLength),
        Vector3D(halfSpan, -thickness, halfLength), Vector3D(halfSpan, -thickness, -halfLength)};

    Vector3D upNormal(0, 1, 0);
    Vector3D downNormal(0, -1, 0);

    // Add vertices
    for (int i = 0 i < 4; i++)
    {
        mesh.vertices.emplace_back(wingVerts[i], upNormal, i % 2, i / 2);
    }
    for (int i = 4 i < 8; i++)
    {
        mesh.vertices.emplace_back(wingVerts[i], downNormal, i % 2, (i - 4) / 2);
    }

    // Add triangles
    std::vector<int> indices = {
        // Top face
        0, 1, 2, 0, 2, 3,
        // Bottom face
        4, 6, 5, 4, 7, 6};

    for (int idx : indices)
    {
        mesh.indices.push_back(baseIndex + idx);
    }
}

void ProceduralAircraftGenerator::addTail(ProceduralMesh &mesh, float span, float length)
{
    // Similar to wings but smaller and positioned at rear
    float halfSpan = span * 0.5f;
    float halfLength = length * 0.5f;
    float thickness = length * 0.01f;
    float zOffset = length * 1.5f; // Position at rear

    int baseIndex = mesh.vertices.size();

    std::vector<Vector3D> tailVerts = {
        Vector3D(-halfSpan, thickness, zOffset - halfLength),
        Vector3D(halfSpan, thickness, zOffset - halfLength),
        Vector3D(halfSpan, thickness, zOffset + halfLength),
        Vector3D(-halfSpan, thickness, zOffset + halfLength),
        Vector3D(-halfSpan, -thickness, zOffset - halfLength),
        Vector3D(-halfSpan, -thickness, zOffset + halfLength),
        Vector3D(halfSpan, -thickness, zOffset + halfLength),
        Vector3D(halfSpan, -thickness, zOffset - halfLength)};

    Vector3D upNormal(0, 1, 0);
    Vector3D downNormal(0, -1, 0);

    for (int i = 0 i < 4; i++)
    {
        mesh.vertices.emplace_back(tailVerts[i], upNormal, i % 2, i / 2);
    }
    for (int i = 4 i < 8; i++)
    {
        mesh.vertices.emplace_back(tailVerts[i], downNormal, i % 2, (i - 4) / 2);
    }

    std::vector<int> indices = {
        0, 1, 2, 0, 2, 3,
        4, 6, 5, 4, 7, 6};

    for (int idx : indices)
    {
        mesh.indices.push_back(baseIndex + idx);
    }
}

// SphericalPatchDisplaceGenerator Implementation
ProceduralMesh SphericalPatchDisplaceGenerator::generate(float baseRadius, int subdivisions,
                                                         int patchCount, float minHeight,
                                                         float maxHeight, int seed)
{
    // Start with base icosphere
    ProceduralMesh baseMesh = IcoSphereGenerator::generate(baseRadius, subdivisions, true);

    // Setup random number generator
    std::mt19937 rng;
    if (seed == -1)
    {
        std::random_device rd;
        rng.seed(rd());
    }
    else
    {
        rng.seed(seed);
    }

    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    std::uniform_real_distribution<float> heightDist(minHeight, maxHeight);

    // Generate random patch centers
    std::vector<Vector3D> patchCenters;
    std::vector<float> patchRadii;
    std::vector<float> patchHeights;

    for (int i = 0 i < patchCount; i++)
    {
        Vector3D center(dist(rng), dist(rng), dist(rng));
        center = center.normalized();
        patchCenters.push_back(center);
        patchRadii.push_back(0.2f + dist(rng) * 0.1f); // Radius between 0.1-0.3
        patchHeights.push_back(heightDist(rng));
    }

    // Displace vertices based on patches
    for (auto &vertex : baseMesh.vertices)
    {
        Vector3D originalPos = vertex.position.normalized() * baseRadius;
        float totalDisplacement = 0.0f;

        for (size_t i = 0 i < patchCenters.size() i++)
        {
            if (isInPatch(originalPos, patchCenters[i], patchRadii[i]))
            {
                float displacement = calculateDisplacement(originalPos, patchCenters[i],
                                                           patchRadii[i], 0.0f, patchHeights[i]);
                totalDisplacement += displacement;
            }
        }

        Vector3D direction = vertex.position.normalized();
        vertex.position = direction * (baseRadius + totalDisplacement);
        vertex.normal = direction; // Keep normal pointing outward
    }

    return baseMesh;
}

bool SphericalPatchDisplaceGenerator::isInPatch(const Vector3D &vertex, const Vector3D &patchCenter,
                                                float patchRadius)
{
    return vertex.normalized().dot(patchCenter) > std::cos(patchRadius);
}

float SphericalPatchDisplaceGenerator::calculateDisplacement(const Vector3D &vertex,
                                                             const Vector3D &patchCenter,
                                                             float patchRadius,
                                                             float minHeight, float maxHeight)
{
    float distance = std::acos(vertex.normalized().dot(patchCenter));
    float normalizedDistance = distance / patchRadius;

    if (normalizedDistance >= 1.0f)
        return 0.0f;

    // Smooth falloff using cosine
    float falloff = (std::cos(normalizedDistance * M_PI) + 1.0f) * 0.5f;
    return minHeight + (maxHeight - minHeight) * falloff;
}


