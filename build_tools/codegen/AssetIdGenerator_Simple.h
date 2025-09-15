#ifndef ASSET_ID_GENERATOR_SIMPLE_H
#define ASSET_ID_GENERATOR_SIMPLE_H

#include <string>
#include <vector>
#include <unordered_map>

/**
 * @brief Information about a discovered asset.
 */
struct AssetInfo
{
    std::string name;       /**< Asset name/identifier */
    std::string type;       /**< Asset type (texture, mesh, material, etc.) */
    std::string package;    /**< Package containing this asset */
    uint32_t numericId;     /**< Generated numeric ID */
    std::string sourceFile; /**< Source file where asset was defined */
};

/**
 * @brief Simplified Generator for asset ID mappings.
 */
class AssetIdGenerator
{
public:
    AssetIdGenerator();
    ~AssetIdGenerator();

    /**
     * @brief Scan a package file for assets.
     *
     * @param packageFile Path to the package file
     * @return true if scanning succeeded
     */
    bool scanPackageFile(const std::string &packageFile);

    /**
     * @brief Generate C++ header with asset ID constants.
     *
     * @param outputFile Path to output header file
     * @return true if generation succeeded
     */
    bool generateCppHeader(const std::string &outputFile);

    /**
     * @brief Print statistics about scanned assets.
     */
    void printStatistics() const;

    /**
     * @brief Get the assets that were discovered.
     */
    const std::unordered_map<std::string, AssetInfo> &getAssets() const;

private:
    std::unordered_map<std::string, AssetInfo> assets_;  /**< Discovered assets by name */
    std::unordered_map<uint32_t, std::string> idToName_; /**< Reverse mapping for collision detection */

    uint32_t nextSequentialId_; /**< Next sequential ID to assign */
    bool useHashBasedIds_;      /**< Whether to use hash-based IDs */

    // Statistics
    size_t totalPackagesScanned_; /**< Number of packages scanned */
    size_t totalScenesScanned_;   /**< Number of scenes scanned */
    size_t totalFilesScanned_;    /**< Total files scanned */
};

#endif // ASSET_ID_GENERATOR_SIMPLE_H
