#include "AssetCompilerService.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <algorithm>
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
            DEBUG_LOG("AssetCompilerService initialized with output directory: " << outputDirectory_);
        }
    }

    AssetCompilerService::~AssetCompilerService() = default;

    void AssetCompilerService::setOutputDirectory(const std::string &directory)
    {
        outputDirectory_ = directory;
        if (debugMode_ && Debug())
        {
            DEBUG_LOG("Asset output directory set to: " << outputDirectory_);
        }
    }

    void AssetCompilerService::setDebugMode(bool enabled)
    {
        debugMode_ = enabled;
        if (Debug())
        {
            DEBUG_LOG("Asset compiler debug mode: " << (enabled ? "enabled" : "disabled"));
        }
    }

    void AssetCompilerService::setOptimizationLevel(int level)
    {
        optimizationLevel_ = std::max(0, std::min(2, level));
        if (debugMode_ && Debug())
        {
            DEBUG_LOG("Asset compiler optimization level set to: " << optimizationLevel_);
        }
    }

    void AssetCompilerService::registerAssetType(const std::string &extension, AssetType type)
    {
        typeMapping_[extension] = type;
        if (debugMode_ && Debug())
        {
            DEBUG_LOG("Registered asset type mapping: " << extension << " -> " << static_cast<int>(type));
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
                DEBUG_LOG("Compiling asset: " << sourceFile);
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
            DEBUG_LOG("Compilation " << (result.success ? "succeeded" : "failed")
                                     << " in " << result.compilationTimeMs << "ms");
            if (!result.success)
            {
                DEBUG_LOG("Error: " << result.errorMessage);
            }
        }

        return result;
    }

    std::vector<CompilationResult> AssetCompilerService::compileAssetPackage(const std::string &packagePath)
    {
        std::vector<CompilationResult> results;

        if (debugMode_ && Debug())
        {
            DEBUG_LOG("Compiling asset package: " << normalizePath(packagePath));
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
            std::filesystem::path packagePath_fs(packagePath);
            std::filesystem::path packageXml = packagePath_fs / "package.xml";
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
            DEBUG_LOG("Compiling directory: " << normalizePath(sourcePath) << (recursive ? " (recursive)" : ""));
        }

        try
        {
            if (recursive)
            {
                for (const auto &entry : std::filesystem::recursive_directory_iterator(sourcePath))
                {
                    if (entry.is_regular_file())
                    {
                        std::filesystem::path entryPath = entry.path();
                        std::string filePath = entryPath.make_preferred().string();

                        // Skip files that are inside package directories
                        // Packages should only be compiled via compileAssetPackage()
                        std::string packageSeparator = "packages" + std::string(1, std::filesystem::path::preferred_separator);
                        if (filePath.find(packageSeparator) != std::string::npos)
                        {
                            if (debugMode_ && Debug())
                            {
                                DEBUG_LOG("Skipping package file during general scan: " << normalizePath(filePath));
                            }
                            continue;
                        }

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
                        std::filesystem::path entryPath = entry.path();
                        std::string filePath = entryPath.make_preferred().string();

                        // Skip files that are inside package directories
                        // Packages should only be compiled via compileAssetPackage()
                        std::string packageSeparator = "packages" + std::string(1, std::filesystem::path::preferred_separator);
                        if (filePath.find(packageSeparator) != std::string::npos)
                        {
                            if (debugMode_ && Debug())
                            {
                                DEBUG_LOG("Skipping package file during general scan: " << normalizePath(filePath));
                            }
                            continue;
                        }

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
                errors.push_back("Source file does not exist: " + sourceFile);
                return false;
            }

            // Check file permissions
            try
            {
                std::filesystem::file_status status = std::filesystem::status(sourceFile);
                if (status.type() != std::filesystem::file_type::regular)
                {
                    errors.push_back("Source path is not a regular file: " + sourceFile);
                    return false;
                }
            }
            catch (const std::exception &e)
            {
                errors.push_back("Cannot check file status for '" + sourceFile + "': " + std::string(e.what()));
                return false;
            }

            AssetType type = detectAssetType(sourceFile);
            if (type == AssetType::Unknown)
            {
                std::filesystem::path path(sourceFile);
                errors.push_back("Unknown or unsupported asset type for extension '" + path.extension().string() + "' in file: " + sourceFile);
                return false;
            }

            // Check file size first for all types
            size_t fileSize = 0;
            try
            {
                fileSize = std::filesystem::file_size(sourceFile);
                if (fileSize == 0)
                {
                    errors.push_back("Asset file is empty (0 bytes): " + sourceFile);
                    return false;
                }
            }
            catch (const std::exception &e)
            {
                errors.push_back("Cannot determine file size for '" + sourceFile + "': " + std::string(e.what()));
                return false;
            }

            // Type-specific validation
            switch (type)
            {
            case AssetType::Texture:
                // Basic texture validation
                if (debugMode_ && Debug())
                {
                    DEBUG_LOG("Validating texture file: " << sourceFile << " (size: " << fileSize << " bytes)");
                }
                // Could add more sophisticated image format validation here
                break;

            case AssetType::Scene:
            case AssetType::Entity:
            {
                if (debugMode_ && Debug())
                {
                    DEBUG_LOG("Validating XML file: " << sourceFile << " (size: " << fileSize << " bytes)");
                }

                // XML validation for scene/entity files
                std::ifstream file(sourceFile);
                if (!file.is_open())
                {
                    errors.push_back("Cannot open XML file for reading: " + sourceFile + " (errno: " + std::strerror(errno) + ")");
                    return false;
                }

                try
                {
                    std::string content((std::istreambuf_iterator<char>(file)),
                                        std::istreambuf_iterator<char>());

                    if (content.empty())
                    {
                        errors.push_back("XML file content is empty after reading: " + sourceFile);
                        return false;
                    }

                    // Basic XML structure validation
                    if (content.find('<') == std::string::npos)
                    {
                        errors.push_back("XML file does not contain any XML tags: " + sourceFile);
                        return false;
                    }

                    // Check for basic XML structure
                    size_t openTags = std::count(content.begin(), content.end(), '<');
                    size_t closeTags = std::count(content.begin(), content.end(), '>');

                    if (openTags != closeTags)
                    {
                        errors.push_back("XML file has mismatched angle brackets (< vs >): " + sourceFile +
                                         " (found " + std::to_string(openTags) + " '<' and " +
                                         std::to_string(closeTags) + " '>' characters)");
                        return false;
                    }

                    // Check for XML declaration or root element
                    if (content.find("<?xml") == std::string::npos &&
                        content.find("<scene") == std::string::npos &&
                        content.find("<entity") == std::string::npos &&
                        content.find("<root") == std::string::npos)
                    {
                        errors.push_back("XML file does not contain recognizable XML declaration or root element: " + sourceFile);
                        return false;
                    }

                    if (debugMode_ && Debug())
                    {
                        DEBUG_LOG("XML validation passed for: " << sourceFile);
                    }
                }
                catch (const std::exception &e)
                {
                    errors.push_back("Exception while reading XML file '" + sourceFile + "': " + std::string(e.what()));
                    return false;
                }
            }
            break;

            case AssetType::Audio:
                if (debugMode_ && Debug())
                {
                    DEBUG_LOG("Validating audio file: " << sourceFile << " (size: " << fileSize << " bytes)");
                }
                // Could add audio format validation here
                break;

            default:
                // Basic file validation for other types
                if (debugMode_ && Debug())
                {
                    DEBUG_LOG("Validating generic asset file: " << sourceFile << " (size: " << fileSize << " bytes)");
                }
                break;
            }

            return true;
        }
        catch (const std::exception &e)
        {
            errors.push_back("Exception during validation of '" + sourceFile + "': " + std::string(e.what()));
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
                    DEBUG_LOG("Asset cache cleared");
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

        // Rebuild cache by compiling only asset packages
        if (std::filesystem::exists("assets/packages"))
        {
            compileDirectory("assets/packages", true);
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
            if (debugMode_ && Debug())
            {
                DEBUG_LOG("Starting texture compilation for: " << sourceFile);
            }

            // Simple texture compilation - copy file with optimized format
            std::string outputPath = getCompiledPath(sourceFile, ".tex");

            if (debugMode_ && Debug())
            {
                DEBUG_LOG("Output path determined: " << normalizePath(outputPath));
            }

            // Ensure output directory exists
            std::filesystem::path outputDir = std::filesystem::path(outputPath).parent_path();
            try
            {
                if (!std::filesystem::exists(outputDir))
                {
                    std::filesystem::create_directories(outputDir);
                    if (debugMode_ && Debug())
                    {
                        DEBUG_LOG("Created output directory: " << outputDir.string());
                    }
                }
            }
            catch (const std::exception &e)
            {
                result.success = false;
                result.errorMessage = "Failed to create output directory '" + outputDir.string() + "': " + std::string(e.what());
                if (debugMode_ && Debug())
                {
                    DEBUG_LOG("Directory creation failed: " << result.errorMessage);
                }
                return result;
            }

            // Open source file
            std::ifstream source(sourceFile, std::ios::binary);
            if (!source.is_open())
            {
                result.success = false;
                result.errorMessage = "Failed to open source texture file '" + sourceFile + "': " + std::strerror(errno);
                if (debugMode_ && Debug())
                {
                    DEBUG_LOG("Source file open failed: " << result.errorMessage);
                }
                return result;
            }

            if (debugMode_ && Debug())
            {
                DEBUG_LOG("Source texture file opened successfully");
            }

            // Open destination file
            std::ofstream dest(outputPath, std::ios::binary);
            if (!dest.is_open())
            {
                result.success = false;
                result.errorMessage = "Failed to create destination texture file '" + outputPath + "': " + std::strerror(errno);
                if (debugMode_ && Debug())
                {
                    DEBUG_LOG("Destination file creation failed: " << result.errorMessage);
                }
                return result;
            }

            if (debugMode_ && Debug())
            {
                DEBUG_LOG("Destination texture file created successfully");
            }

            // Copy file content
            try
            {
                dest << source.rdbuf();

                // Check for stream errors
                if (source.bad())
                {
                    result.success = false;
                    result.errorMessage = "Error reading from source texture file '" + sourceFile + "' during copy operation";
                    if (debugMode_ && Debug())
                    {
                        DEBUG_LOG("Source read error: " << result.errorMessage);
                    }
                    return result;
                }

                if (dest.bad())
                {
                    result.success = false;
                    result.errorMessage = "Error writing to destination texture file '" + outputPath + "' during copy operation";
                    if (debugMode_ && Debug())
                    {
                        DEBUG_LOG("Destination write error: " << result.errorMessage);
                    }
                    return result;
                }

                // Close files explicitly
                source.close();
                dest.close();

                // Verify the output file was created and has content
                if (!std::filesystem::exists(outputPath))
                {
                    result.success = false;
                    result.errorMessage = "Output texture file '" + outputPath + "' was not created despite successful copy operation";
                    if (debugMode_ && Debug())
                    {
                        DEBUG_LOG("Output file verification failed: " << result.errorMessage);
                    }
                    return result;
                }

                auto outputSize = std::filesystem::file_size(outputPath);
                if (outputSize == 0)
                {
                    result.success = false;
                    result.errorMessage = "Output texture file '" + outputPath + "' is empty after copy operation";
                    if (debugMode_ && Debug())
                    {
                        DEBUG_LOG("Output file size verification failed: " << result.errorMessage);
                    }
                    return result;
                }

                result.success = true;
                result.outputPath = outputPath;
                result.outputSizeBytes = outputSize;

                if (debugMode_ && Debug())
                {
                    DEBUG_LOG("Texture compilation successful: " << normalizePath(sourceFile) << " -> " << normalizePath(outputPath)
                                                                 << " (size: " << outputSize << " bytes)");
                }
            }
            catch (const std::exception &e)
            {
                result.success = false;
                result.errorMessage = "Texture file copy operation failed: " + std::string(e.what());
                if (debugMode_ && Debug())
                {
                    DEBUG_LOG("File copy exception: " << result.errorMessage);
                }
                return result;
            }
        }
        catch (const std::exception &e)
        {
            result.success = false;
            result.errorMessage = "Texture compilation error: " + std::string(e.what());
            if (debugMode_ && Debug())
            {
                DEBUG_LOG("Texture compilation exception: " << result.errorMessage);
            }
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
            DEBUG_LOG("Mesh compilation placeholder for: " << sourceFile);
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
                    DEBUG_LOG("Compiled material: " << normalizePath(sourceFile) << " -> " << normalizePath(outputPath));
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
            DEBUG_LOG("Audio compilation placeholder for: " << sourceFile);
        }

        return result;
    }

    CompilationResult AssetCompilerService::compileScene(const std::string &sourceFile, const AssetMetadata &metadata)
    {
        CompilationResult result;

        try
        {
            if (debugMode_ && Debug())
            {
                DEBUG_LOG("Starting scene compilation for: " << normalizePath(sourceFile));
            }

            // Scene compilation - validate and optimize XML
            std::string outputPath = getCompiledPath(sourceFile, ".scene");

            if (debugMode_ && Debug())
            {
                DEBUG_LOG("Output path determined: " << normalizePath(outputPath));
            }

            // For now, copy with validation
            std::vector<std::string> errors;
            if (!validateAsset(sourceFile, errors))
            {
                result.success = false;
                std::string allErrors = "Scene validation failed: ";
                for (size_t i = 0; i < errors.size(); ++i)
                {
                    if (i > 0)
                        allErrors += "; ";
                    allErrors += errors[i];
                }
                result.errorMessage = allErrors;

                if (debugMode_ && Debug())
                {
                    DEBUG_LOG("Scene validation failed: " << allErrors);
                }
                return result;
            }

            if (debugMode_ && Debug())
            {
                DEBUG_LOG("Scene validation passed, starting file I/O operations");
            }

            // Ensure output directory exists
            std::filesystem::path outputDir = std::filesystem::path(outputPath).parent_path();
            try
            {
                if (!std::filesystem::exists(outputDir))
                {
                    std::filesystem::create_directories(outputDir);
                    if (debugMode_ && Debug())
                    {
                        DEBUG_LOG("Created output directory: " << outputDir.string());
                    }
                }
            }
            catch (const std::exception &e)
            {
                result.success = false;
                result.errorMessage = "Failed to create output directory '" + outputDir.string() + "': " + std::string(e.what());
                if (debugMode_ && Debug())
                {
                    DEBUG_LOG("Directory creation failed: " << result.errorMessage);
                }
                return result;
            }

            // Open source file
            std::ifstream source(sourceFile, std::ios::binary);
            if (!source.is_open())
            {
                result.success = false;
                result.errorMessage = "Failed to open source file '" + sourceFile + "': " + std::strerror(errno);
                if (debugMode_ && Debug())
                {
                    DEBUG_LOG("Source file open failed: " << result.errorMessage);
                }
                return result;
            }

            if (debugMode_ && Debug())
            {
                DEBUG_LOG("Source file opened successfully");
            }

            // Open destination file
            std::ofstream dest(outputPath, std::ios::binary);
            if (!dest.is_open())
            {
                result.success = false;
                result.errorMessage = "Failed to create destination file '" + outputPath + "': " + std::strerror(errno);
                if (debugMode_ && Debug())
                {
                    DEBUG_LOG("Destination file creation failed: " << result.errorMessage);
                }
                return result;
            }

            if (debugMode_ && Debug())
            {
                DEBUG_LOG("Destination file created successfully");
            }

            // Copy file content
            try
            {
                dest << source.rdbuf();

                // Check for stream errors
                if (source.bad())
                {
                    result.success = false;
                    result.errorMessage = "Error reading from source file '" + sourceFile + "' during copy operation";
                    if (debugMode_ && Debug())
                    {
                        DEBUG_LOG("Source read error: " << result.errorMessage);
                    }
                    return result;
                }

                if (dest.bad())
                {
                    result.success = false;
                    result.errorMessage = "Error writing to destination file '" + outputPath + "' during copy operation";
                    if (debugMode_ && Debug())
                    {
                        DEBUG_LOG("Destination write error: " << result.errorMessage);
                    }
                    return result;
                }

                // Close files explicitly
                source.close();
                dest.close();

                // Verify the output file was created and has content
                if (!std::filesystem::exists(outputPath))
                {
                    result.success = false;
                    result.errorMessage = "Output file '" + outputPath + "' was not created despite successful copy operation";
                    if (debugMode_ && Debug())
                    {
                        DEBUG_LOG("Output file verification failed: " << result.errorMessage);
                    }
                    return result;
                }

                auto outputSize = std::filesystem::file_size(outputPath);
                if (outputSize == 0)
                {
                    result.success = false;
                    result.errorMessage = "Output file '" + outputPath + "' is empty after copy operation";
                    if (debugMode_ && Debug())
                    {
                        DEBUG_LOG("Output file size verification failed: " << result.errorMessage);
                    }
                    return result;
                }

                result.success = true;
                result.outputPath = outputPath;
                result.outputSizeBytes = outputSize;

                if (debugMode_ && Debug())
                {
                    DEBUG_LOG("Scene compilation successful: " << normalizePath(sourceFile) << " -> " << normalizePath(outputPath)
                                                               << " (size: " << outputSize << " bytes)");
                }
            }
            catch (const std::exception &e)
            {
                result.success = false;
                result.errorMessage = "File copy operation failed: " + std::string(e.what());
                if (debugMode_ && Debug())
                {
                    DEBUG_LOG("File copy exception: " << result.errorMessage);
                }
                return result;
            }
        }
        catch (const std::exception &e)
        {
            result.success = false;
            result.errorMessage = "Scene compilation error: " + std::string(e.what());
            if (debugMode_ && Debug())
            {
                DEBUG_LOG("Scene compilation exception: " << result.errorMessage);
            }
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

        // Normalize path separators for consistent display
        return outputPath.make_preferred().string();
    }

    std::string AssetCompilerService::normalizePath(const std::string &path)
    {
        return std::filesystem::path(path).make_preferred().string();
    }

} // namespace AssetCompilation
