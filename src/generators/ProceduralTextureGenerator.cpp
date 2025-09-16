#include "ProceduralTextureGenerator.h"
#include <cmath>
#include <algorithm>
#include <random>
#include <sstream>
#include "../debug.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace ProceduralTexture
{

    // ============================================================================
    // Color Implementation
    // ============================================================================

    Color Color::lerp(const Color &a, const Color &b, float t)
    {
        t = std::clamp(t, 0.0f, 1.0f);
        return Color(
            static_cast<uint8_t>(a.r + t * (b.r - a.r)),
            static_cast<uint8_t>(a.g + t * (b.g - a.g)),
            static_cast<uint8_t>(a.b + t * (b.b - a.b)),
            static_cast<uint8_t>(a.a + t * (b.a - a.a)));
    }

    Color Color::fromFloat(float r, float g, float b, float a)
    {
        return Color(
            static_cast<uint8_t>(std::clamp(r * 255.0f, 0.0f, 255.0f)),
            static_cast<uint8_t>(std::clamp(g * 255.0f, 0.0f, 255.0f)),
            static_cast<uint8_t>(std::clamp(b * 255.0f, 0.0f, 255.0f)),
            static_cast<uint8_t>(std::clamp(a * 255.0f, 0.0f, 255.0f)));
    }

    Color Color::fromHSV(float h, float s, float v, float a)
    {
        h = std::fmod(h, 360.0f);
        if (h < 0)
            h += 360.0f;
        s = std::clamp(s, 0.0f, 1.0f);
        v = std::clamp(v, 0.0f, 1.0f);

        float c = v * s;
        float x = c * (1.0f - std::abs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
        float m = v - c;

        float r, g, b;
        if (h < 60)
        {
            r = c;
            g = x;
            b = 0;
        }
        else if (h < 120)
        {
            r = x;
            g = c;
            b = 0;
        }
        else if (h < 180)
        {
            r = 0;
            g = c;
            b = x;
        }
        else if (h < 240)
        {
            r = 0;
            g = x;
            b = c;
        }
        else if (h < 300)
        {
            r = x;
            g = 0;
            b = c;
        }
        else
        {
            r = c;
            g = 0;
            b = x;
        }

        return fromFloat(r + m, g + m, b + m, a);
    }

    // ============================================================================
    // TextureData Implementation
    // ============================================================================

    TextureData::TextureData(uint32_t w, uint32_t h, const std::string &fmt)
        : width(w), height(h), format(fmt)
    {
        channels = (fmt == "RGB") ? 3 : 4;
        pixels.resize(width * height);
    }

    Color &TextureData::getPixel(uint32_t x, uint32_t y)
    {
        return pixels[y * width + x];
    }

    const Color &TextureData::getPixel(uint32_t x, uint32_t y) const
    {
        return pixels[y * width + x];
    }

    void TextureData::setPixel(uint32_t x, uint32_t y, const Color &color)
    {
        if (x < width && y < height)
        {
            pixels[y * width + x] = color;
        }
    }

    void TextureData::clear(const Color &color)
    {
        std::fill(pixels.begin(), pixels.end(), color);
    }

    void TextureData::resize(uint32_t newWidth, uint32_t newHeight)
    {
        width = newWidth;
        height = newHeight;
        pixels.resize(width * height);
    }

    std::vector<uint8_t> TextureData::getRawData() const
    {
        std::vector<uint8_t> data;
        data.reserve(pixels.size() * channels);

        for (const auto &pixel : pixels)
        {
            data.push_back(pixel.r);
            data.push_back(pixel.g);
            data.push_back(pixel.b);
            if (channels == 4)
            {
                data.push_back(pixel.a);
            }
        }

        return data;
    }

    // ============================================================================
    // Main Generation Methods
    // ============================================================================

    TextureData ProceduralTextureGenerator::generateTexture(const TextureParams &params)
    {
        DEBUG_LOG("Generating texture of type " + std::to_string(static_cast<int>(params.type)) + " with size " + std::to_string(params.width) + "x" + std::to_string(params.height));
        switch (params.type)
        {
        case TextureParams::Type::Noise:
            return generateNoiseTexture(params);
        case TextureParams::Type::Gradient:
            return generateGradientTexture(params);
        case TextureParams::Type::Pattern:
            return generatePatternTexture(params);
        case TextureParams::Type::Composite:
            return generateCompositeTexture(params);
        default:
            return TextureData(params.width, params.height);
        }
    }

    TextureData ProceduralTextureGenerator::generateFromParameters(const std::string &type,
                                                                   const std::map<std::string, std::string> &parameters)
    {
        DEBUG_LOG("Generating texture from parameters with type '" + type + "'");
        TextureParams params;
        params.type = parseTextureType(type);

        // Parse common parameters
        auto it = parameters.find("width");
        if (it != parameters.end())
        {
            params.width = static_cast<uint32_t>(std::stoi(it->second));
        }

        it = parameters.find("height");
        if (it != parameters.end())
        {
            params.height = static_cast<uint32_t>(std::stoi(it->second));
        }

        it = parameters.find("name");
        if (it != parameters.end())
        {
            params.name = it->second;
        }

        // Parse type-specific parameters
        switch (params.type)
        {
        case TextureParams::Type::Noise:
            params.noise = parseNoiseParameters(parameters);
            break;
        case TextureParams::Type::Gradient:
            params.gradient = parseGradientParameters(parameters);
            break;
        case TextureParams::Type::Pattern:
            params.pattern = parsePatternParameters(parameters);
            break;
        default:
            break;
        }

        return generateTexture(params);
    }

    // ============================================================================
    // Specific Generators
    // ============================================================================

    TextureData ProceduralTextureGenerator::generateNoise(const NoiseParams &params, uint32_t width, uint32_t height)
    {
        DEBUG_LOG("Generating noise texture with size " + std::to_string(width) + "x" + std::to_string(height));
        TextureData texture(width, height);

        for (uint32_t y = 0; y < height; ++y)
        {
            for (uint32_t x = 0; x < width; ++x)
            {
                float fx = static_cast<float>(x) / width;
                float fy = static_cast<float>(y) / height;

                float noise = 0.0f;
                switch (params.type)
                {
                case NoiseParams::Type::Perlin:
                    noise = fractalNoise(fx * params.frequency, fy * params.frequency, params);
                    break;
                case NoiseParams::Type::Simplex:
                    noise = simplexNoise(fx * params.frequency, fy * params.frequency, params.seed);
                    break;
                case NoiseParams::Type::Fractal:
                    noise = fractalNoise(fx * params.frequency, fy * params.frequency, params);
                    break;
                case NoiseParams::Type::Cellular:
                    noise = cellularNoise(fx * params.frequency, fy * params.frequency, params);
                    break;
                case NoiseParams::Type::Voronoi:
                    noise = voronoiNoise(fx * params.frequency, fy * params.frequency, params);
                    break;
                case NoiseParams::Type::White:
                {
                    std::mt19937 rng(params.seed + x * 1000 + y);
                    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
                    noise = dist(rng);
                }
                break;
                }

                noise = std::clamp(noise, 0.0f, 1.0f);
                uint8_t value = static_cast<uint8_t>(noise * 255);
                texture.setPixel(x, y, Color(value, value, value, 255));
            }
        }

        return texture;
    }

    TextureData ProceduralTextureGenerator::generateGradient(const GradientParams &params, uint32_t width, uint32_t height)
    {
        DEBUG_LOG("Generating gradient texture with size " + std::to_string(width) + "x" + std::to_string(height));
        TextureData texture(width, height);

        for (uint32_t y = 0; y < height; ++y)
        {
            for (uint32_t x = 0; x < width; ++x)
            {
                float fx = static_cast<float>(x) / width;
                float fy = static_cast<float>(y) / height;

                float t = calculateGradientPosition(params, fx, fy);
                if (params.repeat)
                {
                    t = std::fmod(t, 1.0f);
                    if (t < 0)
                        t += 1.0f;
                }
                else
                {
                    t = std::clamp(t, 0.0f, 1.0f);
                }

                Color color = evaluateGradient(params, t);
                texture.setPixel(x, y, color);
            }
        }

        return texture;
    }

    TextureData ProceduralTextureGenerator::generatePattern(const PatternParams &params, uint32_t width, uint32_t height)
    {
        DEBUG_LOG("Generating pattern texture with size " + std::to_string(width) + "x" + std::to_string(height));
        TextureData texture(width, height);

        for (uint32_t y = 0; y < height; ++y)
        {
            for (uint32_t x = 0; x < width; ++x)
            {
                float fx = static_cast<float>(x) / width;
                float fy = static_cast<float>(y) / height;

                Color color;
                switch (params.type)
                {
                case PatternParams::Type::Checkerboard:
                    color = evaluateCheckerboard(params, fx, fy);
                    break;
                case PatternParams::Type::Stripes:
                    color = evaluateStripes(params, fx, fy);
                    break;
                case PatternParams::Type::Dots:
                    color = evaluateDots(params, fx, fy);
                    break;
                case PatternParams::Type::Grid:
                    color = evaluateGrid(params, fx, fy);
                    break;
                case PatternParams::Type::Spiral:
                    color = evaluateSpiral(params, fx, fy);
                    break;
                case PatternParams::Type::Waves:
                    color = evaluateWaves(params, fx, fy);
                    break;
                }

                texture.setPixel(x, y, color);
            }
        }

        return texture;
    }

    // ============================================================================
    // Noise Implementation
    // ============================================================================

    float ProceduralTextureGenerator::perlinNoise(float x, float y, uint32_t seed)
    {
        int X = static_cast<int>(std::floor(x)) & 255;
        int Y = static_cast<int>(std::floor(y)) & 255;

        x -= std::floor(x);
        y -= std::floor(y);

        float u = fade(x);
        float v = fade(y);

        uint32_t A = hash(X, Y, seed);
        uint32_t B = hash(X + 1, Y, seed);
        uint32_t C = hash(X, Y + 1, seed);
        uint32_t D = hash(X + 1, Y + 1, seed);

        return lerp(v,
                    lerp(u, grad(A, x, y), grad(B, x - 1, y)),
                    lerp(u, grad(C, x, y - 1), grad(D, x - 1, y - 1)));
    }

    float ProceduralTextureGenerator::simplexNoise(float x, float y, uint32_t seed)
    {
        // Simplified simplex noise implementation
        const float F2 = 0.5f * (std::sqrt(3.0f) - 1.0f);
        const float G2 = (3.0f - std::sqrt(3.0f)) / 6.0f;

        float s = (x + y) * F2;
        int i = static_cast<int>(std::floor(x + s));
        int j = static_cast<int>(std::floor(y + s));

        float t = (i + j) * G2;
        float X0 = i - t;
        float Y0 = j - t;
        float x0 = x - X0;
        float y0 = y - Y0;

        int i1, j1;
        if (x0 > y0)
        {
            i1 = 1;
            j1 = 0;
        }
        else
        {
            i1 = 0;
            j1 = 1;
        }

        float x1 = x0 - i1 + G2;
        float y1 = y0 - j1 + G2;
        float x2 = x0 - 1.0f + 2.0f * G2;
        float y2 = y0 - 1.0f + 2.0f * G2;

        uint32_t gi0 = hash(i, j, seed) % 12;
        uint32_t gi1 = hash(i + i1, j + j1, seed) % 12;
        uint32_t gi2 = hash(i + 1, j + 1, seed) % 12;

        float n0 = 0.0f, n1 = 0.0f, n2 = 0.0f;

        float t0 = 0.5f - x0 * x0 - y0 * y0;
        if (t0 >= 0)
        {
            t0 *= t0;
            n0 = t0 * t0 * grad(gi0, x0, y0);
        }

        float t1 = 0.5f - x1 * x1 - y1 * y1;
        if (t1 >= 0)
        {
            t1 *= t1;
            n1 = t1 * t1 * grad(gi1, x1, y1);
        }

        float t2 = 0.5f - x2 * x2 - y2 * y2;
        if (t2 >= 0)
        {
            t2 *= t2;
            n2 = t2 * t2 * grad(gi2, x2, y2);
        }

        return 70.0f * (n0 + n1 + n2);
    }

    float ProceduralTextureGenerator::fractalNoise(float x, float y, const NoiseParams &params)
    {
        float total = 0.0f;
        float frequency = params.frequency;
        float amplitude = params.amplitude;
        float maxValue = 0.0f;

        for (uint32_t i = 0; i < params.octaves; ++i)
        {
            total += perlinNoise(x * frequency, y * frequency, params.seed + i) * amplitude;
            maxValue += amplitude;
            amplitude *= params.persistence;
            frequency *= params.lacunarity;
        }

        return total / maxValue;
    }

    float ProceduralTextureGenerator::cellularNoise(float x, float y, const NoiseParams &params)
    {
        // Simple cellular automata implementation
        int gridSize = static_cast<int>(params.frequency);
        int gx = static_cast<int>(x * gridSize);
        int gy = static_cast<int>(y * gridSize);

        std::mt19937 rng(params.seed);
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);

        // Initial random state
        bool alive = (hash(gx, gy, params.seed) % 100) < (params.threshold * 100);

        // Simple neighbor check for cellular pattern
        int neighbors = 0;
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                    continue;
                if ((hash(gx + dx, gy + dy, params.seed) % 100) < (params.threshold * 100))
                {
                    neighbors++;
                }
            }
        }

        // Conway's Game of Life rules (simplified)
        if (alive)
        {
            return (neighbors == 2 || neighbors == 3) ? 1.0f : 0.0f;
        }
        else
        {
            return (neighbors == 3) ? 1.0f : 0.0f;
        }
    }

    float ProceduralTextureGenerator::voronoiNoise(float x, float y, const NoiseParams &params)
    {
        float minDist = 1.0f;

        // Sample multiple cells
        for (int gx = -1; gx <= 1; ++gx)
        {
            for (int gy = -1; gy <= 1; ++gy)
            {
                int cellX = static_cast<int>(x * params.points) + gx;
                int cellY = static_cast<int>(y * params.points) + gy;

                // Generate random point in cell
                std::mt19937 rng(hash(cellX, cellY, params.seed));
                std::uniform_real_distribution<float> dist(0.0f, 1.0f);

                float pointX = (cellX + dist(rng) * params.jitter) / params.points;
                float pointY = (cellY + dist(rng) * params.jitter) / params.points;

                float dx = x - pointX;
                float dy = y - pointY;
                float distance = std::sqrt(dx * dx + dy * dy);

                minDist = std::min(minDist, distance);
            }
        }

        return std::clamp(minDist, 0.0f, 1.0f);
    }

    // ============================================================================
    // Helper Method Implementations
    // ============================================================================

    float ProceduralTextureGenerator::fade(float t)
    {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    float ProceduralTextureGenerator::lerp(float t, float a, float b)
    {
        return a + t * (b - a);
    }

    float ProceduralTextureGenerator::grad(uint32_t hash, float x, float y)
    {
        uint32_t h = hash & 15;
        float u = h < 8 ? x : y;
        float v = h < 4 ? y : (h == 12 || h == 14 ? x : 0);
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }

    uint32_t ProceduralTextureGenerator::hash(uint32_t x, uint32_t y, uint32_t seed)
    {
        uint32_t h = seed;
        h ^= x + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= y + 0x9e3779b9 + (h << 6) + (h >> 2);
        return h;
    }

    // ============================================================================
    // Pattern Evaluation Methods
    // ============================================================================

    Color ProceduralTextureGenerator::evaluateCheckerboard(const PatternParams &params, float x, float y)
    {
        int checkX = static_cast<int>(x * params.frequency);
        int checkY = static_cast<int>(y * params.frequency);
        return ((checkX + checkY) % 2 == 0) ? params.color1 : params.color2;
    }

    Color ProceduralTextureGenerator::evaluateStripes(const PatternParams &params, float x, float y)
    {
        float value = std::sin(x * params.frequency * 2.0f * M_PI + params.phase);
        return (value > 0) ? params.color1 : params.color2;
    }

    Color ProceduralTextureGenerator::evaluateDots(const PatternParams &params, float x, float y)
    {
        float fx = std::fmod(x * params.frequency, 1.0f);
        float fy = std::fmod(y * params.frequency, 1.0f);
        float dist = std::sqrt((fx - 0.5f) * (fx - 0.5f) + (fy - 0.5f) * (fy - 0.5f));
        return (dist < params.thickness * 0.5f) ? params.color1 : params.color2;
    }

    Color ProceduralTextureGenerator::evaluateGrid(const PatternParams &params, float x, float y)
    {
        float fx = std::fmod(x * params.frequency, 1.0f);
        float fy = std::fmod(y * params.frequency, 1.0f);
        bool isLine = (fx < params.thickness) || (fy < params.thickness);
        return isLine ? params.color1 : params.color2;
    }

    Color ProceduralTextureGenerator::evaluateSpiral(const PatternParams &params, float x, float y)
    {
        float dx = x - 0.5f;
        float dy = y - 0.5f;
        float angle = std::atan2(dy, dx);
        float radius = std::sqrt(dx * dx + dy * dy);

        float spiralValue = std::sin(angle * params.frequency + radius * params.amplitude * 20.0f + params.phase);
        return (spiralValue > 0) ? params.color1 : params.color2;
    }

    Color ProceduralTextureGenerator::evaluateWaves(const PatternParams &params, float x, float y)
    {
        float wave1 = std::sin(x * params.frequency * 2.0f * M_PI + params.phase);
        float wave2 = std::sin(y * params.frequency * 2.0f * M_PI + params.phase);
        float combined = (wave1 + wave2) * 0.5f * params.amplitude;

        float t = (combined + 1.0f) * 0.5f;
        return Color::lerp(params.color2, params.color1, t);
    }

    // ============================================================================
    // Internal Generation Methods
    // ============================================================================

    TextureData ProceduralTextureGenerator::generateNoiseTexture(const TextureParams &params)
    {
        DEBUG_LOG("Generating noise texture with name '" + params.name + "'");
        auto texture = generateNoise(params.noise, params.width, params.height);
        texture.name = params.name;
        applyPostProcessing(texture, params);
        return texture;
    }

    TextureData ProceduralTextureGenerator::generateGradientTexture(const TextureParams &params)
    {
        DEBUG_LOG("Generating gradient texture with name '" + params.name + "'");
        auto texture = generateGradient(params.gradient, params.width, params.height);
        texture.name = params.name;
        applyPostProcessing(texture, params);
        return texture;
    }

    TextureData ProceduralTextureGenerator::generatePatternTexture(const TextureParams &params)
    {
        DEBUG_LOG("Generating pattern texture with name '" + params.name + "'");
        auto texture = generatePattern(params.pattern, params.width, params.height);
        texture.name = params.name;
        applyPostProcessing(texture, params);
        return texture;
    }

    TextureData ProceduralTextureGenerator::generateCompositeTexture(const TextureParams &params)
    {
        if (params.layers.empty())
        {
            return TextureData(params.width, params.height);
        }

        std::vector<TextureData> layerTextures;
        layerTextures.reserve(params.layers.size());

        for (const auto &layer : params.layers)
        {
            layerTextures.push_back(generateTexture(layer));
        }

        auto texture = generateComposite(layerTextures, params.blendModes, params.opacities);
        texture.name = params.name;
        applyPostProcessing(texture, params);
        return texture;
    }

    // ============================================================================
    // Parsing Methods
    // ============================================================================

    TextureParams::Type ProceduralTextureGenerator::parseTextureType(const std::string &typeStr)
    {
        if (typeStr == "noise")
            return TextureParams::Type::Noise;
        if (typeStr == "gradient")
            return TextureParams::Type::Gradient;
        if (typeStr == "pattern")
            return TextureParams::Type::Pattern;
        if (typeStr == "composite")
            return TextureParams::Type::Composite;
        return TextureParams::Type::Noise;
    }

    NoiseParams::Type ProceduralTextureGenerator::parseNoiseType(const std::string &typeStr)
    {
        if (typeStr == "perlin")
            return NoiseParams::Type::Perlin;
        if (typeStr == "simplex")
            return NoiseParams::Type::Simplex;
        if (typeStr == "fractal")
            return NoiseParams::Type::Fractal;
        if (typeStr == "cellular")
            return NoiseParams::Type::Cellular;
        if (typeStr == "voronoi")
            return NoiseParams::Type::Voronoi;
        if (typeStr == "white")
            return NoiseParams::Type::White;
        return NoiseParams::Type::Perlin;
    }

    // Implementation of remaining parsing and processing methods would continue...

    // ============================================================================
    // Missing Method Implementations (Stub implementations for build completion)
    // ============================================================================

    void ProceduralTextureGenerator::applyPostProcessing(TextureData &texture, const TextureParams &params)
    {
        // Stub implementation - basic post-processing
        if (params.invert)
        {
            for (auto &pixel : texture.pixels)
            {
                pixel.r = 255 - pixel.r;
                pixel.g = 255 - pixel.g;
                pixel.b = 255 - pixel.b;
            }
        }
        // Additional post-processing would be implemented here
    }

    TextureData ProceduralTextureGenerator::generateComposite(const std::vector<TextureData> &layers,
                                                              const std::vector<TextureParams::BlendMode> &blendModes,
                                                              const std::vector<float> &opacities)
    {
        if (layers.empty())
        {
            return TextureData{};
        }

        // Start with the first layer
        TextureData result = layers[0];

        // Blend additional layers (stub implementation)
        for (size_t i = 1; i < layers.size(); ++i)
        {
            // Simple additive blending for stub
            const auto &layer = layers[i];
            float opacity = (i < opacities.size()) ? opacities[i] : 1.0f;

            for (size_t j = 0; j < result.pixels.size() && j < layer.pixels.size(); ++j)
            {
                result.pixels[j].r = static_cast<uint8_t>(
                    std::min(255.0f, result.pixels[j].r + layer.pixels[j].r * opacity));
                result.pixels[j].g = static_cast<uint8_t>(
                    std::min(255.0f, result.pixels[j].g + layer.pixels[j].g * opacity));
                result.pixels[j].b = static_cast<uint8_t>(
                    std::min(255.0f, result.pixels[j].b + layer.pixels[j].b * opacity));
            }
        }

        return result;
    }

    NoiseParams ProceduralTextureGenerator::parseNoiseParameters(const std::map<std::string, std::string> &parameters)
    {
        NoiseParams params;

        // Parse basic noise parameters (stub implementation)
        auto it = parameters.find("type");
        if (it != parameters.end())
        {
            params.type = parseNoiseType(it->second);
        }

        it = parameters.find("frequency");
        if (it != parameters.end())
        {
            params.frequency = std::stof(it->second);
        }

        it = parameters.find("amplitude");
        if (it != parameters.end())
        {
            params.amplitude = std::stof(it->second);
        }

        return params;
    }

    GradientParams ProceduralTextureGenerator::parseGradientParameters(const std::map<std::string, std::string> &parameters)
    {
        GradientParams params;

        // Parse gradient parameters (stub implementation)
        auto it = parameters.find("type");
        if (it != parameters.end())
        {
            if (it->second == "linear")
                params.type = GradientParams::Type::Linear;
            else if (it->second == "radial")
                params.type = GradientParams::Type::Radial;
            else if (it->second == "angular")
                params.type = GradientParams::Type::Angular;
            else if (it->second == "diamond")
                params.type = GradientParams::Type::Diamond;
        }

        return params;
    }

    PatternParams ProceduralTextureGenerator::parsePatternParameters(const std::map<std::string, std::string> &parameters)
    {
        PatternParams params;

        // Parse pattern parameters (stub implementation)
        auto it = parameters.find("type");
        if (it != parameters.end())
        {
            if (it->second == "checkerboard")
                params.type = PatternParams::Type::Checkerboard;
            else if (it->second == "stripes")
                params.type = PatternParams::Type::Stripes;
            else if (it->second == "dots")
                params.type = PatternParams::Type::Dots;
            else if (it->second == "grid")
                params.type = PatternParams::Type::Grid;
        }

        it = parameters.find("frequency");
        if (it != parameters.end())
        {
            params.frequency = static_cast<uint32_t>(std::stoi(it->second));
        }

        return params;
    }

    float ProceduralTextureGenerator::calculateGradientPosition(const GradientParams &params, float x, float y)
    {
        // Stub implementation for gradient position calculation
        switch (params.type)
        {
        case GradientParams::Type::Linear:
            return x;
        case GradientParams::Type::Radial:
            return std::sqrt(x * x + y * y);
        case GradientParams::Type::Angular:
            return std::atan2(y, x);
        case GradientParams::Type::Diamond:
            return std::abs(x) + std::abs(y);
        default:
            return x;
        }
    }

    Color ProceduralTextureGenerator::evaluateGradient(const GradientParams &params, float position)
    {
        // Stub implementation for gradient evaluation
        if (params.colors.empty())
        {
            return Color(128, 128, 128, 255); // Default gray
        }

        if (params.colors.size() == 1)
        {
            return params.colors[0];
        }

        // Simple linear interpolation between first and last colors
        return Color::lerp(params.colors[0], params.colors.back(), position);
    }
    // This represents the core functionality of the texture generator

} // namespace ProceduralTexture

