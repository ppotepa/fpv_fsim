#pragma once

#include "Package.h"
#include "utils/IJsonParserUnified.h"
#include <string>
#include <memory>
#include <nlohmann/json.hpp>

namespace Assets
{

    // JSON parsing result
    struct PackageLoadResult
    {
        bool success = false;
        Package package;
        std::vector<std::string> errors;
        std::vector<std::string> warnings;
    };

    /**
     * @brief JSON-based package parser for loading package manifests.
     *
     * Replaces the XML-based PackageParser with JSON support.
     */
    class PackageJsonParser
    {
    private:
        std::unique_ptr<IJsonParserUnified> jsonParser_;

        // Helper methods for parsing different sections
        bool parsePackageMetadata(const nlohmann::json &json, Package &package);
        bool parseDependencies(const nlohmann::json &json, Package &package);
        bool parseAssets(const nlohmann::json &json, Package &package);
        bool parseScenes(const nlohmann::json &json, Package &package);

        // Asset parsing methods
        AssetDefinition parseAssetDefinition(const nlohmann::json &json, AssetType type);
        MaterialAssetData parseMaterialAssetData(const nlohmann::json &json);
        MeshAssetData parseMeshAssetData(const nlohmann::json &json);
        TextureAssetData parseTextureAssetData(const nlohmann::json &json);
        ShaderAssetData parseShaderAssetData(const nlohmann::json &json);
        AudioAssetData parseAudioAssetData(const nlohmann::json &json);

        // Scene parsing methods
        SceneDefinition parseSceneDefinition(const nlohmann::json &json);
        EntityDefinition parseEntityDefinition(const nlohmann::json &json);
        Component parseComponent(const nlohmann::json &json, ComponentType type);
        Transform parseTransform(const nlohmann::json &json);
        BehaviorParams parseBehaviorParams(const nlohmann::json &json);

        // Error handling
        void addError(const std::string &error);
        void addWarning(const std::string &warning);

    public:
        PackageJsonParser();
        explicit PackageJsonParser(std::unique_ptr<IJsonParserUnified> parser);
        ~PackageJsonParser() = default;

        /**
         * @brief Load package from JSON file
         * @param packagePath Path to package.json file
         * @return Package load result with success status and any errors
         */
        PackageLoadResult loadPackage(const std::string &packagePath);

        /**
         * @brief Load package from JSON string content
         * @param jsonContent JSON content as string
         * @return Package load result with success status and any errors
         */
        PackageLoadResult loadPackageFromString(const std::string &jsonContent);

        /**
         * @brief Validate JSON structure against package schema
         * @param json JSON object to validate
         * @return true if valid, false otherwise
         */
        bool validatePackageJson(const nlohmann::json &json);
    };

} // namespace Assets
