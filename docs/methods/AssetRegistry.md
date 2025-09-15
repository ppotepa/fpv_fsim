# AssetRegistry.h / AssetRegistry.cpp

## Constructors

- `AssetRegistry()`

  **Summary:** Default constructor for the asset registry.

## Destructors

- `~AssetRegistry()`

  **Summary:** Destructor for the asset registry.

## Asset Registration Methods

- `void registerFont(AssetId id, std::unique_ptr<FontAsset> asset)`

  **Summary:** Registers a font asset with the given ID.

- `void registerTexture(AssetId id, std::unique_ptr<TextureAsset> asset)`

  **Summary:** Registers a texture asset with the given ID.

- `void registerMaterial(AssetId id, std::unique_ptr<MaterialAsset> asset)`

  **Summary:** Registers a material asset with the given ID.

- `void registerMeshRecipe(AssetId id, std::unique_ptr<MeshRecipeAsset> asset)`

  **Summary:** Registers a mesh recipe asset with the given ID.

## Asset Retrieval Methods

- `const FontAsset *getFont(AssetId id) const`

  **Summary:** Retrieves a font asset by ID, returns nullptr if not found.

- `const TextureAsset *getTexture(AssetId id) const`

  **Summary:** Retrieves a texture asset by ID, returns nullptr if not found.

- `const MaterialAsset *getMaterial(AssetId id) const`

  **Summary:** Retrieves a material asset by ID, returns nullptr if not found.

- `const MeshRecipeAsset *getMeshRecipe(AssetId id) const`

  **Summary:** Retrieves a mesh recipe asset by ID, returns nullptr if not found.

## Package Management Methods

- `bool hasPackage(const std::string &packageName) const`

  **Summary:** Checks if a package with the given name has been loaded.

- `void markPackageLoaded(const std::string &packageName)`

  **Summary:** Marks a package as loaded, adding it to the loaded packages list.

- `const std::vector<std::string> &getLoadedPackages() const`

  **Summary:** Returns a reference to the list of loaded package names.

## Scene Configuration Methods

- `void registerSceneConfig(AssetId id, const std::string &sceneXml)`

  **Summary:** Registers a scene configuration with the given ID and XML content.

- `const std::string *getSceneConfig(AssetId id) const`

  **Summary:** Retrieves a scene configuration by ID, returns nullptr if not found.

- `void setDefaultScene(AssetId id)`

  **Summary:** Sets the default scene configuration ID.

- `const std::string *getDefaultScene() const`

  **Summary:** Retrieves the default scene configuration XML, returns nullptr if not set.

- `AssetId getDefaultSceneId() const`

  **Summary:** Returns the ID of the default scene configuration.

## Utility Methods

- `void clear()`

  **Summary:** Clears all registered assets, scene configurations, and loaded packages (used for hot reloading).
