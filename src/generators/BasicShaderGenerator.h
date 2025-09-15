#ifndef BASIC_SHADER_GENERATOR_H
#define BASIC_SHADER_GENERATOR_H

#include <string>
#include <map>
#include <vector>

/**
 * @brief Information about a generated shader.
 */
struct ShaderInfo
{
    std::string vertexSource;            /**< GLSL vertex shader source */
    std::string fragmentSource;          /**< GLSL fragment shader source */
    std::string geometrySource;          /**< GLSL geometry shader source (optional) */
    std::vector<std::string> uniforms;   /**< List of uniform variables */
    std::vector<std::string> attributes; /**< List of vertex attributes */
};

/**
 * @brief Generator for basic GLSL shaders from parametric definitions.
 *
 * This generator creates common shader types (basic lighting, PBR, unlit, etc.)
 * from parameter sets, allowing for data-driven shader creation without
 * requiring manual GLSL coding for every material variant.
 */
class BasicShaderGenerator
{
public:
    /**
     * @brief Generate a shader from parameters.
     *
     * @param shaderType Type of shader to generate ("phong", "pbr", "unlit", etc.)
     * @param parameters Map of parameter name to value
     * @return Generated shader information
     */
    static ShaderInfo generateShader(const std::string &shaderType,
                                     const std::map<std::string, std::string> &parameters);

    /**
     * @brief Generate a basic Phong lighting shader.
     *
     * @param parameters Shader parameters (ambient, diffuse, specular colors, etc.)
     * @return Generated Phong shader
     */
    static ShaderInfo generatePhongShader(const std::map<std::string, std::string> &parameters);

    /**
     * @brief Generate a basic PBR (Physically Based Rendering) shader.
     *
     * @param parameters PBR parameters (roughness, metallic, albedo, etc.)
     * @return Generated PBR shader
     */
    static ShaderInfo generatePBRShader(const std::map<std::string, std::string> &parameters);

    /**
     * @brief Generate an unlit shader (no lighting calculations).
     *
     * @param parameters Basic parameters (color, texture, etc.)
     * @return Generated unlit shader
     */
    static ShaderInfo generateUnlitShader(const std::map<std::string, std::string> &parameters);

    /**
     * @brief Generate a debug shader for visualizing normals, UVs, etc.
     *
     * @param parameters Debug visualization parameters
     * @return Generated debug shader
     */
    static ShaderInfo generateDebugShader(const std::map<std::string, std::string> &parameters);

    /**
     * @brief Get a list of supported shader types.
     *
     * @return Vector of shader type names
     */
    static std::vector<std::string> getSupportedShaderTypes();

private:
    /**
     * @brief Generate common vertex shader code.
     *
     * @param includeNormals Whether to include normal calculations
     * @param includeUVs Whether to include UV coordinates
     * @param includeColors Whether to include vertex colors
     * @return Generated vertex shader source
     */
    static std::string generateVertexShader(bool includeNormals = true,
                                            bool includeUVs = true,
                                            bool includeColors = false);

    /**
     * @brief Generate lighting calculation code.
     *
     * @param lightingModel Lighting model to use ("phong", "pbr", etc.)
     * @return GLSL code for lighting calculations
     */
    static std::string generateLightingCode(const std::string &lightingModel);

    /**
     * @brief Generate uniform declarations from parameters.
     *
     * @param parameters Parameter map
     * @return GLSL uniform declarations
     */
    static std::string generateUniforms(const std::map<std::string, std::string> &parameters);

    /**
     * @brief Extract color value from parameter string.
     *
     * @param colorStr Color string in format "r,g,b" or "r,g,b,a"
     * @param defaultColor Default color if parsing fails
     * @return Parsed color values
     */
    static std::vector<float> parseColor(const std::string &colorStr,
                                         const std::vector<float> &defaultColor);
};

#endif // BASIC_SHADER_GENERATOR_H
