#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace AssetCompilation
{
    enum class AssetType
    {
        Unknown,
        Texture,
        Mesh,
        Material,
        Audio,
        Scene,
        Entity
    };

    struct CompilationResult
    {
        bool success = false;
        std::string errorMessage;
        std::string outputPath;
        size_t outputSizeBytes = 0;
        double compilationTimeMs = 0.0;
    };

    struct AssetMetadata
    {
        std::string sourceFile;
        AssetType type;
        std::string targetFormat;
        std::unordered_map<std::string, std::string> parameters;
        bool requiresCompilation = true;
        std::string checksum;
    };

    /**
     * Runtime asset compilation service that processes raw assets into
     * optimized runtime formats with proper validation and caching.
     */
    class AssetCompilerService
    {
    public:
        AssetCompilerService();
        ~AssetCompilerService();

        // Configuration
        void setOutputDirectory(const std::string &directory);
        void setDebugMode(bool enabled);
        void setOptimizationLevel(int level); // 0=none, 1=basic, 2=aggressive

        // Asset type registration
        void registerAssetType(const std::string &extension, AssetType type);

        // Compilation methods
        CompilationResult compileAsset(const std::string &sourceFile);
        CompilationResult compileAsset(const std::string &sourceFile, const AssetMetadata &metadata);

        // Batch compilation
        std::vector<CompilationResult> compileAssetPackage(const std::string &packagePath);
        std::vector<CompilationResult> compileDirectory(const std::string &sourcePath, bool recursive = true);

        // Asset validation and dependency checking
        bool validateAsset(const std::string &sourceFile, std::vector<std::string> &errors);
        std::vector<std::string> getDependencies(const std::string &sourceFile);
        bool isUpToDate(const std::string &sourceFile, const std::string &compiledFile);

        // Cache management
        void clearCache();
        void rebuildCache();
        size_t getCacheSize() const;

        // Compiler statistics
        struct Statistics
        {
            size_t assetsCompiled = 0;
            size_t assetsCached = 0;
            size_t assetsSkipped = 0;
            double totalCompilationTime = 0.0;
            size_t totalInputSize = 0;
            size_t totalOutputSize = 0;
        };

        const Statistics &getStatistics() const;
        void resetStatistics();

    private:
        std::string outputDirectory_;
        bool debugMode_;
        int optimizationLevel_;
        std::unordered_map<std::string, AssetType> typeMapping_;
        Statistics statistics_;

        // Asset type specific compilers
        CompilationResult compileTexture(const std::string &sourceFile, const AssetMetadata &metadata);
        CompilationResult compileMesh(const std::string &sourceFile, const AssetMetadata &metadata);
        CompilationResult compileMaterial(const std::string &sourceFile, const AssetMetadata &metadata);
        CompilationResult compileAudio(const std::string &sourceFile, const AssetMetadata &metadata);
        CompilationResult compileScene(const std::string &sourceFile, const AssetMetadata &metadata);
        CompilationResult compileEntity(const std::string &sourceFile, const AssetMetadata &metadata);

        // Utility methods
        AssetType detectAssetType(const std::string &sourceFile);
        std::string generateChecksum(const std::string &filePath);
        bool ensureOutputDirectory();
        std::string getCompiledPath(const std::string &sourceFile, const std::string &extension = ".compiled");
    };

} // namespace AssetCompilation

