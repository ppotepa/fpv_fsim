#include "AssetRegistry.h"
#include <iostream>

AssetRegistry::AssetRegistry() {}

AssetRegistry::~AssetRegistry() {}

void AssetRegistry::registerFont(AssetId id, std::unique_ptr<FontAsset> asset)
{
    fonts_[id] = std::move(asset);
}

void AssetRegistry::registerTexture(AssetId id, std::unique_ptr<TextureAsset> asset)
{
    textures_[id] = std::move(asset);
}

void AssetRegistry::registerMaterial(AssetId id, std::unique_ptr<MaterialAsset> asset)
{
    materials_[id] = std::move(asset);
}

void AssetRegistry::registerMeshRecipe(AssetId id, std::unique_ptr<MeshRecipeAsset> asset)
{
    meshRecipes_[id] = std::move(asset);
}

const FontAsset *AssetRegistry::getFont(AssetId id) const
{
    auto it = fonts_.find(id);
    return it != fonts_.end() ? it->second.get() : nullptr;
}

const TextureAsset *AssetRegistry::getTexture(AssetId id) const
{
    auto it = textures_.find(id);
    return it != textures_.end() ? it->second.get() : nullptr;
}

const MaterialAsset *AssetRegistry::getMaterial(AssetId id) const
{
    auto it = materials_.find(id);
    return it != materials_.end() ? it->second.get() : nullptr;
}

const MeshRecipeAsset *AssetRegistry::getMeshRecipe(AssetId id) const
{
    auto it = meshRecipes_.find(id);
    return it != meshRecipes_.end() ? it->second.get() : nullptr;
}

bool AssetRegistry::hasPackage(const std::string &packageName) const
{
    return std::find(loadedPackages_.begin(), loadedPackages_.end(), packageName) != loadedPackages_.end();
}

void AssetRegistry::markPackageLoaded(const std::string &packageName)
{
    if (!hasPackage(packageName))
    {
        loadedPackages_.push_back(packageName);
    }
}

const std::vector<std::string> &AssetRegistry::getLoadedPackages() const
{
    return loadedPackages_;
}

void AssetRegistry::clear()
{
    fonts_.clear();
    textures_.clear();
    materials_.clear();
    meshRecipes_.clear();
    sceneConfigs_.clear();
    defaultSceneId_.clear();
    loadedPackages_.clear();
}

// Scene configuration methods
void AssetRegistry::registerSceneConfig(AssetId id, const std::string &sceneXml)
{
    sceneConfigs_[id] = sceneXml;
}

const std::string *AssetRegistry::getSceneConfig(AssetId id) const
{
    auto it = sceneConfigs_.find(id);
    return (it != sceneConfigs_.end()) ? &it->second : nullptr;
}

void AssetRegistry::setDefaultScene(AssetId id)
{
    defaultSceneId_ = id;
}

const std::string *AssetRegistry::getDefaultScene() const
{
    if (defaultSceneId_.empty())
        return nullptr;
    return getSceneConfig(defaultSceneId_);
}

AssetId AssetRegistry::getDefaultSceneId() const
{
    return defaultSceneId_;
}
