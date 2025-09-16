#ifndef SHADER_COMPILER_H
#define SHADER_COMPILER_H

#include <windows.h>
#include <gl/GL.h>
#include <string>
#include "assets/ShaderAsset.h"

/**
 * @brief Compiles GLSL shaders into OpenGL programs
 */
class ShaderCompiler
{
public:
    ShaderCompiler();
    ~ShaderCompiler();

    /**
     * @brief Compile a shader asset into an OpenGL program
     * @param shaderAsset The shader asset to compile
     * @return true if compilation successful, false otherwise
     */
    bool CompileShader(ShaderAsset &shaderAsset);

    /**
     * @brief Use a compiled shader program
     * @param programId OpenGL program ID to use
     */
    void UseShader(unsigned int programId);

    /**
     * @brief Set uniform values for a shader
     */
    void SetFloat(unsigned int programId, const std::string &name, float value);
    void SetVec3(unsigned int programId, const std::string &name, float x, float y, float z);
    void SetMat4(unsigned int programId, const std::string &name, const float *matrix);

private:
    unsigned int CompileShaderSource(const std::string &source, unsigned int shaderType);
    unsigned int LinkProgram(unsigned int vertexShader, unsigned int fragmentShader);
    bool CheckCompileErrors(unsigned int shader, const std::string &type);
    int GetUniformLocation(unsigned int programId, const std::string &name);
};

#endif

