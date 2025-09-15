# BootstrapSystem.h / BootstrapSystem.cpp

## Constructors

- `BootstrapSystem(EventBus &eventBus, World &world, AssetRegistry &assetRegistry, AssetPackLoader &assetLoader)`

  **Summary:** Constructor taking references to event bus, world, asset registry, and loader.

## Destructors

- `virtual ~BootstrapSystem() = default;`

  **Summary:** Virtual destructor.

## Public Methods

- `void update(World &world, float deltaTime) override`

  **Summary:** Updates the bootstrap system (no continuous updates needed).

- `void Init()`

  **Summary:** Initializes the bootstrap system, loading packages and triggering world generation events.

- `void PostFrameUpdate()`

  **Summary:** Called after frame updates (placeholder for future hot-reloading).

## Private Methods

- `bool CheckForAssetPackages()`

  **Summary:** Checks if asset packages exist in the filesystem.

- `bool LoadAvailablePackages()`

  **Summary:** Loads available asset packages, prioritizing DeveloperPackage.
