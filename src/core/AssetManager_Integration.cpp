bool AssetManager::registerWithAssetRegistry(Assets::AssetRegistry& registry) {
    if (!initialized) {
        std::cerr << "AssetManager not initialized" << std::endl;
        return false;
    }
    
    // First register all internal assets
    for (const auto& pair : internalAssets) {
        const AssetInfo& info = pair.second;
        
        // Convert internal asset type to AssetRegistry type
        Assets::AssetType registryType;
        switch (info.type) {
            case AssetType::TEXTURE: registryType = Assets::AssetType::Texture; break;
            case AssetType::FONT: registryType = Assets::AssetType::Font; break;
            case AssetType::AUDIO: registryType = Assets::AssetType::Audio; break;
            case AssetType::MATERIAL: registryType = Assets::AssetType::Material; break;
            case AssetType::MESH: registryType = Assets::AssetType::Mesh; break;
            case AssetType::SHADER: registryType = Assets::AssetType::Shader; break;
            case AssetType::SCENE: registryType = Assets::AssetType::Scene; break;
            default: registryType = Assets::AssetType::Unknown; break;
        }
        
        // Register with the AssetRegistry as an internal asset from "core" package
        Assets::AssetId assetId = registry.registerAsset(
            "core",            // Internal assets are considered part of the "core" package
            info.id,           // Use the same ID
            registryType,      // Converted asset type
            info.path          // Path to the asset file
        );
        
        if (assetId == Assets::INVALID_ASSET_ID) {
            std::cerr << "Failed to register internal asset: " << info.id << std::endl;
            // Continue even if registration fails
        }
    }
    
    return true;
}
