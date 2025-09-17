# FPV Flight Simulator: Complete Architecture & Flow Reference
**Version:** 1.4  
**Date:** September 17, 2025  
**Project:** fpv_fsim  
**Branch:** feature/package-modularity  
**Status:** Current and Complete
**Review Status:** Architecture validated, implementation verified

## 1. Application Overview

The FPV Flight Simulator is a modular 3D simulation engine designed with a package-based architecture inspired by the Quake 3 engine. The application uses a dual asset system, discovers packages from external directories, and compiles only the necessary assets on run, with the core package being the foundation for all functionality.

This document provides a comprehensive reference for the application's architecture, package processing, asset management, and scene rendering, focusing on both design requirements and implementation details.

## 2. Core Architecture Flow

### 2.1 Package-Based Architecture
```
[Application Start]
    ↓
[Initialize Dual Asset System]
    ↓
[Load Internal Assets] → [Load User Assets]
    ↓
[Initialize Package System]
    |
    ↓
[Package Discovery]  
    |             → [Discover Available Packages in assets/packages/]
    ↓              
[Package Loading]
    |             → [Load Core Package] → [Required, always loaded first]
    |             → [Load External Packages]
    ↓
[Register Behaviors]
    |             → [Register SpinBehavior, DebugOverlayBehavior]
    ↓
[Create OpenGL Window]
    ↓
[Initialize Scene Renderer]
    |             → [Load scene.green_cubes]
    ↓
[Enter Main Loop]
    |             → [Process Windows Messages]
    |             → [Calculate Delta Time]
    |             → [Update Behavior System]
    |             → [Update Scene Renderer]
    |             → [Render Scene]
    ↓
[Cleanup Resources]
```

### 2.2 Asset System Flow
```
[Asset Request]
    ↓
[Check User Assets First] → [Found?] → YES → [Return User Asset]
    ↓ NO
[Check Internal Assets] → [Found?] → YES → [Return Internal Asset]
    ↓ NO
[Return Fallback Asset]
```

### 2.3 Rendering Flow
```
[Scene Compilation]
    ↓
[Asset Parsing] → [Material Resolution] → [Transform Processing]
    ↓
[Create Render Objects]
    ↓
[Animation Update] → [Matrix Calculations] → [OpenGL Rendering]
    ↓
[Display Frame] → [Swap Buffers]
```

## 3. Dual Asset System

### 3.1 Purpose and Architecture

The dual asset system separates internal engine assets from user-customizable content with a clear priority system:

1. **User Assets (`assets/`)**
   - User-customizable content packages
   - Override internal assets with same ID
   - Hot-reloadable
   - Package-based organization
   - Located in `assets/` directory

2. **Internal Assets (`internal_assets/`)**
   - Core engine assets (textures, materials, meshes, scenes)
   - Fallback assets for error conditions
   - Not user-modifiable
   - Always available
   - Located in `internal_assets/` directory

3. **Fallback Assets**
   - Used when requested asset not found in either location
   - Basic placeholder assets (error textures, default meshes)

**Asset Priority:** User Assets > Internal Assets > Fallback Assets

### 3.3 Asset Management Features
- **Dual System:** Internal + User assets with proper priority
- **XML Configuration:** Declarative asset definitions
- **Fallback System:** Error handling with default assets
- **Hot Reload:** Runtime asset reloading capability

### 3.2 Asset Resolution System

```
[Asset Request]
    ↓
[Check User Assets First] → [Found?] → YES → [Return User Asset]
    ↓ NO
[Check Internal Assets] → [Found?] → YES → [Return Internal Asset]
    ↓ NO
[Return Fallback Asset]
```

## 4. Package System Architecture

### 4.1 Key Components

- **PackageBootstrap**: Main entry point for initializing the package system
- **PackageManager**: Manages loading, unloading, and dependency resolution of packages
- **PackageParser**: Parses package XML configurations and extracts data
- **AssetRegistry**: Centralized registry of all available assets
- **BehaviorRegistry**: Factory for creating behavior components
- **BehaviorSystem**: Updates behaviors attached to entities
- **IoContainer**: Dependency injection container for loose coupling

### 4.3 Package Loading Flow

```
[PackageBootstrap::initialize]
    ↓
[Setup Core Services]
    ↓
[Initialize Core Systems]
    |             → [Resolve PackageManager, AssetRegistry, BehaviorSystem]
    ↓
[Register Asset Loaders]
    ↓
[Load Initial Packages]
    |             → [PackageManager::discoverPackages]
    |             → [Get load order based on dependencies]
    |             → [Load each package in correct order]
    ↓
[Register Package Behaviors]
    ↓
[Setup Package Containers]
```

### 4.4 Package XML Processing

```
[PackageManager::loadPackage]
    ↓
[PackageParser::loadPackage]
    |             → [Parse XML file]
    |             → [Extract package metadata, assets, scenes]
    ↓
[Validate Package]
    |             → [Check for required package ID]
    |             → [Validate dependencies]
    ↓
[Register Assets]
    ↓
[Return Package]
```

## 5. Scene Compilation and Loading

### 5.1 Scene Compilation Process

The scene compilation process transforms XML scene definitions into optimized runtime data:

```
[Parse Scene XML]
    |             → [Extract entities and properties]
    ↓
[Resolve Asset References]
    |             → [Link mesh/material assets to IDs]
    ↓
[Validate Components]
    |             → [Ensure required components are present]
    ↓
[Compile Behavior Parameters]
    |             → [Serialize behavior params to binary]
    ↓
[Pack Component Data]
    |             → [Efficiently pack component data]
    ↓
[Generate Scene Binary]
    |             → [Create optimized scene representation]
```

**Output: Compiled Scene Data**
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
        uint32_t componentDataOffset;    // Offset into component data blob
        std::string behaviorClass;       // Code-behind behavior class
        BehaviorParams behaviorParams;   // Serialized parameters
    };
    
    CompiledEntity entities[];
    uint8_t componentDataBlob[];        // Packed component data
};
```

### 5.2 Scene Loading Flow

```
[SceneConfigParser::loadXmlScene]
    |             → [Construct scene file path from sceneId]
    |             → [Check if file exists]
    |             → [Load and parse XML file using PugiXmlParser]
    ↓
[Parse Scene Structure]
    |             → [Extract scene attributes (id, name, type)]
    |             → [Parse materials, textures, meshes]
    |             → [Parse entities with components]
    ↓
[Resolve Asset Paths]
    |             → [Make relative paths absolute]
    ↓
[Return Parsed Scene]
```

### 5.3 Asset-to-Render Pipeline

```
[XML Scene Definition]
    ↓
[AssetManager Resolution] → [Material Lookup] → [Mesh Lookup]
    ↓
[Scene Compilation] → [RenderObject Creation]
    ↓
[Animation Processing] → [Matrix Calculations]
    ↓
[OpenGL Rendering] → [Frame Display]
```

## 6. Entity-Component System & Behavior Attachment

### 6.1 Entity-Component Architecture

The application uses a flexible object composition system:

- **Entity**: Basic game object with ID and name
- **Transform**: Position, rotation, scale
- **Components**: Modular functionality units
- **Behaviors**: Reusable logic components 
- **World**: Container for entities
- **EventBus**: Communication between systems

### 6.2 Runtime Behavior Attachment

```
[Create Entity]
    ↓
[BehaviorRegistry::createBehavior]
    |             → [Create instance of specified behavior class]
    ↓
[Behavior::initialize]
    |             → [Set up behavior with entity reference]
    |             → [Parse XML parameters]
    ↓
[BehaviorSystem::update]
    |             → [Call update() on all behaviors each frame]
```

### 6.3 Code-Behind Behavior Flow

**Runtime Behavior Attachment:**
1. XML entity specifies `codeBehind="behaviors.ClassName"`
2. BehaviorRegistry creates instance of specified class
3. Behavior initializes with entity reference and XML parameters
4. Entity receives attached behavior for lifecycle management
5. BehaviorSystem calls update() on all behaviors each frame

This enhanced flow enables declarative scene authoring with high-performance C++ behaviors while maintaining hot-reload capabilities for rapid development iteration.

## 7. Main Simulation Loop

The main simulation loop handles all per-frame processing with both fixed and variable timestep components:

```
[Process Windows Messages]
    |             → [Handle WM_QUIT, WM_CLOSE, Dispatch]
    ↓
[Calculate Delta Time]
    ↓
[Update Behavior System]
    |             → [BehaviorSystem::update(deltaTime)]
    ↓
[Fixed-Timestep Physics Update (60Hz)]
    |             → [PhysicsSystem::update]
    |                → [Gravity, Drag, Collisions, Integration]
    |             → [VehicleControlSystem::update]
    |                → [CPU, Mixer, Battery limits]
    |             → [SensorSystem::update]
    |                → [Sample, Noise, Write SensorsC]
    |             → [BehaviorSystem::update]
    |                → [Update all code-behind behaviors]
    ↓
[Variable-Timestep Updates]
    |             → [InputSystem::update]
    |                → [Poll, Process, Publish Events]
    |             → [WorldGenSystem::update]
    |                → [Procedural, LOD, Scene Management]
    |             → [ConsoleSystem::update]
    ↓
[Update Scene Renderer]
    |             → [SceneRenderer::update(deltaTime)]
    ↓
[Render Scene]
    |             → [SceneRenderer::render()]
    ↓
[Cap Frame Rate]
    |             → [~60 FPS target]
```

### 7.1 Event System Flow

Events are used for communication between decoupled systems:

```
[Event Trigger] → [EventBus] → [Registered Listeners] → [Action Execution]
```

## 8. Hot-Reload Capability

The package system supports hot-reloading, allowing packages to be updated at runtime without application restart:

```
[File Watcher Detects Changes]
    ↓
[Unload Modified Package]
    |             → [PackageManager::unloadPackage]
    ↓
[Parse Updated Package]
    |             → [PackageParser::loadPackage]
    ↓
[Load New Package Version]
    |             → [PackageManager::loadPackage]
    ↓
[Update Asset Registry]
    |             → [AssetRegistry::updateAssets]
    ↓
[Reattach Behaviors]
    |             → [BehaviorSystem::rebindBehaviors]
```

## 9. Rendering System

### 9.1 Components
- **SceneRenderer:** Manages scene objects and rendering
- **RenderObject:** Compiled render data (positions, colors, animations)
- **Material System:** Color and texture management
- **Transform System:** 3D matrix calculations

### 9.2 Rendering Flow
```
[Scene Compilation]
    ↓
[Asset Parsing] → [Material Resolution] → [Transform Processing]
    ↓
[Create Render Objects]
    ↓
[Animation Update] → [Matrix Calculations] → [OpenGL Rendering]
    ↓
[Display Frame] → [Swap Buffers]
```

### 9.3 Current Implementation Features
- **Multiple Objects:** Support for multiple 3D objects in a scene
- **Materials:** Color and texture support (green and red materials implemented)
- **Animations:** Real-time rotation and transformation
- **Camera System:** 3D perspective projection
- **Current Scene Demo:**
  - **3 Green Cubes:** Positioned horizontally, rotating at different speeds
  - **1 Red Cube:** Positioned above center, rotating in opposite direction
  - **Real-time Animation:** Smooth rotation with 60 FPS target
  - **3D Perspective:** Proper camera projection and depth

## 10. File Structure & Organization

### 10.1 Directory Structure
```
fpv_fsim/
├── src/                        # Source code
│   ├── core/                   # Core engine systems
│   ├── assets/                 # Asset management
│   ├── components/             # ECS components
│   ├── systems/                # ECS systems
│   ├── behaviors/              # Behavior implementations
│   ├── rendering/              # Rendering subsystem
│   ├── factory/                # Object factories
│   └── platform/               # Platform-specific code
├── internal_assets/            # Engine internal assets
│   └── core/                   # Core asset definitions
│       ├── textures/           # Default textures
│       ├── materials/          # Material definitions
│       ├── meshes/             # 3D geometry
│       ├── scenes/             # Scene definitions
│       └── shaders/            # Shader programs
├── assets/                     # User-modifiable assets
│   └── packages/               # Content packages
│       └── core/               # Core game package
├── tests/                      # Unit tests
├── docs/                       # Documentation
└── build-scripts/              # Build automation
```

### 10.2 Configuration Files
- **CMakeLists.txt:** Build system configuration
- **internal_assets.xml:** Internal asset registry
- **package.xml:** Package definitions
- **scene XML files:** 3D scene definitions
- **material XML files:** Material properties

## 11. Implementation Status & Technical Specifications

### 11.1 Implemented Features ✅
- Dual asset system with internal/user separation
- Scene rendering with multiple colored cubes
- Rotation animations with configurable speeds
- Package system with XML configuration
- Entity-component architecture
- OpenGL rendering pipeline
- Build and test automation
- Asset compilation pipeline

### 11.2 Architecture Compliance
- **Separation of Concerns:** Clear boundaries between systems
- **SOLID Principles:** Single responsibility, dependency inversion
- **Asset Isolation:** Renderer only uses compiled data, no direct asset references
- **Modular Design:** Pluggable behaviors and packages

### 11.3 Build System & Platform Support
- **CMake:** Cross-platform build configuration
- **MinGW-w64:** Windows compilation toolchain
- **C++17:** Modern C++ standards
- **OpenGL:** 3D graphics rendering
- **Windows:** Primary development platform
- **PowerShell:** Build and automation scripts
- **Dependencies:**
  - OpenGL for graphics rendering
  - PugiXML for XML parsing
  - Windows API for window management and input

### 11.4 Quality Assurance
- **Testing Strategy:**
  - Unit Tests: Core system functionality
  - Integration Tests: Cross-system communication
  - Visual Tests: Rendering output validation
  - Build Tests: Compilation and deployment verification
- **Code Quality:**
  - Clean Architecture: Layered system design
  - Error Handling: Graceful failure modes
  - Documentation: Comprehensive code comments
  - Logging: Debug and status information

## 12. Future Roadmap

### 12.1 Planned Features
- **Scene Loading from XML:** Runtime scene compilation
- **Advanced Materials:** Texture mapping and lighting
- **Physics Integration:** Collision detection and response
- **Input System:** User interaction and controls
- **Audio System:** 3D spatial audio
- **Networking:** Multiplayer support

### 12.2 Architecture Improvements
- **Asset Hot Reload:** Runtime asset updates
- **Scripting System:** Lua/Python integration
- **Plugin Architecture:** External module loading
- **Performance Profiling:** Optimization tools
- **Memory Management:** Advanced allocation strategies

---

**Document Status:** Current and Complete  
**Last Updated:** September 17, 2025  
**Review Status:** Architecture validated, implementation verified
