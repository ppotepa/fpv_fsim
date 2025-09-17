# WorldGenSystem.h / WorldGenSystem.cpp

## Constructors

- `WorldGenSystem(EventBus &eventBus, World &world, AssetRegistry &assetRegistry)`

  **Summary:** Constructor taking event bus, world, and asset registry references.

## Destructors

- `virtual ~WorldGenSystem() = default;`

  **Summary:** Virtual destructor.

## Public Methods

- `void update(World &world, float deltaTime) override`

  **Summary:** Updates the world generation system (event-driven, no continuous updates).

- `void GenerateDefaultSphereWorld()`

  **Summary:** Generates a default Earth-like sphere world with atmosphere and clouds.

- `void GenerateWorldFromJSONScene(const std::string &sceneJson)`

  **Summary:** Generates the world based on JSON scene configuration.

## Private Methods

- `void OnNoPackagesFound(const NoPackagesFoundEvent &event)`

  **Summary:** Event handler that triggers default world generation.

- `void OnDefaultWorldRequested(const DefaultWorldGeneratedEvent &event)`

  **Summary:** Event handler that generates world from JSON or falls back to default.

- `AssetId GenerateProceduralSphereMesh(float radius, int segments)`

  **Summary:** Generates a procedural sphere mesh asset ID (placeholder implementation).

- `AssetId GetEarthMaterialId()`

  **Summary:** Returns the Earth material asset ID (placeholder).

- `AssetId GetAtmosphereMaterialId(int layer)`

  **Summary:** Returns atmosphere material asset ID for the given layer (placeholder).

- `AssetId GetCloudMaterialId()`

  **Summary:** Returns the cloud material asset ID (placeholder).
