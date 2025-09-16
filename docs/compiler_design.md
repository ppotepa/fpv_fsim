# Package Asset Compiler Design

## Overview

The **Package Asset Compiler** transforms human-authored package XML files into optimized runtime representations, processing assets, scenes, and behaviors for efficient loading and execution. This compilation system enables hot-reload during development while ensuring optimal runtime performance.

## Compilation Pipeline

### 1. Package Discovery and Parsing

```
packages/
├── core/
│   └── package.xml          # Core engine assets
├── environment/
│   └── package.xml          # Environment assets  
├── vehicles/
│   └── package.xml          # Vehicle definitions
└── ui/
    └── package.xml          # UI components
```

**Discovery Process:**
- Scan package directories for `package.xml` files
- Build dependency graph based on package dependencies
- Determine compilation order (topological sort)
- Validate package schemas and references

### 2. Asset Compilation

#### Input: XML Asset Definitions
```xml
<assets>
    <material id="RedMaterial">
        <shader>core.StandardLit</shader>
        <properties>
            <albedo>1.0 0.0 0.0 1.0</albedo>
            <metallic>0.1</metallic>
            <roughness>0.8</roughness>
        </properties>
    </material>
    
    <mesh id="CubeMesh">
        <source>assets/models/cube.obj</source>
        <optimize>true</optimize>
        <generateTangents>true</generateTangents>
    </mesh>
</assets>
```

#### Output: Compiled Asset Metadata
```cpp
struct CompiledAsset {
    uint32_t assetId;           // Runtime asset ID
    AssetType type;             // Material, Mesh, Texture, etc.
    std::string runtimePath;    // Path to compiled binary
    uint32_t dataSize;          // Size of asset data
    uint32_t dependencies[];    // Dependent asset IDs
    AssetMetadata metadata;     // Type-specific metadata
};
```

#### Compilation Steps:
1. **Parse XML Definition** - Extract asset properties and source paths
2. **Resolve Dependencies** - Link to required assets (textures, shaders)
3. **Process Source Data** - Convert source files (OBJ, PNG, etc.) to runtime format
4. **Optimize Data** - Compress textures, optimize meshes, bake lighting
5. **Generate Binary** - Serialize to efficient binary format
6. **Build Metadata** - Create runtime lookup tables

### 3. Scene Compilation

#### Input: XML Scene Definitions
```xml
<scenes>
    <scene id="DeveloperScene" name="Developer Test Scene">
        <entity id="rotateCube" name="Rotating Red Cube" codeBehind="behaviors.RotatingCube">
            <transform>
                <position x="0" y="0" z="-5" />
                <rotation x="0" y="0" z="0" w="1" />
                <scale x="1" y="1" z="1" />
            </transform>
            <components>
                <mesh asset="CubeMesh" />
                <material asset="RedMaterial" />
                <renderable visible="true" castShadows="true" />
            </components>
            <params>
                <rotation_speed>1.5</rotation_speed>
                <rotation_axis>0 1 0</rotation_axis>
            </params>
        </entity>
    </scene>
</scenes>
```

#### Output: Compiled Scene Data
```cpp
struct CompiledScene {
    uint32_t sceneId;
    std::string sceneName;
    uint32_t entityCount;
    
    struct CompiledEntity {
        uint32_t entityId;
        std::string entityName;
        Transform initialTransform;
        ComponentMask componentMask;     // Bitmask of component types
        uint32_t componentDataOffset;   // Offset into component data blob
        std::string behaviorClass;      // Code-behind behavior class
        BehaviorParams behaviorParams;  // Serialized parameters
    };
    
    CompiledEntity entities[];
    uint8_t componentDataBlob[];        // Packed component data
};
```

#### Scene Compilation Process:
1. **Parse Scene XML** - Extract entities and their properties
2. **Resolve Asset References** - Link mesh/material assets to IDs
3. **Validate Components** - Ensure required components are present
4. **Compile Behavior Parameters** - Serialize behavior params to binary
5. **Pack Component Data** - Efficiently pack component data
6. **Generate Scene Binary** - Create optimized scene representation

### 4. Behavior Integration

#### Code-Behind Compilation:
```cpp
// Behavior Registry (auto-generated during compilation)
namespace BehaviorRegistry {
    std::unordered_map<std::string, BehaviorFactory> factories = {
        {"behaviors.RotatingCube", []() { return std::make_unique<RotatingCube>(); }},
        {"vehicles.QuadcopterController", []() { return std::make_unique<QuadcopterController>(); }},
        {"environment.CloudSystem", []() { return std::make_unique<CloudSystem>(); }}
    };
}
```

**Behavior Compilation Steps:**
1. **Scan C++ Source** - Find REGISTER_BEHAVIOR() macros
2. **Extract Behavior Names** - Build registry of available behaviors
3. **Validate References** - Ensure XML references match registered behaviors
4. **Generate Factory Code** - Auto-generate behavior factory functions
5. **Compile Parameter Schema** - Extract parameter types for validation

## Asset Processing Pipeline

### Texture Processing
```
PNG/JPG/TGA → Format Conversion → Compression → Mipmap Generation → Binary Output
    ↓              ↓                ↓              ↓                ↓
Source Image → RGBA8/RGB8/etc → DXT/ASTC/etc → Multiple LODs → .texture file
```

### Mesh Processing
```
OBJ/FBX/GLTF → Import → Optimization → Tangent Gen → Binary Output
     ↓          ↓         ↓            ↓            ↓
Source Mesh → Vertices → Index Buffer → Normal Maps → .mesh file
```

### Material Processing
```
XML Material → Shader Linkage → Property Validation → Binary Output
     ↓             ↓               ↓                   ↓
Material Def → Shader Programs → Uniform Layout → .material file
```

## Compilation Optimizations

### 1. Dependency-Based Compilation
```cpp
class AssetCompiler {
    void compilePackage(const Package& package) {
        // Build dependency graph
        DependencyGraph graph = buildDependencyGraph(package);
        
        // Compile in dependency order
        for (auto& asset : graph.getTopologicalOrder()) {
            if (needsRecompilation(asset)) {
                compileAsset(asset);
            }
        }
    }
    
    bool needsRecompilation(const Asset& asset) {
        auto compiledTime = getCompiledTimestamp(asset);
        auto sourceTime = getSourceTimestamp(asset);
        
        // Recompile if source is newer than compiled output
        return sourceTime > compiledTime;
    }
};
```

### 2. Parallel Compilation
```cpp
class ParallelAssetCompiler {
    void compilePackageParallel(const Package& package) {
        ThreadPool threadPool(std::thread::hardware_concurrency());
        
        for (auto& batch : getDependencyBatches(package)) {
            // Submit entire batch to thread pool
            for (auto& asset : batch) {
                threadPool.submit([this, asset]() {
                    compileAsset(asset);
                });
            }
            
            // Wait for batch completion before next batch
            threadPool.waitForBatch();
        }
    }
};
```

### 3. Incremental Compilation
- Track file modification times
- Maintain compilation cache
- Only recompile changed assets and dependents
- Support partial package recompilation

## Hot-Reload System

### Development Mode
```cpp
class AssetHotReloadSystem {
    void initialize() {
        // Watch package directories for changes
        fileWatcher.watchDirectory("packages/", [this](const std::string& path) {
            onPackageFileChanged(path);
        });
    }
    
    void onPackageFileChanged(const std::string& packagePath) {
        // Recompile affected package
        auto package = loadPackage(packagePath);
        compilePackage(package);
        
        // Notify runtime systems of changes
        EventBus::instance().emit(AssetReloadedEvent{package.id});
    }
};
```

### Runtime Integration
```cpp
class AssetManager {
    void onAssetReloaded(const AssetReloadedEvent& event) {
        // Reload affected assets
        reloadPackageAssets(event.packageId);
        
        // Update entities using these assets
        for (auto& entity : world.getEntitiesUsingAssets(event.packageId)) {
            refreshEntityAssets(entity);
        }
    }
};
```

## Binary Format Specifications

### Package Binary Header
```cpp
struct PackageHeader {
    uint32_t magic;              // 'FPKG' magic number
    uint16_t version;            // Package format version
    uint16_t flags;              // Compression, endianness, etc.
    uint32_t assetCount;         // Number of assets
    uint32_t sceneCount;         // Number of scenes
    uint32_t dependencyCount;    // Number of dependencies
    uint64_t timestamp;          // Compilation timestamp
    uint32_t assetTableOffset;   // Offset to asset table
    uint32_t sceneTableOffset;   // Offset to scene table
    uint32_t stringTableOffset;  // Offset to string table
    uint32_t dataOffset;         // Offset to binary data
};
```

### Asset Table Entry
```cpp
struct AssetEntry {
    uint32_t assetId;            // Runtime asset ID
    uint32_t nameOffset;         // Offset into string table
    uint16_t assetType;          // AssetType enum value
    uint16_t flags;              // Asset-specific flags
    uint32_t dataOffset;         // Offset into data section
    uint32_t dataSize;           // Size of asset data
    uint32_t dependencyOffset;   // Offset to dependency list
    uint16_t dependencyCount;    // Number of dependencies
    uint16_t reserved;           // Alignment padding
};
```

## Error Handling and Validation

### Compilation Errors
```cpp
enum class CompilationError {
    MISSING_SOURCE_FILE,
    INVALID_ASSET_REFERENCE,
    CIRCULAR_DEPENDENCY,
    BEHAVIOR_NOT_FOUND,
    INVALID_PARAMETER_TYPE,
    SHADER_COMPILATION_FAILED,
    MESH_OPTIMIZATION_FAILED
};

class CompilationResult {
public:
    bool success() const { return errors.empty(); }
    const std::vector<CompilationError>& getErrors() const { return errors; }
    const std::vector<std::string>& getWarnings() const { return warnings; }
    
private:
    std::vector<CompilationError> errors;
    std::vector<std::string> warnings;
};
```

### Runtime Validation
```cpp
class PackageValidator {
public:
    ValidationResult validate(const Package& package) {
        ValidationResult result;
        
        // Validate asset references
        for (auto& scene : package.scenes) {
            for (auto& entity : scene.entities) {
                validateAssetReferences(entity, result);
                validateBehaviorReference(entity, result);
                validateComponentCompatibility(entity, result);
            }
        }
        
        return result;
    }
};
```

## Performance Metrics

### Compilation Performance
- **Asset Compilation Time**: ~50-100ms per asset (depending on complexity)
- **Parallel Efficiency**: ~80-90% with 8+ cores
- **Incremental Overhead**: <5ms for unchanged assets
- **Hot-Reload Latency**: <200ms from file change to runtime update

### Memory Usage
- **Compilation Peak**: ~2-4x final package size during compilation
- **Runtime Overhead**: <1% of total asset memory
- **Dependency Cache**: ~10-20MB for large projects

This compilation system provides the foundation for the enhanced package modularity architecture, enabling efficient development workflows while maintaining optimal runtime performance.