#include "AssetRegistry.h"
#include <iostream>

/**
 * @brief Construct an empty asset registry.
 *
 * Initializes all asset maps and configuration storage.
 */
AssetRegistry::AssetRegistry() {}

/**
 * @brief Destroy the asset registry and free all assets.
 *
 * All stored assets are automatically cleaned up through their unique pointers.
 */
AssetRegistry::~AssetRegistry() {}

/**
 * @brief Register a font asset with the given ID.
 *
 * Stores the font asset in the registry, taking ownership of the pointer.
 * If an asset with the same ID already exists, it will be replaced.
 *
 * @param id Unique identifier for the font asset
 * @param asset Unique pointer to the font asset
 */
void AssetRegistry::registerFont(AssetId id, std::unique_ptr<FontAsset> asset)
{
    fonts_[id] = std::move(asset);
}

/**
 * @brief Register a texture asset with the given ID.
 *
 * Stores the texture asset in the registry, taking ownership of the pointer.
 * If an asset with the same ID already exists, it will be replaced.
 *
 * @param id Unique identifier for the texture asset
 * @param asset Unique pointer to the texture asset
 */
void AssetRegistry::registerTexture(AssetId id, std::unique_ptr<TextureAsset> asset)
{
    textures_[id] = std::move(asset);
}

/**
 * @brief Register a material asset with the given ID.
 *
 * Stores the material asset in the registry, taking ownership of the pointer.
 * If an asset with the same ID already exists, it will be replaced.
 *
 * @param id Unique identifier for the material asset
 * @param asset Unique pointer to the material asset
 */
void AssetRegistry::registerMaterial(AssetId id, std::unique_ptr<MaterialAsset> asset)
{
    materials_[id] = std::move(asset);
}

/**
 * @brief Register a mesh recipe asset with the given ID.
 *
 * Stores the mesh recipe asset in the registry, taking ownership of the pointer.
 * If an asset with the same ID already exists, it will be replaced.
 *
 * @param id Unique identifier for the mesh recipe asset
 * @param asset Unique pointer to the mesh recipe asset
 */
void AssetRegistry::registerMeshRecipe(AssetId id, std::unique_ptr<MeshRecipeAsset> asset)
{
    meshRecipes_[id] = std::move(asset);
}

/**
 * @brief Get a font asset by ID.
 *
 * Searches for a font asset with the given ID and returns a pointer to it.
 *
 * @param id The asset identifier
 * @return Pointer to the font asset, or nullptr if not found
 */
const FontAsset *AssetRegistry::getFont(AssetId id) const
{
    auto it = fonts_.find(id);
    return it != fonts_.end() ? it->second.get() : nullptr;
}

/**
 * @brief Get a texture asset by ID.
 *
 * Searches for a texture asset with the given ID and returns a pointer to it.
 *
 * @param id The asset identifier
 * @return Pointer to the texture asset, or nullptr if not found
 */
const TextureAsset *AssetRegistry::getTexture(AssetId id) const
{
    auto it = textures_.find(id);
    return it != textures_.end() ? it->second.get() : nullptr;
}

/**
 * @brief Get a material asset by ID.
 *
 * Searches for a material asset with the given ID and returns a pointer to it.
 *
 * @param id The asset identifier
 * @return Pointer to the material asset, or nullptr if not found
 */
const MaterialAsset *AssetRegistry::getMaterial(AssetId id) const
{
    auto it = materials_.find(id);
    return it != materials_.end() ? it->second.get() : nullptr;
}

/**
 * @brief Get a mesh recipe asset by ID.
 *
 * Searches for a mesh recipe asset with the given ID and returns a pointer to it.
 *
 * @param id The asset identifier
 * @return Pointer to the mesh recipe asset, or nullptr if not found
 */
const MeshRecipeAsset *AssetRegistry::getMeshRecipe(AssetId id) const
{
    auto it = meshRecipes_.find(id);
    return it != meshRecipes_.end() ? it->second.get() : nullptr;
}

/**
 * @brief Check if a package has been loaded.
 *
 * Searches the list of loaded packages for the given package name.
 *
 * @param packageName Name of the package to check
 * @return true if the package is loaded, false otherwise
 */
bool AssetRegistry::hasPackage(const std::string &packageName) const
{
    return std::find(loadedPackages_.begin(), loadedPackages_.end(), packageName) != loadedPackages_.end();
}

/**
 * @brief Mark a package as loaded.
 *
 * Adds the package name to the list of loaded packages if it's not already there.
 * This prevents duplicate loading of the same package.
 *
 * @param packageName Name of the package to mark as loaded
 */
void AssetRegistry::markPackageLoaded(const std::string &packageName)
{
    if (!hasPackage(packageName))
    {
        loadedPackages_.push_back(packageName);
    }
}

/**
 * @brief Get the list of all loaded packages.
 *
 * Returns a reference to the internal vector of loaded package names.
 *
 * @return Const reference to the vector of loaded package names
 */
const std::vector<std::string> &AssetRegistry::getLoadedPackages() const
{
    return loadedPackages_;
}

/**
 * @brief Clear all assets and configurations.
 *
 * Removes all registered assets, scene configurations, and package information.
 * Used during hot reloading to reset the registry to a clean state.
 */
void AssetRegistry::clear()
{
    fonts_.clear();
    textures_.clear();
    materials_.clear();
    meshRecipes_.clear();
    sceneConfigs_.clear();
    defaultSceneId_ = 0; // Reset to invalid ID
    loadedPackages_.clear();
}

// Scene configuration methods

/**
 * @brief Register a scene configuration with the given ID.
 *
 * Stores the XML scene configuration string for later retrieval.
 * Scene configurations define how worlds should be generated.
 *
 * @param id Unique identifier for the scene configuration
 * @param sceneXml XML string containing the scene configuration
 */
void AssetRegistry::registerSceneConfig(AssetId id, const std::string &sceneXml)
{
    sceneConfigs_[id] = sceneXml;
}

/**
 * @brief Get a scene configuration by ID.
 *
 * Retrieves the XML string for a scene configuration.
 *
 * @param id The scene configuration identifier
 * @return Pointer to the XML string, or nullptr if not found
 */
const std::string *AssetRegistry::getSceneConfig(AssetId id) const
{
    auto it = sceneConfigs_.find(id);
    return (it != sceneConfigs_.end()) ? &it->second : nullptr;
}

/**
 * @brief Set the default scene configuration.
 *
 * Marks a scene configuration as the default one to use when no specific
 * scene is requested.
 *
 * @param id The scene configuration identifier to set as default
 */
void AssetRegistry::setDefaultScene(AssetId id)
{
    defaultSceneId_ = id;
}

/**
 * @brief Get the default scene configuration XML.
 *
 * Returns the XML string of the default scene configuration.
 *
 * @return Pointer to the default scene XML string, or nullptr if not set
 */
const std::string *AssetRegistry::getDefaultScene() const
{
    if (defaultSceneId_ == 0)
        return nullptr;
    return getSceneConfig(defaultSceneId_);
}

/**
 * @brief Get the ID of the default scene configuration.
 *
 * Returns the identifier of the scene configuration marked as default.
 *
 * @return The default scene configuration ID
 */
AssetId AssetRegistry::getDefaultSceneId() const
{
    return defaultSceneId_;
}


