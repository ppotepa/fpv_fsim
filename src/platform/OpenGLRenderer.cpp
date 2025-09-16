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
    std::cout << "OpenGLRenderer: Initializing..." << std::endl;

    // Basic OpenGL setup
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Get OpenGL version info for debugging
    const char *version = (const char *)glGetString(GL_VERSION);
    const char *vendor = (const char *)glGetString(GL_VENDOR);
    const char *renderer = (const char *)glGetString(GL_RENDERER);

    std::cout << "OpenGL Version: " << (version ? version : "Unknown") << std::endl;
    std::cout << "OpenGL Vendor: " << (vendor ? vendor : "Unknown") << std::endl;
    std::cout << "OpenGL Renderer: " << (renderer ? renderer : "Unknown") << std::endl;

    // Set up clear color to help identify when rendering is occurring
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // Dark blue-ish background

    // Load default shader
    if (!LoadDefaultShader())
    {
        std::cout << "Warning: Failed to load default shader, using fixed pipeline" << std::endl;
    }

    // Enable wire frame rendering for debugging visibility
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    initialized = true;
    std::cout << "OpenGLRenderer: Initialization complete" << std::endl;
    return true;
}

void OpenGLRenderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::BeginFrame()
{
    Clear();

    // Debug info - helps see if OpenGL is actually working
    static int frameCount = 0;
    if (frameCount++ % 300 == 0)
    {
        std::cout << "OpenGLRenderer: Beginning frame #" << frameCount << std::endl;
        std::cout << "OpenGL context active: " << (glGetError() == GL_NO_ERROR ? "YES" : "NO") << std::endl;
    }

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

    // Debug output to track camera position
    static int frameCount = 0;
    if (frameCount++ % 300 == 0)
    { // Log every 300 frames
        std::cout << "OpenGLRenderer: Camera position (" << eyeX << ", " << eyeY << ", " << eyeZ << ")" << std::endl;
        std::cout << "OpenGLRenderer: Camera target (" << centerX << ", " << centerY << ", " << centerZ << ")" << std::endl;
    }

    // Properly set up a look-at matrix
    // Calculate forward vector (direction from eye to center)
    float forwardX = centerX - eyeX;
    float forwardY = centerY - eyeY;
    float forwardZ = centerZ - eyeZ;

    // Normalize forward vector
    float forwardLength = sqrt(forwardX * forwardX + forwardY * forwardY + forwardZ * forwardZ);
    if (forwardLength < 0.0001f)
    {
        // Prevent division by zero
        forwardX = 0.0f;
        forwardY = 0.0f;
        forwardZ = -1.0f; // Default forward is -Z in OpenGL
    }
    else
    {
        forwardX /= forwardLength;
        forwardY /= forwardLength;
        forwardZ /= forwardLength;
    }

    // Manual implementation of "look at" functionality since we don't have gluLookAt
    // Step 1: Calculate the right vector as the cross product of up and forward
    float rightX = upY * forwardZ - upZ * forwardY;
    float rightY = upZ * forwardX - upX * forwardZ;
    float rightZ = upX * forwardY - upY * forwardX;

    // Normalize the right vector
    float rightLength = sqrt(rightX * rightX + rightY * rightY + rightZ * rightZ);
    if (rightLength > 0.0001f)
    {
        rightX /= rightLength;
        rightY /= rightLength;
        rightZ /= rightLength;
    }

    // Step 2: Recalculate the up vector to make sure it's perpendicular to both forward and right
    float newUpX = forwardY * rightZ - forwardZ * rightY;
    float newUpY = forwardZ * rightX - forwardX * rightZ;
    float newUpZ = forwardX * rightY - forwardY * rightX;

    // Step 3: Create a view matrix using these vectors
    float viewMatrix[16] = {
        rightX, newUpX, -forwardX, 0.0f,
        rightY, newUpY, -forwardY, 0.0f,
        rightZ, newUpZ, -forwardZ, 0.0f,
        -(rightX * eyeX + rightY * eyeY + rightZ * eyeZ),
        -(newUpX * eyeX + newUpY * eyeY + newUpZ * eyeZ),
        forwardX * eyeX + forwardY * eyeY + forwardZ * eyeZ,
        1.0f};

    // Apply the view matrix
    glMultMatrixf(viewMatrix);
}

void OpenGLRenderer::DrawSphere(float x, float y, float z, float radius, float r, float g, float b)
{
    // Debug output to verify the renderer is being called
    static int sphereCount = 0;
    if (sphereCount++ % 100 == 0)
    { // Only print every 100th sphere to avoid spam
        std::cout << "OpenGLRenderer: Drawing sphere at (" << x << ", " << y << ", " << z
                  << ") radius=" << radius << " color=(" << r << ", " << g << ", " << b << ")" << std::endl;
    }

    glPushMatrix();
    glTranslatef(x, y, z);

    glColor3f(r, g, b);

    // Draw a simple wireframe sphere using basic OpenGL
    DrawWireSphere(radius, 16);

    // Also draw a solid sphere with lower alpha for better visibility
    glEnable(GL_BLEND);
    glColor4f(r, g, b, 0.3f);
    DrawSolidSphere(radius * 0.95f, 12);

    glPopMatrix();
}

void OpenGLRenderer::DrawText2D(float x, float y, const std::string &text, float r, float g, float b)
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

void OpenGLRenderer::DrawSolidSphere(float radius, int segments)
{
    // Draw solid sphere with triangles
    for (int j = 0; j < segments; j++)
    {
        float phi1 = j * 3.14159f / segments;
        float phi2 = (j + 1) * 3.14159f / segments;

        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= segments; i++)
        {
            float theta = i * 2.0f * 3.14159f / segments;

            float x1 = radius * sin(phi1) * cos(theta);
            float y1 = radius * cos(phi1);
            float z1 = radius * sin(phi1) * sin(theta);

            float x2 = radius * sin(phi2) * cos(theta);
            float y2 = radius * cos(phi2);
            float z2 = radius * sin(phi2) * sin(theta);

            // First vertex
            glVertex3f(x1, y1, z1);

            // Second vertex
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }
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
