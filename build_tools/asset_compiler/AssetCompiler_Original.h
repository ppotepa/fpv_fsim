#ifndef ASSET_COMPILER_H
#define ASSET_COMPILER_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#ifdef HAVE_PUGIXML
// Forward declarations
class IXmlParser;
class VoxelMeshGenerator;
class ProceduralTextureGenerator;
#endif

/**
 * @brief Error information from asset compilation.
 */
struct CompilationError
{
    std::string file;       /**< File where error occurred */
    int line;              /**< Line number (if applicable) */
    std::string message;   /**< Error description */
    std::string severity;  /**< "error", "warning", "info" */
};

/**
 * @brief Asset compiler for processing raw asset definitions into optimized runtime formats.
 * 
 * The AssetCompiler processes package XML files, validates them against schemas,
 * generates procedural assets, and outputs optimized binary packs for production use.
 * In debug mode, it can also generate intermediate representations for hot-reloading.
 */
class AssetCompiler
{
public:
    /**
     * @brief Construct a new AssetCompiler.
     */
    AssetCompiler();

    /**
     * @brief Destroy the compiler and clean up resources.
     */
    ~AssetCompiler();

    /**
     * @brief Process an asset package configuration file.
     * 
     * @param configFile Path to the package.xml file to process
     * @return true if processing succeeded, false if errors occurred
     */
    bool processAssetConfiguration(const std::string& configFile);

    /**
     * @brief Validate XML content against an XSD schema.
     * 
     * @param xmlFile Path to the XML file to validate
     * @param schemaFile Path to the XSD schema file
     * @return true if validation passes, false if there are errors
     */
    bool validateAgainstSchema(const std::string& xmlFile, const std::string& schemaFile);

    /**
     * @brief Get all compilation errors that occurred.
     * 
     * @return Vector of compilation errors
     */
    std::vector<CompilationError> getErrors() const;

    /**
     * @brief Get all compilation warnings that occurred.
     * 
     * @return Vector of compilation warnings
     */
    std::vector<CompilationError> getWarnings() const;

    /**
     * @brief Set the output directory for compiled assets.
     * 
     * @param outputDir Path to the directory where .pak files will be written
     */
    void setOutputDirectory(const std::string& outputDir);

    /**
     * @brief Set whether to enable debug mode (generates IR for hot-reloading).
     * 
     * @param enable true to enable debug mode, false for release mode
     */
    void setDebugMode(bool enable);

    /**
     * @brief Set whether to enable aggressive optimizations for release builds.
     * 
     * @param enable true to enable optimizations, false to disable
     */
    void setOptimizationsEnabled(bool enable);

    /**
     * @brief Clear all errors and warnings.
     */
    void clearDiagnostics();

private:
    /**
     * @brief Process a single package XML file.
     * 
     * @param packageFile Path to the package.xml file
     * @param packageName Name of the package (derived from file or explicit)
     * @return true if processing succeeded
     */
    bool processPackage(const std::string& packageFile, const std::string& packageName);

    /**
     * @brief Process texture assets from XML.
     * 
     * @param texturesPath XPath to textures section in XML
     * @return true if processing succeeded
     */
    bool processTextures(const std::string& texturesPath);

    /**
     * @brief Process mesh assets from XML.
     * 
     * @param meshesPath XPath to meshes section in XML
     * @return true if processing succeeded
     */
    bool processMeshes(const std::string& meshesPath);

    /**
     * @brief Process material assets from XML.
     * 
     * @param materialsPath XPath to materials section in XML
     * @return true if processing succeeded
     */
    bool processMaterials(const std::string& materialsPath);

    /**
     * @brief Process shader assets from XML.
     * 
     * @param shadersPath XPath to shaders section in XML
     * @return true if processing succeeded
     */
    bool processShaders(const std::string& shadersPath);

    /**
     * @brief Process scene configurations from XML.
     * 
     * @param scenesPath XPath to scenes section in XML
     * @return true if processing succeeded
     */
    bool processScenes(const std::string& scenesPath);

    /**
     * @brief Generate a texture asset from procedural parameters.
     * 
     * @param params Texture generation parameters from XML
     * @param outputPath Where to write the generated texture
     * @return true if generation succeeded
     */
    bool generateProceduralTexture(const std::unordered_map<std::string, std::string>& params, const std::string& outputPath);

    /**
     * @brief Generate a mesh asset from procedural parameters.
     * 
     * @param params Mesh generation parameters from XML
     * @param outputPath Where to write the generated mesh
     * @return true if generation succeeded
     */
    bool generateProceduralMesh(const std::unordered_map<std::string, std::string>& params, const std::string& outputPath);

    /**
     * @brief Write a binary asset pack file.
     * 
     * @param packageName Name of the package
     * @param assets Map of asset IDs to asset data
     * @return true if writing succeeded
     */
    bool writeBinaryPack(const std::string& packageName, const std::unordered_map<uint32_t, std::vector<uint8_t>>& assets);

    /**
     * @brief Add an error to the diagnostics.
     * 
     * @param file File where error occurred
     * @param line Line number
     * @param message Error message
     */
    void addError(const std::string& file, int line, const std::string& message);

    /**
     * @brief Add a warning to the diagnostics.
     * 
     * @param file File where warning occurred
     * @param line Line number
     * @param message Warning message
     */
    void addWarning(const std::string& file, int line, const std::string& message);

private:
#ifdef HAVE_PUGIXML
    std::unique_ptr<IXmlParser> xmlParser_;                    /**< XML parser implementation */
    std::unique_ptr<VoxelMeshGenerator> meshGenerator_;        /**< Procedural mesh generator */
    std::unique_ptr<ProceduralTextureGenerator> textureGenerator_; /**< Procedural texture generator */
#endif
    
    std::vector<CompilationError> errors_;                     /**< Compilation errors */
    std::vector<CompilationError> warnings_;                   /**< Compilation warnings */
    
    std::string outputDirectory_;                              /**< Output directory for .pak files */
    bool debugMode_;                                          /**< Whether debug mode is enabled */
    bool optimizationsEnabled_;                               /**< Whether optimizations are enabled */
    
    std::string currentFile_;                                 /**< Currently processing file */
    std::unordered_map<std::string, uint32_t> assetIdMap_;   /**< Map asset names to numeric IDs */
    uint32_t nextAssetId_;                                   /**< Next available asset ID */
};

#endif // ASSET_COMPILER_H
