#pragma once
#include <string>
#include <map>
#include <memory>

/**
 * @file ShaderAsset.h
 * @brief Asset structure for shader resources.
 *
 * Defines the basic shader asset structure for loading and managing
 * shaders in the asset system. Supports vertex and fragment shader
 * sources with parameter definitions.
 */

/**
 * @struct ShaderAsset
 * @brief Asset data structure for shader resources.
 *
 * Contains shader source code, compilation state, and parameter definitions
 * for use in the rendering pipeline.
 */
struct ShaderAsset
{
    /** @brief Shader asset identifier */
    std::string id;

    /** @brief Path to the shader file */
    std::string path;

    /** @brief Vertex shader source code */
    std::string vertexSource;

    /** @brief Fragment shader source code */
    std::string fragmentSource;

    /** @brief Shader parameters and their default values */
    std::map<std::string, std::string> parameters;

    /** @brief Whether the shader has been compiled successfully */
    bool isCompiled;

    /** @brief Compilation error messages (if any) */
    std::string compilationErrors;

    /** @brief OpenGL shader program ID (if compiled) */
    unsigned int programId;

    /**
     * @brief Construct a new ShaderAsset.
     */
    ShaderAsset()
        : isCompiled(false), programId(0)
    {
    }

    /**
     * @brief Get parameter value with fallback.
     *
     * @param paramName Name of the parameter
     * @param defaultValue Default value if parameter not found
     * @return Parameter value or default
     */
    std::string getParameter(const std::string &paramName, const std::string &defaultValue = "") const
    {
        auto it = parameters.find(paramName);
        return (it != parameters.end()) ? it->second : defaultValue;
    }

    /**
     * @brief Check if parameter exists.
     *
     * @param paramName Name of the parameter to check
     * @return True if parameter exists
     */
    bool hasParameter(const std::string &paramName) const
    {
        return parameters.find(paramName) != parameters.end();
    }
};

/**
 * @class BasicShaderGenerator
 * @brief Generates basic shader source code for common materials.
 *
 * Provides factory methods for creating simple shaders including
 * the cel-shading shader used in the voxel busy indicator scene.
 */
class BasicShaderGenerator
{
public:
    /**
     * @brief Generate a cel-shading vertex shader.
     *
     * @param bands Number of cel-shading bands
     * @return Vertex shader source code
     */
    static std::string generateCelVertexShader(int bands = 4);

    /**
     * @brief Generate a cel-shading fragment shader.
     *
     * @param bands Number of cel-shading bands
     * @param outlineEnabled Whether outline rendering is enabled
     * @return Fragment shader source code
     */
    static std::string generateCelFragmentShader(int bands = 4, bool outlineEnabled = false);

    /**
     * @brief Generate a simple unlit vertex shader.
     *
     * @return Basic vertex shader source code
     */
    static std::string generateUnlitVertexShader();

    /**
     * @brief Generate a simple unlit fragment shader.
     *
     * @return Basic fragment shader source code
     */
    static std::string generateUnlitFragmentShader();

    /**
     * @brief Create a complete cel-shading shader asset.
     *
     * @param id Asset identifier
     * @param bands Number of cel-shading bands
     * @param outlineEnabled Whether outlines are enabled
     * @return Complete shader asset
     */
    static std::unique_ptr<ShaderAsset> createCelBandShader(const std::string &id,
                                                            int bands = 4,
                                                            bool outlineEnabled = false);

private:
    static std::string getCommonUniforms();
    static std::string getCommonAttributes();
};

