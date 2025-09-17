# Dual Asset System Implementation

## Overview

This implementation adds a dual asset system to the drone simulation engine, separating internal engine assets from user-customizable content.

## Directory Structure

```
drone_sim_ggl/
├── internal_assets/       # Internal engine assets (not user-modifiable)
│   └── core/
│       ├── textures/      # Basic textures used by the engine
│       ├── fonts/         # Default fonts
│       ├── audio/         # Default audio
│       ├── materials/     # Default materials
│       ├── meshes/        # Basic geometric meshes
│       └── shaders/       # Core rendering shaders
├── assets/                # User assets (customizable content)
│   └── packages/          # User-created content packages
└── src/
    └── core/
        ├── AssetManager.h      # Dual asset system manager
        ├── AssetManager.cpp    # (Empty - implementation in header)
        └── AssetManager_Integration.cpp # Integration with existing AssetRegistry
```

## AssetManager Class

The `AssetManager` class manages both internal and user assets with the following key features:

- Separate paths for internal and user assets
- Asset type categorization (textures, fonts, audio, materials, meshes, shaders, scenes)
- Integration with the existing AssetRegistry system

## Implementation Details

### Asset Loading Priority

1. User assets are checked first and take precedence
2. If not found, internal assets are used
3. If neither is found, fallback to error assets

### Usage

Initialize the AssetManager with paths to internal and user assets:

```cpp
AssetManager assetManager;
assetManager.initialize("internal_assets", "assets");
```

## Future Improvements

1. Implement asset hot-reloading
2. Add asset version control
3. Enhance integration with the engine's entity system
4. Add support for custom asset types

## Implementation Notes

The current implementation is simplified for integration purposes. The AssetManager provides a minimal interface to work with the existing AssetRegistry system.
