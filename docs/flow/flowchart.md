flowchart TD

%% =============================
%% 1. DEVELOPMENT & BUILD-TIME TOOLCHAIN
%% =============================

subgraph DEV["1. Development & Build-Time Toolchain"]
  RAW["Developer Input / Raw Assets\n(.obj, .fbx, .glb, .png, .xml, .cpp, configs)"]
  TOOLCHAIN["Build Toolchain (C++, CMake, GCC/aarch64-g++)"]

  RAW --> TOOLCHAIN

  subgraph COMPILER["Asset Compiler Service"]
    CFG1["Load Configuration\n(XML configs)"]
    VAL["Schema Validation (XSD)"]
    RES["Resolve Paths & Dependencies"]
    EXT["Parameter Extraction"]
    OPT["Asset Cooking\n(Meshoptimizer, KTX2, Procedural Gen)"]
    OUT1["Generate Binary Asset Packs\n(*.pak)"]
    OUT2["Generate Plugins\n(lib_*.so)"]
    MAN["Create Manifest"]

    CFG1 --> VAL --> RES --> EXT --> OPT --> OUT1 --> OUT2 --> MAN
  end

  subgraph CODEGEN["Asset ID Generator"]
    SCAN["Scan package.xml, scene.xml"]
    SYM["Process Names & Types"]
    REF["Resolve References"]
    IDS["Generate Numeric IDs\n(FNV-1a / sequential)"]
    OUT3["ASSET_IDS.h / .ids.bin / JSON map"]

    SCAN --> SYM --> REF --> IDS --> OUT3
  end

  TOOLCHAIN --> COMPILER
  TOOLCHAIN --> CODEGEN
end

%% =============================
%% 2. RUNTIME INITIALIZATION
%% =============================

subgraph INIT["2. Runtime Initialization"]
  MAIN["main() entry point"]
  ENG["Engine::initialize()\n(EventBus, World, SimClock, AssetRegistry)"]
  SYS["Add Core Systems\n(Physics, Input, VehicleControl, WorldGen, Console, Render, HotReload)"]
  BOOT["BootstrapSystem::Init()\n- Compile assets (debug)\n- Load packages\n- Register assets"]
  LOAD["WorldGenSystem::LoadScene('DeveloperScene')\n(SceneParser, EntityFactory, Fallback Sphere)"]

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
