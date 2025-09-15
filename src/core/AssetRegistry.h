#ifndef ASSET_REGISTRY_H
#define ASSET_REGISTRY_H

#include <unordered_map>
#include <string>
#include <memory>
#include <variant>

// Forward declarations for asset types
struct FontAsset;
struct TextureAsset;
struct MaterialAsset;
struct MeshRecipeAsset;

using AssetId = std::string;

class AssetRegistry
{
public:
    AssetRegistry();
    ~AssetRegistry();

    // Asset storage and retrieval
    void registerFont(AssetId id, std::unique_ptr<FontAsset> asset);
    void registerTexture(AssetId id, std::unique_ptr<TextureAsset> asset);
    void registerMaterial(AssetId id, std::unique_ptr<MaterialAsset> asset);
    void registerMeshRecipe(AssetId id, std::unique_ptr<MeshRecipeAsset> asset);

    const FontAsset *getFont(AssetId id) const;
    const TextureAsset *getTexture(AssetId id) const;
    const MaterialAsset *getMaterial(AssetId id) const;
    const MeshRecipeAsset *getMeshRecipe(AssetId id) const;

    // Package management
    bool hasPackage(const std::string &packageName) const;
    void markPackageLoaded(const std::string &packageName);
    const std::vector<std::string> &getLoadedPackages() const;

    // Scene configuration management
    void registerSceneConfig(AssetId id, const std::string &sceneXml);
    const std::string *getSceneConfig(AssetId id) const;
    void setDefaultScene(AssetId id);
    const std::string *getDefaultScene() const;
    AssetId getDefaultSceneId() const;

    // Clear all assets (for hot reloading)
    void clear();

private:
    std::unordered_map<AssetId, std::unique_ptr<FontAsset>> fonts_;
    std::unordered_map<AssetId, std::unique_ptr<TextureAsset>> textures_;
    std::unordered_map<AssetId, std::unique_ptr<MaterialAsset>> materials_;
    std::unordered_map<AssetId, std::unique_ptr<MeshRecipeAsset>> meshRecipes_;

    // Scene configurations
    std::unordered_map<AssetId, std::string> sceneConfigs_;
    AssetId defaultSceneId_;

    std::vector<std::string> loadedPackages_;
};

// Asset type definitions
struct FontAsset
{
    std::string path;
    int size;
    bool antialiasing;
};

struct TextureAsset
{
    std::string path;
    std::string format;
    bool mipmaps;
    std::string filter;
};

struct MaterialAsset
{
    std::string shaderId;
    std::unordered_map<std::string, std::variant<std::string, float, int, bool>> params;
};

struct MeshRecipeAsset
{
    std::string generator;
    std::unordered_map<std::string, std::variant<float, int, bool>> params;
};

#endif
