#pragma once
#include <string>
#include <vector>

namespace Terrain
{

struct NoiseLayer
{
    std::string type;     // "sine", "sine_cosine", "sine_cosine_complex"
    float amplitude;      // Layer amplitude
    float frequency;      // Layer frequency
    float phase;          // Layer phase offset
};

struct TerrainConfig
{
    float noiseAmplitude;           // Global noise amplitude
    float normalizationFactor;     // Global normalization factor
    std::vector<NoiseLayer> noiseLayers;  // Noise layers
};

class TerrainGenerator
{
private:
    TerrainConfig config_;
    bool isConfigLoaded_ = false;

public:
    TerrainGenerator() = default;
    ~TerrainGenerator() = default;

    // Load terrain configuration from package JSON
    bool LoadTerrainConfig(const std::string& packagePath);
    
    // Generate terrain noise for given coordinates
    float GenerateTerrainNoise(float latitude, float longitude) const;
    
    // Check if config is loaded
    bool IsConfigLoaded() const { return isConfigLoaded_; }
};

} // namespace Terrain
