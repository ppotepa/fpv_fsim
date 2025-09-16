#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <windows.h>
#include <gl/GL.h>
#include <string>
#include <vector>
#include "ShaderCompiler.h"
#include "assets/ShaderAsset.h"

/**
 * @brief Basic OpenGL renderer for entities and primitives
 */
class OpenGLRenderer
{
public:
    OpenGLRenderer();
    ~OpenGLRenderer();

    bool Initialize();
    void Clear();
    void BeginFrame();
    void EndFrame();

    // Shader management
    bool LoadDefaultShader();
    void UseDefaultShader();

    // Simple primitive rendering
    void DrawSphere(float x, float y, float z, float radius, float r, float g, float b);
    void DrawText2D(float x, float y, const std::string& text, float r, float g, float b);
    
    // 3D camera setup
    void SetupCamera(float fov, float aspect, float nearPlane, float farPlane);
    void SetCameraView(float eyeX, float eyeY, float eyeZ, 
                      float centerX, float centerY, float centerZ,
                      float upX, float upY, float upZ);

private:
    bool initialized;
    ShaderCompiler shaderCompiler;
    ShaderAsset defaultShader;
    
    void DrawWireSphere(float radius, int segments);
    void DrawSolidSphere(float radius, int segments);
};

#endif
