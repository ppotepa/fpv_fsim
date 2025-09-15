#ifndef ASSET_COMPILER_H
#define ASSET_COMPILER_H

#include <string>
#include <vector>
#include <unordered_map>

/**
 * @brief Error information from asset compilation.
 */
struct CompilationError
{
    std::string file;     /**< File where error occurred */
    int line;             /**< Line number (if applicable) */
    std::string message;  /**< Error description */
    std::string severity; /**< "error", "warning", "info" */
};

/**
 * @brief Simplified Asset compiler for demo purposes.
 */
class AssetCompiler
{
public:
    AssetCompiler();
    ~AssetCompiler();

    /**
     * @brief Process an asset configuration file.
     *
     * @param configFile Path to the configuration file
     * @return true if processing succeeded
     */
    bool processAssetConfiguration(const std::string &configFile);

    /**
     * @brief Set the output directory for compiled assets.
     *
     * @param outputDir Output directory path
     */
    void setOutputDirectory(const std::string &outputDir);

    /**
     * @brief Set whether to enable debug mode.
     *
     * @param enable true to enable debug mode, false for release mode
     */
    void setDebugMode(bool enable);

    /**
     * @brief Set whether to enable optimizations.
     *
     * @param enable true to enable optimizations, false to disable
     */
    void setOptimizationsEnabled(bool enable);

    /**
     * @brief Clear all errors and warnings.
     */
    void clearDiagnostics();

    /**
     * @brief Get compilation errors.
     *
     * @return vector of compilation errors
     */
    const std::vector<CompilationError> &getErrors() const;

    /**
     * @brief Get compilation warnings.
     *
     * @return vector of compilation warnings
     */
    const std::vector<CompilationError> &getWarnings() const;

private:
    /**
     * @brief Get or create a numeric ID for an asset name.
     */
    uint32_t getOrCreateAssetId(const std::string &assetName);

    /**
     * @brief Add an error to the diagnostics.
     */
    void addError(const std::string &file, int line, const std::string &message);

    /**
     * @brief Add a warning to the diagnostics.
     */
    void addWarning(const std::string &file, int line, const std::string &message);

private:
    std::vector<CompilationError> errors_;   /**< Compilation errors */
    std::vector<CompilationError> warnings_; /**< Compilation warnings */

    std::string outputDirectory_; /**< Output directory for .pak files */
    bool debugMode_;              /**< Whether debug mode is enabled */
    bool optimizationsEnabled_;   /**< Whether optimizations are enabled */

    std::string currentFile_;                              /**< Currently processing file */
    std::unordered_map<std::string, uint32_t> assetIdMap_; /**< Map asset names to numeric IDs */
    uint32_t nextAssetId_;                                 /**< Next available asset ID */
};

#endif // ASSET_COMPILER_H
