#include "TerrainGenerator.h"
#include "../debug.h"
#include "../platform/NlohmannJsonParser.h"
#include <cmath>

namespace Terrain
{

bool TerrainGenerator::LoadTerrainConfig(const std::string& packagePath)
{
    try
    {
        DEBUG_LOG("Loading terrain config from package: " + packagePath);
        
        // Use NlohmannJsonParser to load the JSON file
        NlohmannJsonParser jsonParser;
        if (!jsonParser.loadFile(packagePath))
        {
            DEBUG_LOG("Failed to load package file: " + packagePath);
            return false;
        }
        
        const auto& rootJson = jsonParser.getRootJson();
        if (!rootJson.contains("terrainGeneration"))
        {
            DEBUG_LOG("No terrainGeneration section found in package");
            return false;
        }
        
        const auto& terrainConfig = rootJson["terrainGeneration"];
        
        // Parse mesh configurations
        if (!terrainConfig.contains("meshes") || !terrainConfig["meshes"].is_array())
        {
            DEBUG_LOG("No meshes array found in terrain config");
            return false;
        }
        
        for (const auto& mesh : terrainConfig["meshes"])
        {
            if (mesh.contains("name") && mesh["name"] == "earthLandSphere")
            {
                // Load noise layers
                config_.noiseAmplitude = terrainConfig["noiseAmplitude"];
                config_.normalizationFactor = terrainConfig["normalizationFactor"];
                
                // Clear existing layers
                config_.noiseLayers.clear();
                
                if (terrainConfig.contains("noiseLayers") && terrainConfig["noiseLayers"].is_array())
                {
                    for (const auto& layerJson : terrainConfig["noiseLayers"])
                    {
                        NoiseLayer layer;
                        layer.type = layerJson["type"];
                        layer.amplitude = layerJson["amplitude"];
                        layer.frequency = layerJson["frequency"];
                        layer.phase = layerJson["phase"];
                        
                        config_.noiseLayers.push_back(layer);
                    }
                }
                
                isConfigLoaded_ = true;
                DEBUG_LOG("Loaded terrain config with " + std::to_string(config_.noiseLayers.size()) + " noise layers");
                return true;
            }
        }
        
        DEBUG_LOG("earthLandSphere mesh config not found");
        return false;
    }
    catch (const std::exception& e)
    {
        DEBUG_LOG("Exception loading terrain config: " + std::string(e.what()));
        return false;
    }
}

float TerrainGenerator::GenerateTerrainNoise(float latitude, float longitude) const
{
    if (!isConfigLoaded_)
    {
        DEBUG_LOG("Terrain config not loaded");
        return 0.0f;
    }
    
    float totalNoise = 0.0f;
    
    for (const auto& layer : config_.noiseLayers)
    {
        float layerNoise = 0.0f;
        
        if (layer.type == "sine")
        {
            layerNoise = std::sin(latitude * layer.frequency + layer.phase) * layer.amplitude;
        }
        else if (layer.type == "sine_cosine")
        {
            layerNoise = (std::sin(latitude * layer.frequency + layer.phase) + 
                         std::cos(longitude * layer.frequency + layer.phase)) * layer.amplitude;
        }
        else if (layer.type == "sine_cosine_complex")
        {
            layerNoise = (std::sin(latitude * layer.frequency * 2.0f + layer.phase) * 
                         std::cos(longitude * layer.frequency * 1.5f + layer.phase)) * layer.amplitude;
        }
        
        totalNoise += layerNoise;
    }
    
    return totalNoise * config_.noiseAmplitude * config_.normalizationFactor;
}

} // namespace Terrain
