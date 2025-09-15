# Asset-Scene-Compiler Implementation

This implementation follows the comprehensive asset-scene-compiler guideline from `docs/4.0-asset-scene-compiler.md`. It provides a robust, two-mode asset pipeline supporting both rapid development iteration and optimized production builds.

## 🏗️ Architecture Overview

The system implements the **"Two Modes, One Codepath"** principle:

- **Debug Mode**: Hot-swapping with live XML parsing and procedural generation
- **Release Mode**: Optimized binary packs with pre-compiled assets

### Key Design Principles

1. **Strings Only at the Edges**: XML and file paths exist only at compilation time; runtime uses stable numeric `AssetId`s
2. **Deterministic Commits**: Hot-swapped changes are batched and committed at frame boundaries
3. **Thin Runtime, Fat Tools**: Complex processing happens at build time, runtime focuses on efficient loading
4. **IoC & ECS Integration**: Clear separation of concerns using Dependency Injection and Entity Component System

## 📁 Directory Structure

```
drone_sim_ggl/
├── assets/                          # Source assets and configuration
│   ├── packages/                    # Asset packages
│   │   └── DeveloperPackage/        # Default development package
│   │       ├── package.xml          # Asset definitions
│   │       ├── textures/           # Source texture files
│   │       └── materials.xml       # Material definitions
│   └── schemas/                     # XSD schemas for validation
│       ├── asset.xsd               # Package schema
│       └── scene.xsd               # Scene schema
├── build_tools/                     # Asset pipeline tools
│   ├── asset_compiler/             # CLI tool for asset compilation
│   │   ├── main.cpp                # Entry point
│   │   ├── AssetCompiler.h/.cpp    # Core compiler logic
│   │   └── CMakeLists.txt          # Build configuration
│   ├── codegen/                    # CLI tool for asset ID generation
│   │   ├── main.cpp                # Entry point
│   │   ├── AssetIdGenerator.h/.cpp # ID generation logic
│   │   └── CMakeLists.txt          # Build configuration
│   ├── build_scripts/              # Automation scripts
│   │   ├── build_assets.ps1        # Windows build script
│   │   └── build_assets.sh         # Linux/macOS build script
│   └── CMakeLists.txt              # Main build configuration
├── runtime/                        # Runtime data directory
│   └── data/                       # Compiled assets and caches
│       ├── packs/                  # Binary asset packs (.pak files)
│       ├── plugins/                # Shared object libraries (.so)
│       └── cache/                  # Runtime caches
│           └── thumb_index/        # Content-hash based index
└── src/                            # Engine source code
    ├── core/                       # Core engine systems
    │   ├── AssetRegistry.h/.cpp    # Central asset storage
    │   ├── AssetPackLoader.h/.cpp  # Package loading system
    │   ├── AssetIds.h              # Generated numeric asset IDs
    │   ├── EventBus.h/.cpp         # Event system
    │   └── World.h/.cpp            # ECS world manager
    ├── platform/                   # Platform abstraction
    │   ├── IXmlParser.h            # XML parser interface
    │   └── PugiXmlParser.h/.cpp    # pugixml implementation
    ├── systems/                    # ECS systems
    │   ├── AssetHotReloadSystem.h/.cpp # Hot-reloading in debug mode
    │   ├── BootstrapSystem.h/.cpp  # Initial setup and package loading
    │   ├── WorldGenSystem.h/.cpp   # World generation from scene configs
    │   └── VisualizationSystem.h/.cpp # 3D rendering
    ├── generators/                 # Procedural asset generators
    │   ├── VoxelMeshGenerator.h/.cpp # Procedural mesh generation
    │   ├── ProceduralTextureGenerator.h/.cpp # Texture generation
    │   └── BasicShaderGenerator.h/.cpp # GLSL shader generation
    └── config/                     # Configuration parsing
        └── SceneConfigParser.h/.cpp # XML scene configuration parser
```

## 🔧 Build Tools

### Asset Compiler (`build_tools/asset_compiler/`)

The Asset Compiler processes XML package definitions and generates optimized runtime assets.

**Features:**
- XML schema validation against XSD files
- Procedural asset generation (textures, meshes, shaders)
- Binary pack generation for release builds
- Comprehensive error reporting and diagnostics

**Usage:**
```bash
# Debug mode (hot-reloading)
./asset_compiler -d -o runtime/data/packs assets/packages/DeveloperPackage/package.xml

# Release mode (optimized binary packs)
./asset_compiler -O -o runtime/data/packs assets/packages/DeveloperPackage/package.xml
```

### Codegen Tool (`build_tools/codegen/`)

The Codegen tool scans asset definitions and generates stable numeric IDs.

**Features:**
- Scans XML files for asset references
- Generates C++ header with constants
- Produces binary lookup tables
- Creates JSON mappings for debugging

**Usage:**
```bash
# Generate C++ header
./codegen -f header -o src/core/AssetIds.h -n Assets assets/packages/

# Generate binary lookup table
./codegen -f binary -o runtime/data/asset_ids.bin assets/packages/

# Generate JSON debug mapping
./codegen -f json -o debug_assets.json assets/packages/
```

## 🎯 Asset ID System

The system enforces **"strings only at the edges"** by using stable numeric IDs at runtime:

```cpp
// Generated AssetIds.h
namespace Assets {
    using AssetId = uint32_t;
    
    static constexpr AssetId EARTH_ALBEDO = 100;
    static constexpr AssetId DRONE_FRAME = 1004;
    static constexpr AssetId PBR_STANDARD = 3000;
}

// Runtime usage
auto texture = assetRegistry.getTexture(Assets::EARTH_ALBEDO);
auto mesh = assetRegistry.getMesh(Assets::DRONE_FRAME);
```

## 🔄 Two-Mode Pipeline

### Debug Mode (Development)
```
XML Assets → Live Parsing → Procedural Generation → In-Memory Assets → Hot-Reload
```

1. **File Watching**: `AssetHotReloadSystem` monitors XML files for changes
2. **Live Compilation**: Assets are generated on-demand from XML definitions
3. **Hot Swapping**: Changes are applied at frame boundaries for deterministic behavior
4. **Instant Feedback**: Developers see changes immediately without restarting

### Release Mode (Production)
```
XML Assets → Schema Validation → Asset Compilation → Binary Packs → Fast Loading
```

1. **Build-Time Processing**: All assets are compiled and optimized offline
2. **Binary Packs**: Assets are bundled into memory-mappable `.pak` files
3. **Numeric IDs**: All asset references use pre-generated stable numeric IDs
4. **Optimized Loading**: Memory-mapped I/O provides fast, deterministic loading

## 🚀 Getting Started

### 1. Build the Tools
```bash
# Windows
.\build_tools\build_scripts\build_assets.ps1

# Linux/macOS
./build_tools/build_scripts/build_assets.sh
```

### 2. Run the Demo
```bash
# Try debug mode
.\demo_pipeline.ps1 -Debug

# Try release mode
.\demo_pipeline.ps1 -Release

# Full demonstration
.\demo_pipeline.ps1 -Demo
```

### 3. Integrate with Main Application
```cpp
#include "core/AssetIds.h"
#include "core/AssetRegistry.h"

// Use numeric asset IDs
auto earthTexture = registry.getTexture(Assets::EARTH_ALBEDO);
auto droneModel = registry.getMesh(Assets::DRONE_FRAME);
```

## 🎨 Asset Types Supported

### Textures
- **File-based**: PNG, KTX2, DDS with compression and mipmaps
- **Procedural**: Perlin noise, FBM noise, gradients, patterns

### Meshes
- **File-based**: OBJ, FBX, GLTF with optimization and LOD generation
- **Procedural**: Cubes, spheres, cylinders, compound shapes

### Materials
- **PBR**: Physically Based Rendering with albedo, normal, roughness, metallic maps
- **Phong**: Classic ambient/diffuse/specular lighting model
- **Unlit**: Simple color or textured materials

### Shaders
- **Procedural**: Generated GLSL shaders for common lighting models
- **File-based**: Custom GLSL vertex, fragment, and geometry shaders

### Scenes
- **XML-defined**: Complete scene descriptions with entities, cameras, lighting
- **Procedural elements**: Automatic terrain, city generation, atmospheric effects

## 🔍 Key Classes

### Core Asset Management
- **`AssetRegistry`**: Central storage for all loaded assets
- **`AssetPackLoader`**: Loads assets from XML or binary packs
- **`IXmlParser`**: Platform-independent XML parsing interface

### ECS Systems
- **`AssetHotReloadSystem`**: Monitors files and triggers hot-reloading
- **`BootstrapSystem`**: Initial setup and package discovery
- **`WorldGenSystem`**: Creates world from scene configurations
- **`VisualizationSystem`**: Renders the final scene

### Generators
- **`VoxelMeshGenerator`**: Creates procedural meshes from parameters
- **`ProceduralTextureGenerator`**: Generates textures using noise functions
- **`BasicShaderGenerator`**: Creates GLSL shaders from templates

## 📊 Performance Benefits

### Debug Mode
- ⚡ Instant iteration: No build step for asset changes
- 🔧 Developer-friendly: Clear error messages and validation
- 📝 Flexible: Easy to experiment with new assets and parameters

### Release Mode
- 🚀 Fast loading: Memory-mapped binary packs
- 📦 Optimized assets: Compressed textures, LOD meshes, minimized memory footprint
- 🎯 Deterministic: Stable numeric IDs ensure consistent behavior

## 🧪 Testing

The system includes comprehensive validation:

1. **Schema Validation**: XSD schemas ensure XML correctness
2. **Asset Compilation**: Verifies all references are valid
3. **ID Generation**: Ensures no collisions in numeric IDs
4. **Integration Tests**: End-to-end pipeline validation

## 🚧 Future Enhancements

- Asset dependency tracking and incremental compilation
- GPU texture compression pipeline integration
- Automatic LOD generation for meshes
- Asset streaming for large worlds
- Cross-platform shader compilation (SPIR-V)
- Hot-reloading for scenes and entity configurations

---

This implementation provides a production-ready asset pipeline that scales from rapid prototyping to shipped products, following modern game engine architecture principles.
