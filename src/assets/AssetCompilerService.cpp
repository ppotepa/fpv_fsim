#include "AssetCompilerService.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include "../debug.h"

namespace AssetCompilation
{
    AssetCompilerService::AssetCompilerService()
        : outputDirectory_("runtime/data/compiled"), debugMode_(false), optimizationLevel_(1)
    {
        // Register default asset type mappings
        registerAssetType(".png", AssetType::Texture);
        registerAssetType(".jpg", AssetType::Texture);
        registerAssetType(".jpeg", AssetType::Texture);
        registerAssetType(".bmp", AssetType::Texture);
        registerAssetType(".tga", AssetType::Texture);

        registerAssetType(".obj", AssetType::Mesh);
        registerAssetType(".fbx", AssetType::Mesh);
        registerAssetType(".gltf", AssetType::Mesh);
        registerAssetType(".dae", AssetType::Mesh);

        registerAssetType(".wav", AssetType::Audio);
        registerAssetType(".mp3", AssetType::Audio);
        registerAssetType(".ogg", AssetType::Audio);

        registerAssetType(".xml", AssetType::Scene); // Scene or entity files

        if (Debug())
        {
            std::cout << "AssetCompilerService initialized with output directory: " << outputDirectory_ << std::endl;
        }
    }

    AssetCompilerService::~AssetCompilerService() = default;

    void AssetCompilerService::setOutputDirectory(const std::string &directory)
    {
        outputDirectory_ = directory;
        if (debugMode_ && Debug())
        {
            std::cout << "Asset output directory set to: " << outputDirectory_ << std::endl;
        }
    }

    void AssetCompilerService::setDebugMode(bool enabled)
    {
        debugMode_ = enabled;
        if (Debug())
        {
            std::cout << "Asset compiler debug mode: " << (enabled ? "enabled" : "disabled") << std::endl;
        }
    }

    void AssetCompilerService::setOptimizationLevel(int level)
    {
        optimizationLevel_ = std::max(0, std::min(2, level));
        if (debugMode_ && Debug())
        {
            std::cout << "Asset compiler optimization level set to: " << optimizationLevel_ << std::endl;
        }
    }

    void AssetCompilerService::registerAssetType(const std::string &extension, AssetType type)
    {
        typeMapping_[extension] = type;
        if (debugMode_ && Debug())
        {
            std::cout << "Registered asset type mapping: " << extension << " -> " << static_cast<int>(type) << std::endl;
        }
    }

    CompilationResult AssetCompilerService::compileAsset(const std::string &sourceFile)
    {
        // Create default metadata
        AssetMetadata metadata;
        metadata.sourceFile = sourceFile;
        metadata.type = detectAssetType(sourceFile);
        metadata.requiresCompilation = true;

        return compileAsset(sourceFile, metadata);
    }

    CompilationResult AssetCompilerService::compileAsset(const std::string &sourceFile, const AssetMetadata &metadata)
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        CompilationResult result;

        try
        {
            if (debugMode_ && Debug())
            {
                std::cout << "Compiling asset: " << sourceFile << std::endl;
            }

            // Validate source file exists
            if (!std::filesystem::exists(sourceFile))
            {
                result.success = false;
                result.errorMessage = "Source file does not exist: " + sourceFile;
                return result;
            }

            // Ensure output directory exists
            if (!ensureOutputDirectory())
            {
                result.success = false;
                result.errorMessage = "Failed to create output directory: " + outputDirectory_;
                return result;
            }

            // Check if compilation is needed
            std::string compiledPath = getCompiledPath(sourceFile);
            if (!metadata.requiresCompilation && isUpToDate(sourceFile, compiledPath))
            {
                result.success = true;
                result.outputPath = compiledPath;
                result.errorMessage = "Asset is up to date, skipped compilation";
                statistics_.assetsSkipped++;
                return result;
            }

            // Compile based on asset type
            switch (metadata.type)
            {
            case AssetType::Texture:
                result = compileTexture(sourceFile, metadata);
                break;
            case AssetType::Mesh:
                result = compileMesh(sourceFile, metadata);
                break;
            case AssetType::Material:
                result = compileMaterial(sourceFile, metadata);
                break;
            case AssetType::Audio:
                result = compileAudio(sourceFile, metadata);
                break;
            case AssetType::Scene:
                result = compileScene(sourceFile, metadata);
                break;
            case AssetType::Entity:
                result = compileEntity(sourceFile, metadata);
                break;
            default:
                result.success = false;
                result.errorMessage = "Unknown or unsupported asset type";
                break;
            }

            // Update statistics
            if (result.success)
            {
                statistics_.assetsCompiled++;
                statistics_.totalInputSize += std::filesystem::file_size(sourceFile);
                if (std::filesystem::exists(result.outputPath))
                {
                    statistics_.totalOutputSize += std::filesystem::file_size(result.outputPath);
                }
            }
        }
        catch (const std::exception &e)
        {
            result.success = false;
            result.errorMessage = "Exception during compilation: " + std::string(e.what());
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        result.compilationTimeMs = std::chrono::duration<double, std::milli>(endTime - startTime).count();
        statistics_.totalCompilationTime += result.compilationTimeMs;

        if (debugMode_ && Debug())
        {
            std::cout << "Compilation " << (result.success ? "succeeded" : "failed")
                      << " in " << result.compilationTimeMs << "ms" << std::endl;
            if (!result.success)
            {
                std::cout << "Error: " << result.errorMessage << std::endl;
            }
        }

        return result;
    }

    std::vector<CompilationResult> AssetCompilerService::compileAssetPackage(const std::string &packagePath)
    {
        std::vector<CompilationResult> results;

        if (debugMode_ && Debug())
        {
            std::cout << "Compiling asset package: " << packagePath << std::endl;
        }

        try
        {
            if (!std::filesystem::exists(packagePath))
            {
                CompilationResult result;
                result.success = false;
                result.errorMessage = "Package path does not exist: " + packagePath;
                results.push_back(result);
                return results;
            }

            // Look for package.xml to get asset list
            std::string packageXml = packagePath + "/package.xml";
            if (std::filesystem::exists(packageXml))
            {
                // TODO: Parse package.xml to get asset list
                // For now, compile all supported files in directory
                results = compileDirectory(packagePath, true);
            }
            else
            {
                // No package.xml, compile all supported files
                results = compileDirectory(packagePath, true);
            }
        }
        catch (const std::exception &e)
        {
            CompilationResult result;
            result.success = false;
            result.errorMessage = "Exception during package compilation: " + std::string(e.what());
            results.push_back(result);
        }

        return results;
    }

    std::vector<CompilationResult> AssetCompilerService::compileDirectory(const std::string &sourcePath, bool recursive)
    {
        std::vector<CompilationResult> results;

        if (debugMode_ && Debug())
        {
            std::cout << "Compiling directory: " << sourcePath << (recursive ? " (recursive)" : "") << std::endl;
        }

        try
        {
            if (recursive)
            {
                for (const auto &entry : std::filesystem::recursive_directory_iterator(sourcePath))
                {
                    if (entry.is_regular_file())
                    {
                        std::string filePath = entry.path().string();
                        AssetType type = detectAssetType(filePath);

                        if (type != AssetType::Unknown)
                        {
                            CompilationResult result = compileAsset(filePath);
                            results.push_back(result);
                        }
                    }
                }
            }
            else
            {
                for (const auto &entry : std::filesystem::directory_iterator(sourcePath))
                {
                    if (entry.is_regular_file())
                    {
                        std::string filePath = entry.path().string();
                        AssetType type = detectAssetType(filePath);

                        if (type != AssetType::Unknown)
                        {
                            CompilationResult result = compileAsset(filePath);
                            results.push_back(result);
                        }
                    }
                }
            }
        }
        catch (const std::exception &e)
        {
            CompilationResult result;
            result.success = false;
            result.errorMessage = "Exception during directory compilation: " + std::string(e.what());
            results.push_back(result);
        }

        return results;
    }

    bool AssetCompilerService::validateAsset(const std::string &sourceFile, std::vector<std::string> &errors)
    {
        errors.clear();

        try
        {
            if (!std::filesystem::exists(sourceFile))
            {
                errors.push_back("Source file does not exist");
                return false;
            }

            AssetType type = detectAssetType(sourceFile);
            if (type == AssetType::Unknown)
            {
                errors.push_back("Unknown or unsupported asset type");
                return false;
            }

            // Type-specific validation
            switch (type)
            {
            case AssetType::Texture:
                // Basic texture validation - check if it's a valid image file
                if (std::filesystem::file_size(sourceFile) == 0)
                {
                    errors.push_back("Texture file is empty");
                    return false;
                }
                break;

            case AssetType::Scene:
            case AssetType::Entity:
            {
                // XML validation for scene/entity files
                std::ifstream file(sourceFile);
                if (file.is_open())
                {
                    std::string content((std::istreambuf_iterator<char>(file)),
                                        std::istreambuf_iterator<char>());
                    if (content.find('<') == std::string::npos)
                    {
                        errors.push_back("XML file does not contain valid XML content");
                        return false;
                    }
                }
                else
                {
                    errors.push_back("Cannot read XML file");
                    return false;
                }
            }
            break;

            default:
                // Basic file validation for other types
                if (std::filesystem::file_size(sourceFile) == 0)
                {
                    errors.push_back("Asset file is empty");
                    return false;
                }
                break;
            }

            return true;
        }
        catch (const std::exception &e)
        {
            errors.push_back("Exception during validation: " + std::string(e.what()));
            return false;
        }
    }

    std::vector<std::string> AssetCompilerService::getDependencies(const std::string &sourceFile)
    {
        std::vector<std::string> dependencies;

        // Basic dependency detection - can be enhanced for specific asset types
        AssetType type = detectAssetType(sourceFile);

        if (type == AssetType::Scene || type == AssetType::Entity)
        {
            // For XML files, look for asset references
            try
            {
                std::ifstream file(sourceFile);
                if (file.is_open())
                {
                    std::string content((std::istreambuf_iterator<char>(file)),
                                        std::istreambuf_iterator<char>());

                    // Simple dependency extraction - look for material_id, mesh_id, etc.
                    // This could be enhanced with proper XML parsing
                    // For now, just return empty dependencies
                }
            }
            catch (...)
            {
                // Ignore errors in dependency detection
            }
        }

        return dependencies;
    }

    bool AssetCompilerService::isUpToDate(const std::string &sourceFile, const std::string &compiledFile)
    {
        try
        {
            if (!std::filesystem::exists(compiledFile))
            {
                return false;
            }

            auto sourceTime = std::filesystem::last_write_time(sourceFile);
            auto compiledTime = std::filesystem::last_write_time(compiledFile);

            return compiledTime >= sourceTime;
        }
        catch (...)
        {
            return false;
        }
    }

    void AssetCompilerService::clearCache()
    {
        try
        {
            if (std::filesystem::exists(outputDirectory_))
            {
                std::filesystem::remove_all(outputDirectory_);
                std::filesystem::create_directories(outputDirectory_);

                if (debugMode_ && Debug())
                {
                    std::cout << "Asset cache cleared" << std::endl;
                }
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error clearing cache: " << e.what() << std::endl;
        }
    }

    void AssetCompilerService::rebuildCache()
    {
        clearCache();

        // Rebuild cache by compiling all assets in the assets directory
        if (std::filesystem::exists("assets"))
        {
            compileDirectory("assets", true);
        }
    }

    size_t AssetCompilerService::getCacheSize() const
    {
        size_t totalSize = 0;

        try
        {
            if (std::filesystem::exists(outputDirectory_))
            {
                for (const auto &entry : std::filesystem::recursive_directory_iterator(outputDirectory_))
                {
                    if (entry.is_regular_file())
                    {
                        totalSize += entry.file_size();
                    }
                }
            }
        }
        catch (...)
        {
            // Ignore errors
        }

        return totalSize;
    }

    const AssetCompilerService::Statistics &AssetCompilerService::getStatistics() const
    {
        return statistics_;
    }

    void AssetCompilerService::resetStatistics()
    {
        statistics_ = Statistics{};
    }

    // Private implementation methods

    CompilationResult AssetCompilerService::compileTexture(const std::string &sourceFile, const AssetMetadata &metadata)
    {
        CompilationResult result;

        try
        {
            // Simple texture compilation - copy file with optimized format
            std::string outputPath = getCompiledPath(sourceFile, ".tex");

            // For demo purposes, just copy the file with metadata
            std::ifstream source(sourceFile, std::ios::binary);
            std::ofstream dest(outputPath, std::ios::binary);

            if (source && dest)
            {
                dest << source.rdbuf();

                result.success = true;
                result.outputPath = outputPath;
                result.outputSizeBytes = std::filesystem::file_size(outputPath);

                if (debugMode_ && Debug())
                {
                    std::cout << "Compiled texture: " << sourceFile << " -> " << outputPath << std::endl;
                }
            }
            else
            {
                result.success = false;
                result.errorMessage = "Failed to copy texture file";
            }
        }
        catch (const std::exception &e)
        {
            result.success = false;
            result.errorMessage = "Texture compilation error: " + std::string(e.what());
        }

        return result;
    }

    CompilationResult AssetCompilerService::compileMesh(const std::string &sourceFile, const AssetMetadata &metadata)
    {
        CompilationResult result;

        // Placeholder mesh compilation
        result.success = true;
        result.outputPath = getCompiledPath(sourceFile, ".mesh");
        result.errorMessage = "Mesh compilation not fully implemented yet";

        if (debugMode_ && Debug())
        {
            std::cout << "Mesh compilation placeholder for: " << sourceFile << std::endl;
        }

        return result;
    }

    CompilationResult AssetCompilerService::compileMaterial(const std::string &sourceFile, const AssetMetadata &metadata)
    {
        CompilationResult result;

        try
        {
            // Material compilation - process XML to binary format
            std::string outputPath = getCompiledPath(sourceFile, ".mat");

            // Simple copy for now - could add optimization and validation
            std::ifstream source(sourceFile, std::ios::binary);
            std::ofstream dest(outputPath, std::ios::binary);

            if (source && dest)
            {
                dest << source.rdbuf();

                result.success = true;
                result.outputPath = outputPath;
                result.outputSizeBytes = std::filesystem::file_size(outputPath);

                if (debugMode_ && Debug())
                {
                    std::cout << "Compiled material: " << sourceFile << " -> " << outputPath << std::endl;
                }
            }
            else
            {
                result.success = false;
                result.errorMessage = "Failed to compile material file";
            }
        }
        catch (const std::exception &e)
        {
            result.success = false;
            result.errorMessage = "Material compilation error: " + std::string(e.what());
        }

        return result;
    }

    CompilationResult AssetCompilerService::compileAudio(const std::string &sourceFile, const AssetMetadata &metadata)
    {
        CompilationResult result;

        // Placeholder audio compilation
        result.success = true;
        result.outputPath = getCompiledPath(sourceFile, ".audio");
        result.errorMessage = "Audio compilation not fully implemented yet";

        if (debugMode_ && Debug())
        {
            std::cout << "Audio compilation placeholder for: " << sourceFile << std::endl;
        }

        return result;
    }

    CompilationResult AssetCompilerService::compileScene(const std::string &sourceFile, const AssetMetadata &metadata)
    {
        CompilationResult result;

        try
        {
            // Scene compilation - validate and optimize XML
            std::string outputPath = getCompiledPath(sourceFile, ".scene");

            // For now, copy with validation
            std::vector<std::string> errors;
            if (!validateAsset(sourceFile, errors))
            {
                result.success = false;
                result.errorMessage = "Scene validation failed: " + errors[0];
                return result;
            }

            std::ifstream source(sourceFile, std::ios::binary);
            std::ofstream dest(outputPath, std::ios::binary);

            if (source && dest)
            {
                dest << source.rdbuf();

                result.success = true;
                result.outputPath = outputPath;
                result.outputSizeBytes = std::filesystem::file_size(outputPath);

                if (debugMode_ && Debug())
                {
                    std::cout << "Compiled scene: " << sourceFile << " -> " << outputPath << std::endl;
                }
            }
            else
            {
                result.success = false;
                result.errorMessage = "Failed to compile scene file";
            }
        }
        catch (const std::exception &e)
        {
            result.success = false;
            result.errorMessage = "Scene compilation error: " + std::string(e.what());
        }

        return result;
    }

    CompilationResult AssetCompilerService::compileEntity(const std::string &sourceFile, const AssetMetadata &metadata)
    {
        CompilationResult result;

        // Similar to scene compilation
        return compileScene(sourceFile, metadata);
    }

    AssetType AssetCompilerService::detectAssetType(const std::string &sourceFile)
    {
        std::filesystem::path path(sourceFile);
        std::string extension = path.extension().string();

        // Convert to lowercase for case-insensitive matching
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

        auto it = typeMapping_.find(extension);
        if (it != typeMapping_.end())
        {
            return it->second;
        }

        return AssetType::Unknown;
    }

    std::string AssetCompilerService::generateChecksum(const std::string &filePath)
    {
        // Simple checksum based on file size and modification time
        try
        {
            auto size = std::filesystem::file_size(filePath);
            auto time = std::filesystem::last_write_time(filePath);

            std::stringstream ss;
            ss << std::hex << size << "_" << time.time_since_epoch().count();
            return ss.str();
        }
        catch (...)
        {
            return "unknown";
        }
    }

    bool AssetCompilerService::ensureOutputDirectory()
    {
        try
        {
            if (!std::filesystem::exists(outputDirectory_))
            {
                std::filesystem::create_directories(outputDirectory_);
            }
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    std::string AssetCompilerService::getCompiledPath(const std::string &sourceFile, const std::string &extension)
    {
        std::filesystem::path sourcePath(sourceFile);
        std::filesystem::path relativePath = std::filesystem::relative(sourcePath);

        std::filesystem::path outputPath = std::filesystem::path(outputDirectory_) / relativePath;
        outputPath.replace_extension(extension);

        return outputPath.string();
    }

} // namespace AssetCompilation
