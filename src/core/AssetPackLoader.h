#ifndef ASSET_PACK_LOADER_H
#define ASSET_PACK_LOADER_H

#include "AssetRegistry.h"
#include <memory>
#include <string>

/**
 * @brief Loads and parses asset packages from XML files.
 *
 * The AssetPackLoader is responsible for reading XML package files,
 * parsing their contents, and registering the defined assets with
 * the AssetRegistry. It supports loading different types of assets
 * including fonts, textures, materials, and mesh recipes.
 */
class AssetPackLoader
{
public:
    /**
     * @brief Construct an asset pack loader with a reference to the registry.
     *
     * @param registry Reference to the asset registry where loaded assets will be stored
     */
    AssetPackLoader(AssetRegistry &registry);

    /**
     * @brief Destroy the asset pack loader.
     */
    ~AssetPackLoader();

    /**
     * @brief Load a package from an XML file.
     *
     * Reads the XML file, parses its contents, and registers all assets
     * and configurations with the asset registry.
     *
     * @param packagePath Path to the XML package file
     * @return true if loading succeeded, false otherwise
     */
    bool loadPackage(const std::string &packagePath);

    /**
     * @brief Load the developer package specifically.
     *
     * Convenience method that loads the developer package from the
     * standard location (assets/packages/DeveloperPackage/package.xml).
     *
     * @return true if loading succeeded, false otherwise
     */
    bool loadDeveloperPackage();

private:
    AssetRegistry &registry_; /**< Reference to the asset registry */

    /**
     * @brief Parse the assets section from XML content.
     *
     * @param xmlContent The raw XML content string
     * @param packageName Name of the package being loaded
     * @return true if parsing succeeded, false otherwise
     */
    bool parseAssets(const std::string &xmlContent, const std::string &packageName);

    /**
     * @brief Parse the configurations section from XML content.
     *
     * @param xmlContent The raw XML content string
     * @param packageName Name of the package being loaded
     * @return true if parsing succeeded, false otherwise
     */
    bool parseConfigurations(const std::string &xmlContent, const std::string &packageName);

    /**
     * @brief Parse a font asset from an XML node.
     *
     * @param xmlNode XML string containing the font asset definition
     * @return Unique pointer to the parsed font asset
     */
    std::unique_ptr<FontAsset> parseFontAsset(const std::string &xmlNode);

    /**
     * @brief Parse a texture asset from an XML node.
     *
     * @param xmlNode XML string containing the texture asset definition
     * @return Unique pointer to the parsed texture asset
     */
    std::unique_ptr<TextureAsset> parseTextureAsset(const std::string &xmlNode);

    /**
     * @brief Parse a material asset from an XML node.
     *
     * @param xmlNode XML string containing the material asset definition
     * @return Unique pointer to the parsed material asset
     */
    std::unique_ptr<MaterialAsset> parseMaterialAsset(const std::string &xmlNode);

    /**
     * @brief Parse a mesh recipe asset from an XML node.
     *
     * @param xmlNode XML string containing the mesh recipe asset definition
     * @return Unique pointer to the parsed mesh recipe asset
     */
    std::unique_ptr<MeshRecipeAsset> parseMeshRecipeAsset(const std::string &xmlNode);
};

#endif
