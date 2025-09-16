#ifndef ASSET_REGISTRY_H
#define ASSET_REGISTRY_H

#include <unordered_map>
#include <string>
#include <memory>
#include <variant>
#include <vector>
#include "AssetIds.h"

// Forward declarations for asset types
struct FontAsset;
struct TextureAsset;
struct MaterialAsset;
struct MeshRecipeAsset;

// Use numeric AssetId as defined in AssetIds.h for performance and consistency
using AssetId = Assets::AssetId;

/**
 * @brief Central registry for managing all game assets.
 *
 * The AssetRegistry stores and provides access to all types of assets used
 * in the simulation, including fonts, textures, materials, and mesh recipes.
 * It also manages package loading state and scene configurations for
 * data-driven world generation.
 */
class AssetRegistry
{
public:
    /**
     * @brief Construct an empty asset registry.
     */
    AssetRegistry();

    /**
     * @brief Destroy the asset registry and free all assets.
     */
    ~AssetRegistry();

    // Asset storage and retrieval

    /**
     * @brief Register a font asset with the given ID.
     *
     * @param id Unique identifier for the font asset
     * @param asset Unique pointer to the font asset
     */
    void registerFont(AssetId id, std::unique_ptr<FontAsset> asset);

    /**
     * @brief Register a texture asset with the given ID.
     *
     * @param id Unique identifier for the texture asset
     * @param asset Unique pointer to the texture asset
     */
    void registerTexture(AssetId id, std::unique_ptr<TextureAsset> asset);

    /**
     * @brief Register a material asset with the given ID.
     *
     * @param id Unique identifier for the material asset
     * @param asset Unique pointer to the material asset
     */
    void registerMaterial(AssetId id, std::unique_ptr<MaterialAsset> asset);

    /**
     * @brief Register a mesh recipe asset with the given ID.
     *
     * @param id Unique identifier for the mesh recipe asset
     * @param asset Unique pointer to the mesh recipe asset
     */
    void registerMeshRecipe(AssetId id, std::unique_ptr<MeshRecipeAsset> asset);

    /**
     * @brief Get a font asset by ID.
     *
     * @param id The asset identifier
     * @return Pointer to the font asset, or nullptr if not found
     */
    const FontAsset *getFont(AssetId id) const;

    /**
     * @brief Get a texture asset by ID.
     *
     * @param id The asset identifier
     * @return Pointer to the texture asset, or nullptr if not found
     */
    const TextureAsset *getTexture(AssetId id) const;

    /**
     * @brief Get a material asset by ID.
     *
     * @param id The asset identifier
     * @return Pointer to the material asset, or nullptr if not found
     */
    const MaterialAsset *getMaterial(AssetId id) const;

    /**
     * @brief Get a mesh recipe asset by ID.
     *
     * @param id The asset identifier
     * @return Pointer to the mesh recipe asset, or nullptr if not found
     */
    const MeshRecipeAsset *getMeshRecipe(AssetId id) const;

    // Package management

    /**
     * @brief Check if a package has been loaded.
     *
     * @param packageName Name of the package to check
     * @return true if the package is loaded, false otherwise
     */
    bool hasPackage(const std::string &packageName) const;

    /**
     * @brief Mark a package as loaded.
     *
     * @param packageName Name of the package to mark as loaded
     */
    void markPackageLoaded(const std::string &packageName);

    /**
     * @brief Get the list of all loaded packages.
     *
     * @return Const reference to the vector of loaded package names
     */
    const std::vector<std::string> &getLoadedPackages() const;

    // Scene configuration management

    /**
     * @brief Register a scene configuration with the given ID.
     *
     * @param id Unique identifier for the scene configuration
     * @param sceneXml XML string containing the scene configuration
     */
    void registerSceneConfig(AssetId id, const std::string &sceneXml);

    /**
     * @brief Get a scene configuration by ID.
     *
     * @param id The scene configuration identifier
     * @return Pointer to the XML string, or nullptr if not found
     */
    const std::string *getSceneConfig(AssetId id) const;

    /**
     * @brief Set the default scene configuration.
     *
     * @param id The scene configuration identifier to set as default
     */
    void setDefaultScene(AssetId id);

    /**
     * @brief Get the default scene configuration XML.
     *
     * @return Pointer to the default scene XML string, or nullptr if not set
     */
    const std::string *getDefaultScene() const;

    /**
     * @brief Get the ID of the default scene configuration.
     *
     * @return The default scene configuration ID
     */
    AssetId getDefaultSceneId() const;

    /**
     * @brief Clear all assets and configurations.
     *
     * Used for hot reloading to reset the registry state.
     */
    void clear();

private:
    std::unordered_map<AssetId, std::unique_ptr<FontAsset>> fonts_;             /**< Registered font assets */
    std::unordered_map<AssetId, std::unique_ptr<TextureAsset>> textures_;       /**< Registered texture assets */
    std::unordered_map<AssetId, std::unique_ptr<MaterialAsset>> materials_;     /**< Registered material assets */
    std::unordered_map<AssetId, std::unique_ptr<MeshRecipeAsset>> meshRecipes_; /**< Registered mesh recipe assets */

    // Scene configurations
    std::unordered_map<AssetId, std::string> sceneConfigs_; /**< Registered scene configurations */
    AssetId defaultSceneId_;                                /**< ID of the default scene configuration */

    std::vector<std::string> loadedPackages_; /**< List of loaded package names */
};

// Asset type definitions

/**
 * @brief Font asset data structure.
 *
 * Contains information needed to load and render fonts.
 */
struct FontAsset
{
    std::string path;  /**< File path to the font file */
    int size;          /**< Font size in points */
    bool antialiasing; /**< Whether to use antialiasing */
};

/**
 * @brief Texture asset data structure.
 *
 * Contains information needed to load and configure textures.
 */
struct TextureAsset
{
    std::string path;   /**< File path to the texture file */
    std::string format; /**< Texture format (e.g., "RGBA", "RGB") */
    bool mipmaps;       /**< Whether to generate mipmaps */
    std::string filter; /**< Texture filtering mode */
};

/**
 * @brief Material asset data structure.
 *
 * Contains shader and parameter information for materials.
 */
struct MaterialAsset
{
    std::string shaderId;                                                                /**< ID of the shader to use */
    std::unordered_map<std::string, std::variant<std::string, float, int, bool>> params; /**< Material parameters */
};

/**
 * @brief Mesh recipe asset data structure.
 *
 * Contains procedural generation parameters for meshes.
 */
struct MeshRecipeAsset
{
    std::string generator;                                                               /**< Name of the generator to use */
    std::unordered_map<std::string, std::variant<float, int, bool, std::string>> params; /**< Generation parameters */
};

#endif
