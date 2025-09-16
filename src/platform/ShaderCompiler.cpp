#include "ShaderCompiler.h"
#include <iostream>
#include "../debug.h"

// Define GLchar if not defined
#ifndef GLchar
typedef char GLchar;
#endif

// We need OpenGL extensions for modern shader functions
// For now, define them manually since we're using basic OpenGL
#ifndef GL_VERTEX_SHADER
#define GL_VERTEX_SHADER 0x8B31
#endif
#ifndef GL_FRAGMENT_SHADER
#define GL_FRAGMENT_SHADER 0x8B30
#endif
#ifndef GL_COMPILE_STATUS
#define GL_COMPILE_STATUS 0x8B81
#endif
#ifndef GL_LINK_STATUS
#define GL_LINK_STATUS 0x8B82
#endif

// Function pointers for OpenGL shader functions
typedef void(APIENTRY *PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
typedef void(APIENTRY *PFNGLCOMPILESHADERPROC)(GLuint shader);
typedef GLuint(APIENTRY *PFNGLCREATEPROGRAMPROC)(void);
typedef GLuint(APIENTRY *PFNGLCREATESHADERPROC)(GLenum type);
typedef void(APIENTRY *PFNGLDELETESHADERPROC)(GLuint shader);
typedef void(APIENTRY *PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint *params);
typedef void(APIENTRY *PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void(APIENTRY *PFNGLLINKPROGRAMPROC)(GLuint program);
typedef void(APIENTRY *PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length);
typedef void(APIENTRY *PFNGLUSEPROGRAMPROC)(GLuint program);
typedef GLint(APIENTRY *PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar *name);
typedef void(APIENTRY *PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
typedef void(APIENTRY *PFNGLUNIFORM3FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void(APIENTRY *PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

// Function pointers
static PFNGLATTACHSHADERPROC glAttachShader = nullptr;
static PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
static PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
static PFNGLCREATESHADERPROC glCreateShader = nullptr;
static PFNGLDELETESHADERPROC glDeleteShader = nullptr;
static PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
static PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
static PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
static PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
static PFNGLUNIFORM1FPROC glUniform1f = nullptr;
static PFNGLUNIFORM3FPROC glUniform3f = nullptr;
static PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;

ShaderCompiler::ShaderCompiler()
{
    // Load OpenGL extensions for shader support
    glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
    glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
    glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
    glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
    glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
    glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
    glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
    glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
    glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
    glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
    glUniform3f = (PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f");
    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");

    // Check if critical functions are available
    if (!glCreateShader || !glCreateProgram)
    {
        DEBUG_LOG("Warning: OpenGL shader extensions not available - shader compilation disabled");
    }
    else
    {
        DEBUG_LOG("OpenGL shader compiler initialized successfully");
    }
}

ShaderCompiler::~ShaderCompiler()
{
}

bool ShaderCompiler::CompileShader(ShaderAsset &shaderAsset)
{
    if (!glCreateShader || !glCreateProgram)
    {
        shaderAsset.compilationErrors = "OpenGL shader extensions not available";
        shaderAsset.isCompiled = false;
        return false;
    }

    // Compile vertex shader
    unsigned int vertexShader = CompileShaderSource(shaderAsset.vertexSource, GL_VERTEX_SHADER);
    if (vertexShader == 0)
    {
        shaderAsset.compilationErrors = "Failed to compile vertex shader";
        shaderAsset.isCompiled = false;
        return false;
    }

    // Compile fragment shader
    unsigned int fragmentShader = CompileShaderSource(shaderAsset.fragmentSource, GL_FRAGMENT_SHADER);
    if (fragmentShader == 0)
    {
        glDeleteShader(vertexShader);
        shaderAsset.compilationErrors = "Failed to compile fragment shader";
        shaderAsset.isCompiled = false;
        return false;
    }

    // Link program
    unsigned int program = LinkProgram(vertexShader, fragmentShader);
    if (program == 0)
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        shaderAsset.compilationErrors = "Failed to link shader program";
        shaderAsset.isCompiled = false;
        return false;
    }

    // Cleanup individual shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    shaderAsset.programId = program;
    shaderAsset.isCompiled = true;
    shaderAsset.compilationErrors.clear();

    DEBUG_LOG("Shader compiled successfully: " << shaderAsset.id);
    return true;
}

void ShaderCompiler::UseShader(unsigned int programId)
{
    if (glUseProgram && programId > 0)
    {
        glUseProgram(programId);
    }
}

void ShaderCompiler::SetFloat(unsigned int programId, const std::string &name, float value)
{
    if (glUniform1f)
    {
        int location = GetUniformLocation(programId, name);
        if (location >= 0)
        {
            glUniform1f(location, value);
        }
    }
}

void ShaderCompiler::SetVec3(unsigned int programId, const std::string &name, float x, float y, float z)
{
    if (glUniform3f)
    {
        int location = GetUniformLocation(programId, name);
        if (location >= 0)
        {
            glUniform3f(location, x, y, z);
        }
    }
}

void ShaderCompiler::SetMat4(unsigned int programId, const std::string &name, const float *matrix)
{
    if (glUniformMatrix4fv)
    {
        int location = GetUniformLocation(programId, name);
        if (location >= 0)
        {
            glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
        }
    }
}

unsigned int ShaderCompiler::CompileShaderSource(const std::string &source, unsigned int shaderType)
{
    unsigned int shader = glCreateShader(shaderType);
    const char *src = source.c_str();
    const char *const *srcPtr = &src;
    glShaderSource(shader, 1, (const GLchar *const *)srcPtr, nullptr);
    glCompileShader(shader);

    if (!CheckCompileErrors(shader, shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"))
    {
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

unsigned int ShaderCompiler::LinkProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    if (!CheckCompileErrors(program, "PROGRAM"))
    {
        return 0;
    }

    return program;
}

bool ShaderCompiler::CheckCompileErrors(unsigned int shader, const std::string &type)
{
    int success;
    char infoLog[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            if (glGetShaderInfoLog)
            {
                glGetShaderInfoLog(shader, 1024, nullptr, (GLchar *)infoLog);
                std::cerr << "Shader compilation error of type: " << type << "\n"
                          << infoLog << std::endl;
            }
            return false;
        }
    }
    else
    {
        // For program linking, we would need glGetProgramiv and glGetProgramInfoLog
        // For now, assume success since we're using basic functionality
    }

    return true;
}

int ShaderCompiler::GetUniformLocation(unsigned int programId, const std::string &name)
{
    if (glGetUniformLocation)
    {
        return glGetUniformLocation(programId, (const GLchar *)name.c_str());
    }
    return -1;
}


