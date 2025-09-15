// Simple version of AssetCompiler without XML dependencies for demo purposes
#include "AssetCompiler.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

AssetCompiler::AssetCompiler()
    : debugMode_(false), optimizationsEnabled_(true), nextAssetId_(1)
{
    outputDirectory_ = "runtime/data/packs";
}

AssetCompiler::~AssetCompiler() = default;

bool AssetCompiler::processAssetConfiguration(const std::string &configFile)
{
    clearDiagnostics();
    currentFile_ = configFile;

    if (!std::filesystem::exists(configFile))
    {
        addError(configFile, 0, "Configuration file does not exist");
        return false;
    }

    // Simplified mode without XML parsing for demo
    std::cout << "Asset Compiler Demo Mode" << std::endl;
    std::cout << "Processing: " << configFile << std::endl;

    // Create output directory
    std::filesystem::create_directories(outputDirectory_);

    // Generate a demo asset ID for demonstration
    std::string assetName = "demo_texture";
    uint32_t assetId = getOrCreateAssetId(assetName);

    // Write a demo pack file
    std::string outputPath = outputDirectory_ + "/demo_pack.bin";
    std::ofstream output(outputPath, std::ios::binary);
    if (output.is_open())
    {
        // Simple pack format: magic header + asset count + asset entries
        std::string magic = "FPVSIM01";
        output.write(magic.c_str(), 8);

        uint32_t assetCount = 1;
        output.write(reinterpret_cast<const char *>(&assetCount), sizeof(assetCount));

        // Asset entry: ID + name length + name + data size + data
        output.write(reinterpret_cast<const char *>(&assetId), sizeof(assetId));

        uint32_t nameLength = static_cast<uint32_t>(assetName.length());
        output.write(reinterpret_cast<const char *>(&nameLength), sizeof(nameLength));
        output.write(assetName.c_str(), nameLength);

        std::string demoData = "Demo texture data for " + assetName;
        uint32_t dataSize = static_cast<uint32_t>(demoData.length());
        output.write(reinterpret_cast<const char *>(&dataSize), sizeof(dataSize));
        output.write(demoData.c_str(), dataSize);

        output.close();
        std::cout << "Created demo pack: " << outputPath << std::endl;
        std::cout << "Asset '" << assetName << "' assigned ID: " << assetId << std::endl;
        return true;
    }

    addError(configFile, 0, "Failed to create output pack");
    return false;
}

void AssetCompiler::setOutputDirectory(const std::string &outputDir)
{
    outputDirectory_ = outputDir;
}

void AssetCompiler::setDebugMode(bool enable)
{
    debugMode_ = enable;
}

void AssetCompiler::setOptimizationsEnabled(bool enable)
{
    optimizationsEnabled_ = enable;
}

void AssetCompiler::clearDiagnostics()
{
    errors_.clear();
    warnings_.clear();
}

const std::vector<CompilationError> &AssetCompiler::getErrors() const
{
    return errors_;
}

const std::vector<CompilationError> &AssetCompiler::getWarnings() const
{
    return warnings_;
}

uint32_t AssetCompiler::getOrCreateAssetId(const std::string &assetName)
{
    auto it = assetIdMap_.find(assetName);
    if (it != assetIdMap_.end())
    {
        return it->second;
    }

    uint32_t newId = nextAssetId_++;
    assetIdMap_[assetName] = newId;
    return newId;
}

void AssetCompiler::addError(const std::string &file, int line, const std::string &message)
{
    CompilationError error;
    error.file = file;
    error.line = line;
    error.message = message;
    error.severity = "error";
    errors_.push_back(error);
}

void AssetCompiler::addWarning(const std::string &file, int line, const std::string &message)
{
    CompilationError warning;
    warning.file = file;
    warning.line = line;
    warning.message = message;
    warning.severity = "warning";
    warnings_.push_back(warning);
}
