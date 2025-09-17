# AssetPackLoader.h / AssetPackLoader.cpp

## Constructors

- `AssetPackLoader(AssetRegistry &registry)`

  **Summary:** Constructor that takes a reference to the asset registry for storing loaded assets.

## Destructors

- `~AssetPackLoader()`

  **Summary:** Destructor for the asset pack loader.

## Public Methods

- `bool loadPackage(const std::string &packagePath)`

  **Summary:** Loads an asset package from the specified JSON file path, parsing assets and configurations.

- `bool loadDeveloperPackage()`

  **Summary:** Convenience method to load the developer package from the default path.

## Private Methods

- `bool parseAssets(const std::string &jsonContent, const std::string &packageName)`

  **Summary:** Parses the assets section from JSON content and registers assets with the registry.

- `bool parseConfigurations(const std::string &jsonContent, const std::string &packageName)`

  **Summary:** Parses the configurations section from JSON content, including scene configurations.

- `std::unique_ptr<FontAsset> parseFontAsset(const std::string &jsonNode)`

  **Summary:** Parses a font asset from a JSON node, extracting path, size, and antialiasing properties.

- `std::unique_ptr<TextureAsset> parseTextureAsset(const std::string &jsonNode)`

  **Summary:** Parses a texture asset from a JSON node, extracting path, format, mipmaps, and filter properties.

- `std::unique_ptr<MaterialAsset> parseMaterialAsset(const std::string &jsonNode)`

  **Summary:** Parses a material asset from a JSON node, extracting shader ID and parameters.

- `std::unique_ptr<MeshRecipeAsset> parseMeshRecipeAsset(const std::string &jsonNode)`

  **Summary:** Parses a mesh recipe asset from a JSON node, extracting generator and parameters.
