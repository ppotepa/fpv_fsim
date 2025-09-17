# Internal Assets

This directory contains core engine assets that are required for the FPV Flight Simulator to function properly. These assets provide fallbacks when user assets are not available or when errors occur.

## Structure

- `core/`: Core engine assets
  - `textures/`: Default textures used throughout the engine
  - `fonts/`: Default fonts for UI and debug overlays
  - `audio/`: Default audio files for feedback and effects
  - `materials/`: Default material definitions for rendering
  - `meshes/`: Basic primitive meshes (cube, sphere, plane)
  - `shaders/`: Core shaders for rendering
  - `internal_assets.xml`: Configuration file that defines all internal assets

- Root-level error assets: Used as ultimate fallbacks when even the internal assets can't be loaded
  - `error.png`: Error texture displayed when texture loading fails
  - `error.ttf`: Error font used when font loading fails
  - `error.wav`: Error sound played when audio loading fails

## Asset Loading

Internal assets are automatically loaded by the `AssetManager` during engine initialization. They are not meant to be directly referenced by users or modified.

To override an internal asset with your own version:

1. Create a new asset in your package
2. Use the same asset ID as the internal asset
3. The asset system will automatically use your version instead of the internal one

## Modifying Internal Assets

**Warning:** Internal assets should not be modified unless you are developing the engine itself. Changes to internal assets may cause unexpected behavior or crashes.

## Adding New Internal Assets

If you're extending the engine and need to add new internal assets:

1. Add the asset file to the appropriate subdirectory
2. Register the asset in `core/internal_assets.xml`
3. Update the `AssetManager` if necessary to handle the new asset type
