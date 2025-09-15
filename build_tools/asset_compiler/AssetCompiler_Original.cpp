#include "AssetCompiler.h"
#ifdef HAVE_PUGIXML
#include "platform/IXmlParser.h"
#include "platform/PugiXmlParser.h"
#include "generators/VoxelMeshGenerator.h"
#include "generators/ProceduralTextureGenerator.h"
#endif
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

AssetCompiler::AssetCompiler()
#ifdef HAVE_PUGIXML
    : xmlParser_(std::make_unique<PugiXmlParser>())
    , meshGenerator_(std::make_unique<VoxelMeshGenerator>())
    , textureGenerator_(std::make_unique<ProceduralTextureGenerator>())
    , debugMode_(false)
#else
    : debugMode_(false)
#endif
    , optimizationsEnabled_(true)
    , nextAssetId_(1)
{
    outputDirectory_ = "runtime/data/packs";
}

AssetCompiler::~AssetCompiler() = default;

bool AssetCompiler::processAssetConfiguration(const std::string& configFile)
{
    clearDiagnostics();
    currentFile_ = configFile;

    if (!std::filesystem::exists(configFile))
    {
        addError(configFile, 0, "Configuration file does not exist");
        return false;
    }

#ifdef HAVE_PUGIXML
    if (!xmlParser_->loadFile(configFile))
    {
        addError(configFile, 0, "Failed to parse XML: " + xmlParser_->getLastError());
        return false;
    }

    // Validate against schema if available
    std::string schemaPath = "assets/schemas/asset.xsd";
    if (std::filesystem::exists(schemaPath))
    {
        if (!xmlParser_->validateAgainstSchema(schemaPath))
        {
            addError(configFile, 0, "Schema validation failed: " + xmlParser_->getLastError());
            return false;
        }
    }

    // Parse the asset package
    return parseAssetPackage();
#else
    // Simplified mode without XML parsing
    std::cout << "Asset Compiler Demo Mode (XML parsing disabled)" << std::endl;
    std::cout << "Processing: " << configFile << std::endl;
    
    // Create output directory
    std::filesystem::create_directories(outputDirectory_);
    
    // Write a demo pack file
    std::string outputPath = outputDirectory_ + "/demo_pack.bin";
    std::ofstream output(outputPath, std::ios::binary);
    if (output.is_open())
    {
        std::string content = "FPVSIM_PACK_DEMO\n";
        output.write(content.c_str(), content.length());
        output.close();
        std::cout << "Created demo pack: " << outputPath << std::endl;
        return true;
    }
    
    addError(configFile, 0, "Failed to create output pack");
    return false;
#endif
}
    {
        if (!validateAgainstSchema(configFile, schemaPath))
        {
            addError(configFile, 0, "Schema validation failed");
            return false;
        }
    }

    // Extract package name from file path
    std::filesystem::path packagePath(configFile);
    std::string packageName = packagePath.parent_path().filename().string();
    
    return processPackage(configFile, packageName);
}

bool AssetCompiler::validateAgainstSchema(const std::string& xmlFile, const std::string& schemaFile)
{
    std::vector<std::string> validationErrors;
    bool isValid = xmlParser_->validateAgainstSchema(schemaFile, validationErrors);
    
    for (const auto& error : validationErrors)
    {
        addError(xmlFile, 0, "Schema validation: " + error);
    }
    
    return isValid;
}

std::vector<CompilationError> AssetCompiler::getErrors() const
{
    return errors_;
}

std::vector<CompilationError> AssetCompiler::getWarnings() const
{
    return warnings_;
}

void AssetCompiler::setOutputDirectory(const std::string& outputDir)
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

bool AssetCompiler::processPackage(const std::string& packageFile, const std::string& packageName)
{
    std::cout << "Processing package: " << packageName << " from " << packageFile << std::endl;

    bool success = true;

    // Process different asset types
    if (xmlParser_->hasElement("textures"))
    {
        success &= processTextures("textures");
    }

    if (xmlParser_->hasElement("meshes"))
    {
        success &= processMeshes("meshes");
    }

    if (xmlParser_->hasElement("materials"))
    {
        success &= processMaterials("materials");
    }

    if (xmlParser_->hasElement("shaders"))
    {
        success &= processShaders("shaders");
    }

    if (xmlParser_->hasElement("scenes"))
    {
        success &= processScenes("scenes");
    }

    if (success && !debugMode_)
    {
        // Write binary pack for release mode
        std::unordered_map<uint32_t, std::vector<uint8_t>> assetData;
        // TODO: Collect all processed asset data
        success &= writeBinaryPack(packageName, assetData);
    }

    return success;
}

bool AssetCompiler::processTextures(const std::string& texturesPath)
{
    std::cout << "Processing textures..." << std::endl;

    auto textureElements = xmlParser_->getElementsWithName("texture", texturesPath);
    
    for (const auto& texturePath : textureElements)
    {
        std::string id = xmlParser_->getElementAttribute(texturePath, "id");
        std::string type = xmlParser_->getElementAttribute(texturePath, "type");
        
        if (id.empty())
        {
            addError(currentFile_, 0, "Texture element missing required 'id' attribute");
            continue;
        }

        // Assign numeric ID
        assetIdMap_[id] = nextAssetId_++;
        
        if (type == "procedural")
        {
            // Extract procedural parameters
            std::unordered_map<std::string, std::string> params;
            
            auto paramElements = xmlParser_->getElementsWithName("param", texturePath);
            for (const auto& paramPath : paramElements)
            {
                std::string name = xmlParser_->getElementAttribute(paramPath, "name");
                std::string value = xmlParser_->getElementText(paramPath);
                if (!name.empty())
                {
                    params[name] = value;
                }
            }
            
            std::string outputPath = outputDirectory_ + "/" + id + ".ktx2";
            if (!generateProceduralTexture(params, outputPath))
            {
                addError(currentFile_, 0, "Failed to generate procedural texture: " + id);
                return false;
            }
        }
        else if (type == "file")
        {
            std::string sourcePath = xmlParser_->getElementText(texturePath + "/source");
            if (sourcePath.empty())
            {
                addError(currentFile_, 0, "File texture missing source path: " + id);
                continue;
            }
            
            // TODO: Process file-based texture (compression, optimization, etc.)
            std::cout << "  Processing file texture: " << id << " from " << sourcePath << std::endl;
        }
    }

    return true;
}

bool AssetCompiler::processMeshes(const std::string& meshesPath)
{
    std::cout << "Processing meshes..." << std::endl;

    auto meshElements = xmlParser_->getElementsWithName("mesh", meshesPath);
    
    for (const auto& meshPath : meshElements)
    {
        std::string id = xmlParser_->getElementAttribute(meshPath, "id");
        std::string type = xmlParser_->getElementAttribute(meshPath, "type");
        
        if (id.empty())
        {
            addError(currentFile_, 0, "Mesh element missing required 'id' attribute");
            continue;
        }

        // Assign numeric ID
        assetIdMap_[id] = nextAssetId_++;
        
        if (type == "procedural")
        {
            // Extract procedural parameters
            std::unordered_map<std::string, std::string> params;
            
            auto paramElements = xmlParser_->getElementsWithName("param", meshPath);
            for (const auto& paramPath : paramElements)
            {
                std::string name = xmlParser_->getElementAttribute(paramPath, "name");
                std::string value = xmlParser_->getElementText(paramPath);
                if (!name.empty())
                {
                    params[name] = value;
                }
            }
            
            std::string outputPath = outputDirectory_ + "/" + id + ".mesh";
            if (!generateProceduralMesh(params, outputPath))
            {
                addError(currentFile_, 0, "Failed to generate procedural mesh: " + id);
                return false;
            }
        }
        else if (type == "file")
        {
            std::string sourcePath = xmlParser_->getElementText(meshPath + "/source");
            if (sourcePath.empty())
            {
                addError(currentFile_, 0, "File mesh missing source path: " + id);
                continue;
            }
            
            // TODO: Process file-based mesh (optimization, LOD generation, etc.)
            std::cout << "  Processing file mesh: " << id << " from " << sourcePath << std::endl;
        }
    }

    return true;
}

bool AssetCompiler::processMaterials(const std::string& materialsPath)
{
    std::cout << "Processing materials..." << std::endl;

    auto materialElements = xmlParser_->getElementsWithName("material", materialsPath);
    
    for (const auto& materialPath : materialElements)
    {
        std::string id = xmlParser_->getElementAttribute(materialPath, "id");
        
        if (id.empty())
        {
            addError(currentFile_, 0, "Material element missing required 'id' attribute");
            continue;
        }

        // Assign numeric ID
        assetIdMap_[id] = nextAssetId_++;
        
        // TODO: Process material properties, shader references, etc.
        std::cout << "  Processing material: " << id << std::endl;
    }

    return true;
}

bool AssetCompiler::processShaders(const std::string& shadersPath)
{
    std::cout << "Processing shaders..." << std::endl;

    auto shaderElements = xmlParser_->getElementsWithName("shader", shadersPath);
    
    for (const auto& shaderPath : shaderElements)
    {
        std::string id = xmlParser_->getElementAttribute(shaderPath, "id");
        
        if (id.empty())
        {
            addError(currentFile_, 0, "Shader element missing required 'id' attribute");
            continue;
        }

        // Assign numeric ID
        assetIdMap_[id] = nextAssetId_++;
        
        // TODO: Compile shaders, generate variants, etc.
        std::cout << "  Processing shader: " << id << std::endl;
    }

    return true;
}

bool AssetCompiler::processScenes(const std::string& scenesPath)
{
    std::cout << "Processing scenes..." << std::endl;

    auto sceneElements = xmlParser_->getElementsWithName("scene", scenesPath);
    
    for (const auto& scenePath : sceneElements)
    {
        std::string id = xmlParser_->getElementAttribute(scenePath, "id");
        
        if (id.empty())
        {
            addError(currentFile_, 0, "Scene element missing required 'id' attribute");
            continue;
        }

        // Assign numeric ID
        assetIdMap_[id] = nextAssetId_++;
        
        // TODO: Process scene graph, optimize, resolve asset references
        std::cout << "  Processing scene: " << id << std::endl;
    }

    return true;
}

bool AssetCompiler::generateProceduralTexture(const std::unordered_map<std::string, std::string>& params, const std::string& outputPath)
{
    // Extract texture type and parameters
    auto typeIt = params.find("type");
    if (typeIt == params.end())
    {
        addError(currentFile_, 0, "Procedural texture missing 'type' parameter");
        return false;
    }

    // TODO: Use ProceduralTextureGenerator to create texture
    std::cout << "    Generating procedural texture of type: " << typeIt->second << std::endl;
    
    // Create output directory if it doesn't exist
    std::filesystem::path outputDir = std::filesystem::path(outputPath).parent_path();
    std::filesystem::create_directories(outputDir);
    
    // TODO: Actually generate and save the texture
    return true;
}

bool AssetCompiler::generateProceduralMesh(const std::unordered_map<std::string, std::string>& params, const std::string& outputPath)
{
    // Extract mesh type and parameters
    auto typeIt = params.find("type");
    if (typeIt == params.end())
    {
        addError(currentFile_, 0, "Procedural mesh missing 'type' parameter");
        return false;
    }

    // TODO: Use VoxelMeshGenerator to create mesh
    std::cout << "    Generating procedural mesh of type: " << typeIt->second << std::endl;
    
    // Create output directory if it doesn't exist
    std::filesystem::path outputDir = std::filesystem::path(outputPath).parent_path();
    std::filesystem::create_directories(outputDir);
    
    // TODO: Actually generate and save the mesh
    return true;
}

bool AssetCompiler::writeBinaryPack(const std::string& packageName, const std::unordered_map<uint32_t, std::vector<uint8_t>>& assets)
{
    std::string packPath = outputDirectory_ + "/" + packageName + ".pak";
    
    std::ofstream packFile(packPath, std::ios::binary);
    if (!packFile.is_open())
    {
        addError(currentFile_, 0, "Failed to create binary pack file: " + packPath);
        return false;
    }

    // TODO: Write binary pack format:
    // - Header with magic number, version, asset count
    // - Asset directory with ID, offset, size for each asset
    // - Asset data sections
    
    std::cout << "Writing binary pack: " << packPath << " with " << assets.size() << " assets" << std::endl;
    
    return true;
}

void AssetCompiler::addError(const std::string& file, int line, const std::string& message)
{
    errors_.push_back({file, line, message, "error"});
}

void AssetCompiler::addWarning(const std::string& file, int line, const std::string& message)
{
    warnings_.push_back({file, line, message, "warning"});
}
