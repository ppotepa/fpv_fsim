#include "OpenGLRenderer.h"
#include <iostream>
#include <cmath>

OpenGLRenderer::OpenGLRenderer()
    : initialized(false)
{
}

OpenGLRenderer::~OpenGLRenderer()
{
}

bool OpenGLRenderer::Initialize()
{
    // Basic OpenGL setup
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Load default shader
    if (!LoadDefaultShader())
    {
        std::cout << "Warning: Failed to load default shader, using fixed pipeline" << std::endl;
    }
    
    initialized = true;
    return true;
}

void OpenGLRenderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::BeginFrame()
{
    Clear();
    
    // Use default shader if available
    UseDefaultShader();
}

void OpenGLRenderer::EndFrame()
{
    // Frame complete - caller handles buffer swapping
}

void OpenGLRenderer::SetupCamera(float fov, float aspect, float nearPlane, float farPlane)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Simple perspective projection using basic OpenGL functions
    float fH = tan(fov / 360.0f * 3.14159f) * nearPlane;
    float fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, nearPlane, farPlane);
}

void OpenGLRenderer::SetCameraView(float eyeX, float eyeY, float eyeZ, 
                                  float centerX, float centerY, float centerZ,
                                  float upX, float upY, float upZ)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Simple look-at implementation using basic OpenGL functions
    // For now, use a simple translation - can be improved later
    glTranslatef(-eyeX, -eyeY, -eyeZ);
}

void OpenGLRenderer::DrawSphere(float x, float y, float z, float radius, float r, float g, float b)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    
    glColor3f(r, g, b);
    
    // Draw a simple wireframe sphere using basic OpenGL
    DrawWireSphere(radius, 16);
    
    glPopMatrix();
}

void OpenGLRenderer::DrawText2D(float x, float y, const std::string& text, float r, float g, float b)
{
    // For now, skip text rendering in OpenGL - this requires font texture loading
    // which is complex. We'll add this later when implementing proper text rendering
}

void OpenGLRenderer::DrawWireSphere(float radius, int segments)
{
    glBegin(GL_LINES);
    
    // Draw longitude lines
    for (int i = 0; i < segments; i++)
    {
        float theta1 = i * 2.0f * 3.14159f / segments;
        float theta2 = (i + 1) * 2.0f * 3.14159f / segments;
        
        for (int j = 0; j < segments; j++)
        {
            float phi = j * 3.14159f / segments;
            
            float x1 = radius * sin(phi) * cos(theta1);
            float y1 = radius * cos(phi);
            float z1 = radius * sin(phi) * sin(theta1);
            
            float x2 = radius * sin(phi) * cos(theta2);
            float y2 = radius * cos(phi);
            float z2 = radius * sin(phi) * sin(theta2);
            
            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
        }
    }
    
    // Draw latitude lines
    for (int i = 0; i < segments; i++)
    {
        float phi1 = i * 3.14159f / segments;
        float phi2 = (i + 1) * 3.14159f / segments;
        
        for (int j = 0; j < segments; j++)
        {
            float theta = j * 2.0f * 3.14159f / segments;
            
            float x1 = radius * sin(phi1) * cos(theta);
            float y1 = radius * cos(phi1);
            float z1 = radius * sin(phi1) * sin(theta);
            
            float x2 = radius * sin(phi2) * cos(theta);
            float y2 = radius * cos(phi2);
            float z2 = radius * sin(phi2) * sin(theta);
            
            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
        }
    }
    
    glEnd();
}

bool OpenGLRenderer::LoadDefaultShader()
{
    // Create a simple default shader for basic rendering
    defaultShader.id = "default";
    
    // Simple vertex shader that just transforms vertices
    defaultShader.vertexSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}
)";

    // Simple fragment shader that uses a uniform color
    defaultShader.fragmentSource = R"(
#version 330 core
out vec4 FragColor;

uniform vec3 uColor;

void main()
{
    FragColor = vec4(uColor, 1.0);
}
)";

    return shaderCompiler.CompileShader(defaultShader);
}

void OpenGLRenderer::UseDefaultShader()
{
    if (defaultShader.isCompiled)
    {
        shaderCompiler.UseShader(defaultShader.programId);
    }
}
