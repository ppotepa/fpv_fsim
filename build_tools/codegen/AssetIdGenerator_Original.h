#ifndef ASSET_ID_GENERATOR_H
#define ASSET_ID_GENERATOR_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#ifdef HAVE_PUGIXML
// Forward declarations
class IXmlParser;
#endif

/**
 * @brief Information about a discovered asset.
 */
struct AssetInfo
{
    std::string name;           /**< Asset name/identifier from XML */
    std::string type;           /**< Asset type (texture, mesh, material, etc.) */
    std::string package;        /**< Package containing this asset */
    uint32_t numericId;         /**< Generated numeric ID */
    std::string sourceFile;     /**< Source XML file where asset was defined */
};

/**
 * @brief Generator for stable numeric AssetId mappings from XML asset definitions.
 * 
 * This tool scans XML asset and scene files to collect all symbolic asset names,
 * generates stable numeric IDs for them, and outputs C++ headers or binary lookup
 * tables. This enforces the "strings only at the edges" principle by providing
 * compile-time constants for asset IDs.
 */
class AssetIdGenerator
{
public:
    /**
     * @brief Construct a new AssetIdGenerator.
     */
    AssetIdGenerator();

    /**
     * @brief Destroy the generator and clean up resources.
     */
    ~AssetIdGenerator();

    /**
     * @brief Scan a package XML file for asset definitions.
     * 
     * @param packageFile Path to the package.xml file to scan
     * @return true if scanning succeeded, false if errors occurred
     */
    bool scanPackageFile(const std::string& packageFile);

    /**
     * @brief Scan a scene XML file for asset references.
     * 
     * @param sceneFile Path to the scene.xml file to scan
     * @return true if scanning succeeded, false if errors occurred
     */
    bool scanSceneFile(const std::string& sceneFile);

    /**
     * @brief Scan all XML files in a directory recursively.
     * 
     * @param directory Path to the directory to scan
     * @return true if scanning succeeded, false if errors occurred
     */
    bool scanDirectory(const std::string& directory);

    /**
     * @brief Generate a C++ header file with asset ID constants.
     * 
     * @param outputFile Path to the output header file (e.g., "AssetIds.h")
     * @param namespaceName Namespace to place the constants in (optional)
     * @return true if generation succeeded, false if errors occurred
     */
    bool generateCppHeader(const std::string& outputFile, const std::string& namespaceName = "");

    /**
     * @brief Generate a binary lookup table file.
     * 
     * @param outputFile Path to the output binary file (e.g., "asset_ids.bin")
     * @return true if generation succeeded, false if errors occurred
     */
    bool generateBinaryTable(const std::string& outputFile);

    /**
     * @brief Generate a JSON mapping file for debugging/tooling.
     * 
     * @param outputFile Path to the output JSON file (e.g., "asset_ids.json")
     * @return true if generation succeeded, false if errors occurred
     */
    bool generateJsonMapping(const std::string& outputFile);

    /**
     * @brief Set the starting ID for asset numbering.
     * 
     * @param startId The first numeric ID to assign (default: 1)
     */
    void setStartingId(uint32_t startId);

    /**
     * @brief Set whether to use hash-based IDs instead of sequential IDs.
     * 
     * Hash-based IDs are more stable across changes but may have collisions.
     * 
     * @param useHashes true to use hash-based IDs, false for sequential
     */
    void setUseHashBasedIds(bool useHashes);

    /**
     * @brief Get all discovered assets.
     * 
     * @return Vector of asset information
     */
    std::vector<AssetInfo> getDiscoveredAssets() const;

    /**
     * @brief Get statistics about the discovered assets.
     * 
     * @return String with statistics summary
     */
    std::string getStatistics() const;

    /**
     * @brief Clear all discovered assets and reset state.
     */
    void clear();

private:
    /**
     * @brief Process asset definitions from XML content.
     * 
     * @param packageName Name of the package being processed
     * @param sourceFile Source file being processed
     * @return true if processing succeeded
     */
    bool processAssetDefinitions(const std::string& packageName, const std::string& sourceFile);

    /**
     * @brief Process asset references from scene XML content.
     * 
     * @param sceneFile Source scene file being processed
     * @return true if processing succeeded
     */
    bool processAssetReferences(const std::string& sceneFile);

    /**
     * @brief Register a discovered asset.
     * 
     * @param name Asset name
     * @param type Asset type
     * @param package Package name
     * @param sourceFile Source file
     */
    void registerAsset(const std::string& name, const std::string& type, 
                      const std::string& package, const std::string& sourceFile);

    /**
     * @brief Generate a stable numeric ID for an asset name.
     * 
     * @param assetName The asset name to generate an ID for
     * @return Generated numeric ID
     */
    uint32_t generateNumericId(const std::string& assetName);

    /**
     * @brief Hash function for asset names.
     * 
     * @param input Input string to hash
     * @return 32-bit hash value
     */
    uint32_t hashString(const std::string& input) const;

    /**
     * @brief Sanitize a string for use as a C++ identifier.
     * 
     * @param input Input string
     * @return Sanitized string suitable for C++ identifiers
     */
    std::string sanitizeIdentifier(const std::string& input) const;

private:
#ifdef HAVE_PUGIXML
    std::unique_ptr<IXmlParser> xmlParser_;                    /**< XML parser implementation */
#endif
    std::unordered_map<std::string, AssetInfo> assets_;       /**< Discovered assets by name */
    std::unordered_map<uint32_t, std::string> idToName_;      /**< Reverse mapping for collision detection */
    
    uint32_t nextSequentialId_;                               /**< Next sequential ID to assign */
    bool useHashBasedIds_;                                    /**< Whether to use hash-based IDs */
    
    // Statistics
    size_t totalPackagesScanned_;                             /**< Number of packages scanned */
    size_t totalScenesScanned_;                               /**< Number of scenes scanned */
    size_t totalFilesScanned_;                                /**< Total files scanned */
};

#endif // ASSET_ID_GENERATOR_H
