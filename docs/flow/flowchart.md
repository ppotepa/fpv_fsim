# Enhanced Package Modularity Flowchart

```mermaid
flowchart TD

%% =============================
%% 1. ENHANCED DEVELOPMENT & BUILD-TIME TOOLCHAIN
%% =============================

subgraph DEV["1. Enhanced Development & Build-Time Toolchain"]
  RAW["Developer Input / Enhanced Assets\n(.gltf, .json packages, .cpp behaviors, scene definitions)"]
  TOOLCHAIN["Build Toolchain (C++, CMake, GCC/aarch64-g++)"]

  RAW --> TOOLCHAIN

  subgraph COMPILER["Enhanced Asset Compiler Service"]
    CFG1["Load Package Configuration\n(package.json with assets + scenes)"]
    VAL["Schema Validation (JSON Schema for packages)"]
    RES["Resolve Asset Dependencies & References"]
    EXT["Extract Assets & Scene Definitions"]
    OPT["Asset Cooking\n(Meshoptimizer, KTX2, Behavior Compilation)"]
    OUT1["Generate Binary Asset Packs\n(*.pak with asset refs)"]
    OUT2["Generate Behavior Libraries\n(lib_behaviors.so)"]
    MAN["Create Enhanced Manifest\n(asset-scene mappings)"]

    CFG1 --> VAL --> RES --> EXT --> OPT --> OUT1 --> OUT2 --> MAN
  end

  subgraph CODEGEN["Enhanced Asset ID Generator"]
    SCAN["Scan package.json, scenes/*.json"]
    SYM["Process Asset Names, Scene IDs & Entity Definitions"]
    REF["Resolve Asset References & Code-Behind Links"]
    IDS["Generate Numeric IDs\n(FNV-1a for assets + scenes)"]
    OUT3["ASSET_IDS.h / SCENE_IDS.h / .ids.bin / JSON map"]

    SCAN --> SYM --> REF --> IDS --> OUT3
  end

  subgraph BEHAVGEN["Code-Behind Behavior Compiler"]
    BHSCAN["Scan codeBehind Attributes"]
    BHREG["Register Behavior Classes"]
    BHLINK["Link JSON Params to C++ Behaviors"]
    BHOUT["Generate Behavior Registry\n(BEHAVIOR_REGISTRY.h)"]

    BHSCAN --> BHREG --> BHLINK --> BHOUT
  end

  TOOLCHAIN --> COMPILER
  TOOLCHAIN --> CODEGEN
  TOOLCHAIN --> BEHAVGEN
end

%% =============================
%% 2. ENHANCED RUNTIME INITIALIZATION
%% =============================

subgraph INIT["2. Enhanced Runtime Initialization"]
  MAIN["main() entry point"]
  ENG["Engine::initialize()\n(EventBus, World, SimClock, AssetRegistry, BehaviorRegistry)"]
  SYS["Add Enhanced Systems\n(Physics, Input, VehicleControl, WorldGen, BehaviorSystem, Console, Render, HotReload)"]
  BOOT["BootstrapSystem::Init()\n- Load packages (assets + scenes)\n- Register behaviors\n- Validate dependencies"]
  LOAD["WorldGenSystem::LoadScene('DeveloperScene')\n(Enhanced SceneParser, EntityFactory with CodeBehind, Asset References)"]

  MAIN --> ENG --> SYS --> BOOT --> LOAD
end

%% =============================
%% 3. ENHANCED MAIN SIMULATION LOOP
%% =============================

subgraph LOOP["3. Enhanced Main Simulation Loop (Engine::run)"]
  START["Show Window / Headless Mode"]

  OSMSG["Handle OS Messages\n(WM_QUIT, Dispatch)"]
  DELTA["Calc deltaTime"]
  CLOCK["SimClock::tick(deltaTime)"]

  subgraph PHYS["Fixed-Timestep Physics Update (60Hz)"]
    PHYSYS["PhysicsSystem::update\n(Gravity, Drag, Collisions, Integration)"]
    VEH["VehicleControlSystem::update\n(CPU, Mixer, Battery limits)"]
    SENS["SensorSystem::update\n(Sample, Noise, Write SensorsC)"]
    BEHAV["BehaviorSystem::update\n(Update all code-behind behaviors)"]

    PHYSYS --> VEH --> SENS --> BEHAV
  end

  subgraph VARSYS["Variable-Timestep Updates"]
    INPUT["InputSystem::update\n(Poll, Process, Publish Events)"]
    WGEN["WorldGenSystem::update\n(Procedural, LOD, Scene Management)"]
    CON["ConsoleSystem::update"]
    REND["VisualizationSystem::update\n(Asset-driven rendering, OpenGL/ES, HUD, Swap Buffers)"]

    INPUT --> WGEN --> CON --> REND
  end

  HOT["AssetHotReloadSystem::update\n(Detect package changes, Recompile assets, Reload scenes, Update behaviors)"]
  FPS["Update FPS counter / stats"]

  START --> OSMSG --> DELTA --> CLOCK --> PHYS --> VARSYS --> HOT --> FPS
end

%% =============================
%% 4. CODE-BEHIND BEHAVIOR FLOW
%% =============================

subgraph BEHAVIOR["4. Code-Behind Behavior Integration"]
  JSONENT["JSON Entity with codeBehind='behaviors.ClassName'"]
  BEHLOOKUP["BehaviorRegistry::create('behaviors.ClassName')"]
  BEHINIT["Behavior::initialize(entity, jsonParams)"]
  BEHATTACH["Entity::attachBehavior(behavior)"]
  BEHUPDATE["BehaviorSystem::update() calls Behavior::update()"]

  JSONENT --> BEHLOOKUP --> BEHINIT --> BEHATTACH --> BEHUPDATE
end

%% =============================
%% Final Enhanced Flow
%% =============================

DEV --> INIT --> LOOP
LOOP --> BEHAVIOR
BEHAVIOR --> LOOP

```

## Enhanced Architecture Flow Description

### Phase 1: Enhanced Development & Build-Time Toolchain

**Enhanced Asset Compiler Service:**
- Processes hierarchical package.json files containing both assets and scenes
- Validates schema for the new package structure
- Resolves asset references within scene definitions
- Compiles behaviors and links them to entities
- Generates optimized binary packs with asset-scene mappings

**Code-Behind Behavior Compiler:**
- Scans JSON for `codeBehind` attributes
- Registers C++ behavior classes in runtime registry
- Links JSON parameters to C++ behavior constructors
- Generates behavior factory for runtime instantiation

### Phase 2: Enhanced Runtime Initialization

**Enhanced Systems:**
- **BehaviorSystem**: Manages all code-behind behaviors attached to entities
- **Enhanced WorldGenSystem**: Loads scenes from package definitions with asset references
- **Enhanced EntityFactory**: Creates entities with behaviors from JSON definitions

**Package Loading:**
- Loads hierarchical package structure (assets + scenes)
- Validates asset dependencies
- Registers behaviors in runtime registry
- Creates asset-scene mappings for efficient lookup

### Phase 3: Enhanced Main Simulation Loop

**Code-Behind Integration:**
- BehaviorSystem updates all attached behaviors during fixed timestep
- Behaviors receive entity reference and deltaTime for updates
- Asset-driven rendering uses references instead of hardcoded resources
- Hot-reload system monitors package changes and updates behaviors

### Phase 4: Code-Behind Behavior Flow

**Runtime Behavior Attachment:**
1. JSON entity specifies `codeBehind="behaviors.ClassName"`
2. BehaviorRegistry creates instance of specified class
3. Behavior initializes with entity reference and JSON parameters
4. Entity receives attached behavior for lifecycle management
5. BehaviorSystem calls update() on all behaviors each frame

This enhanced flow enables declarative scene authoring with high-performance C++ behaviors while maintaining hot-reload capabilities for rapid development iteration.

  MAIN --> ENG --> SYS --> BOOT --> LOAD
end

%% =============================
%% 3. MAIN SIMULATION LOOP
%% =============================

subgraph LOOP["3. Main Simulation Loop (Engine::run)"]
  START["Show Window / Headless Mode"]

  OSMSG["Handle OS Messages\n(WM_QUIT, Dispatch)"]
  DELTA["Calc deltaTime"]
  CLOCK["SimClock::tick(deltaTime)"]

  subgraph PHYS["Fixed-Timestep Physics Update (60Hz)"]
    PHYSYS["PhysicsSystem::update\n(Gravity, Drag, Collisions, Integration)"]
    VEH["VehicleControlSystem::update\n(CPU, Mixer, Battery limits)"]
    SENS["SensorSystem::update\n(Sample, Noise, Write SensorsC)"]

    PHYSYS --> VEH --> SENS
  end

  subgraph VARSYS["Variable-Timestep Updates"]
    INPUT["InputSystem::update\n(Poll, Process, Publish Events)"]
    WGEN["WorldGenSystem::update\n(Procedural, LOD, Voxel Clouds)"]
    CON["ConsoleSystem::update"]
    REND["VisualizationSystem::update\n(OpenGL/ES, HUD, Swap Buffers)"]

    INPUT --> WGEN --> CON --> REND
  end

  HOT["AssetHotReloadSystem::update\n(Detect changes, Recompile, Swap Registry, dlopen)"]
  FPS["Update FPS counter / stats"]

  START --> OSMSG --> DELTA --> CLOCK --> PHYS --> VARSYS --> HOT --> FPS
end

%% =============================
%% Final Flow
%% =============================

DEV --> INIT --> LOOP
