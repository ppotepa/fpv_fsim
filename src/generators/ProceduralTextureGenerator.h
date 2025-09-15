#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <cstdint>
#include <functional>

namespace ProceduralTexture
{

    // ============================================================================
    // Texture Data Structures
    // ============================================================================

    struct Color
    {
        uint8_t r, g, b, a;

        Color() : r(0), g(0), b(0), a(255) {}
        Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
            : r(red), g(green), b(blue), a(alpha) {}

        static Color lerp(const Color &a, const Color &b, float t);
        static Color fromFloat(float r, float g, float b, float a = 1.0f);
        static Color fromHSV(float h, float s, float v, float a = 1.0f);
    };

    struct TextureData
    {
        std::vector<Color> pixels;
        uint32_t width;
        uint32_t height;
        uint32_t channels;  // 3 for RGB, 4 for RGBA
        std::string format; // "RGB", "RGBA", "LUMINANCE", etc.
        std::string name;

        TextureData() : width(0), height(0), channels(4), format("RGBA") {}
        TextureData(uint32_t w, uint32_t h, const std::string &fmt = "RGBA");

        Color &getPixel(uint32_t x, uint32_t y);
        const Color &getPixel(uint32_t x, uint32_t y) const;
        void setPixel(uint32_t x, uint32_t y, const Color &color);

        // Utility methods
        void clear(const Color &color = Color(0, 0, 0, 0));
        void resize(uint32_t newWidth, uint32_t newHeight);
        std::vector<uint8_t> getRawData() const;
    };

    // ============================================================================
    // Noise and Pattern Parameters
    // ============================================================================

    struct NoiseParams
    {
        enum class Type
        {
            Perlin,
            Simplex,
            Fractal,
            Cellular,
            Voronoi,
            White
        };

        Type type = Type::Perlin;
        uint32_t seed = 12345;
        float frequency = 1.0f;
        float amplitude = 1.0f;
        uint32_t octaves = 4;
        float persistence = 0.5f;
        float lacunarity = 2.0f;

        // Cellular automata specific
        uint32_t iterations = 5;
        float threshold = 0.5f;

        // Voronoi specific
        uint32_t points = 16;
        float jitter = 1.0f;
    };

    struct GradientParams
    {
        enum class Type
        {
            Linear,
            Radial,
            Angular,
            Diamond
        };

        Type type = Type::Linear;
        std::vector<Color> colors;
        std::vector<float> stops;             // 0.0 to 1.0
        float angle = 0.0f;                   // For linear gradients (degrees)
        float centerX = 0.5f, centerY = 0.5f; // For radial/angular gradients
        float radius = 0.5f;                  // For radial gradients
        bool repeat = false;
    };

    struct PatternParams
    {
        enum class Type
        {
            Checkerboard,
            Stripes,
            Dots,
            Grid,
            Spiral,
            Waves
        };

        Type type = Type::Checkerboard;
        uint32_t frequency = 8; // Pattern repetitions
        Color color1 = Color(255, 255, 255, 255);
        Color color2 = Color(0, 0, 0, 255);
        float thickness = 0.5f; // Line thickness for stripes/grid
        float amplitude = 1.0f; // Wave amplitude
        float phase = 0.0f;     // Wave phase
    };

    // ============================================================================
    // Texture Generator Parameters
    // ============================================================================

    struct TextureParams
    {
        enum class Type
        {
            Noise,
            Gradient,
            Pattern,
            Composite
        };

        Type type = Type::Noise;
        uint32_t width = 256;
        uint32_t height = 256;
        std::string name = "procedural_texture";

        // Generator-specific parameters
        NoiseParams noise;
        GradientParams gradient;
        PatternParams pattern;

        // Composite blending
        enum class BlendMode
        {
            Replace,
            Add,
            Multiply,
            Overlay,
            Screen,
            Darken,
            Lighten
        };

        std::vector<TextureParams> layers; // For composite textures
        std::vector<BlendMode> blendModes;
        std::vector<float> opacities;

        // Post-processing
        bool normalize = false;
        bool invert = false;
        float brightness = 0.0f; // -1.0 to 1.0
        float contrast = 1.0f;   // 0.0 to 2.0
        float gamma = 1.0f;      // Gamma correction
    };

    // ============================================================================
    // Main Texture Generator Class
    // ============================================================================

    class ProceduralTextureGenerator
    {
    public:
        // Construction and Configuration
        ProceduralTextureGenerator() = default;
        ~ProceduralTextureGenerator() = default;

        // Primary generation methods
        static TextureData generateTexture(const TextureParams &params);
        static TextureData generateFromParameters(const std::string &type,
                                                  const std::map<std::string, std::string> &parameters);

        // Specific generators
        static TextureData generateNoise(const NoiseParams &params, uint32_t width, uint32_t height);
        static TextureData generateGradient(const GradientParams &params, uint32_t width, uint32_t height);
        static TextureData generatePattern(const PatternParams &params, uint32_t width, uint32_t height);
        static TextureData generateComposite(const std::vector<TextureData> &layers,
                                             const std::vector<TextureParams::BlendMode> &blendModes,
                                             const std::vector<float> &opacities);

        // Noise generation methods
        static float perlinNoise(float x, float y, uint32_t seed = 12345);
        static float simplexNoise(float x, float y, uint32_t seed = 12345);
        static float fractalNoise(float x, float y, const NoiseParams &params);
        static float cellularNoise(float x, float y, const NoiseParams &params);
        static float voronoiNoise(float x, float y, const NoiseParams &params);

        // Utility and helper methods
        static TextureParams::Type parseTextureType(const std::string &typeStr);
        static NoiseParams::Type parseNoiseType(const std::string &typeStr);
        static GradientParams::Type parseGradientType(const std::string &typeStr);
        static PatternParams::Type parsePatternType(const std::string &typeStr);
        static TextureParams::BlendMode parseBlendMode(const std::string &modeStr);

        static std::string textureTypeToString(TextureParams::Type type);
        static std::string noiseTypeToString(NoiseParams::Type type);
        static std::string gradientTypeToString(GradientParams::Type type);
        static std::string patternTypeToString(PatternParams::Type type);
        static std::string blendModeToString(TextureParams::BlendMode mode);

        // Parameter validation and estimation
        static bool validateParameters(const TextureParams &params);
        static uint32_t estimateMemoryUsage(const TextureParams &params);
        static uint32_t estimateGenerationTime(const TextureParams &params); // In milliseconds

    private:
        // Internal generation helpers
        static TextureData generateNoiseTexture(const TextureParams &params);
        static TextureData generateGradientTexture(const TextureParams &params);
        static TextureData generatePatternTexture(const TextureParams &params);
        static TextureData generateCompositeTexture(const TextureParams &params);

        // Noise implementation helpers
        static float fade(float t);
        static float lerp(float t, float a, float b);
        static float grad(uint32_t hash, float x, float y);
        static uint32_t hash(uint32_t x, uint32_t y, uint32_t seed);

        // Gradient implementation helpers
        static Color evaluateGradient(const GradientParams &params, float t);
        static float calculateGradientPosition(const GradientParams &params, float x, float y);

        // Pattern implementation helpers
        static Color evaluateCheckerboard(const PatternParams &params, float x, float y);
        static Color evaluateStripes(const PatternParams &params, float x, float y);
        static Color evaluateDots(const PatternParams &params, float x, float y);
        static Color evaluateGrid(const PatternParams &params, float x, float y);
        static Color evaluateSpiral(const PatternParams &params, float x, float y);
        static Color evaluateWaves(const PatternParams &params, float x, float y);

        // Blending and compositing
        static Color blendColors(const Color &base, const Color &overlay,
                                 TextureParams::BlendMode mode, float opacity);
        static Color blendAdd(const Color &a, const Color &b);
        static Color blendMultiply(const Color &a, const Color &b);
        static Color blendOverlay(const Color &a, const Color &b);
        static Color blendScreen(const Color &a, const Color &b);
        static Color blendDarken(const Color &a, const Color &b);
        static Color blendLighten(const Color &a, const Color &b);

        // Post-processing
        static void applyPostProcessing(TextureData &texture, const TextureParams &params);
        static void applyNormalization(TextureData &texture);
        static void applyInversion(TextureData &texture);
        static void applyBrightness(TextureData &texture, float brightness);
        static void applyContrast(TextureData &texture, float contrast);
        static void applyGamma(TextureData &texture, float gamma);

        // XML parameter parsing helpers
        static NoiseParams parseNoiseParameters(const std::map<std::string, std::string> &params);
        static GradientParams parseGradientParameters(const std::map<std::string, std::string> &params);
        static PatternParams parsePatternParameters(const std::map<std::string, std::string> &params);
        static std::vector<Color> parseColorList(const std::string &colorStr);
        static Color parseColor(const std::string &colorStr);

        // Validation helpers
        static bool isValidDimension(uint32_t dimension);
        static bool isValidColorStop(float stop);
        static bool isValidBlendMode(TextureParams::BlendMode mode);
    };

} // namespace ProceduralTexture
