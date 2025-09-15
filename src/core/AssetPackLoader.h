#ifndef ASSET_PACK_LOADER_H
#define ASSET_PACK_LOADER_H

#include "AssetRegistry.h"
#include <memory>
#include <string>

class AssetPackLoader
{
public:
    AssetPackLoader(AssetRegistry &registry);
    ~AssetPackLoader();

    // Load a package from XML file
    bool loadPackage(const std::string &packagePath);

    // Load the developer package specifically
    bool loadDeveloperPackage();

private:
    AssetRegistry &registry_;

    // XML parsing helpers
    bool parseAssets(const std::string &xmlContent, const std::string &packageName);
    bool parseConfigurations(const std::string &xmlContent, const std::string &packageName);

    std::unique_ptr<FontAsset> parseFontAsset(const std::string &xmlNode);
    std::unique_ptr<TextureAsset> parseTextureAsset(const std::string &xmlNode);
    std::unique_ptr<MaterialAsset> parseMaterialAsset(const std::string &xmlNode);
    std::unique_ptr<MeshRecipeAsset> parseMeshRecipeAsset(const std::string &xmlNode);
};

#endif
