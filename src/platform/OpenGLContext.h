#ifndef OPENGL_CONTEXT_H
#define OPENGL_CONTEXT_H

#include <windows.h>
#include <gl/GL.h>

/**
 * @brief Manages OpenGL context creation and management for Windows
 */
class OpenGLContext
{
public:
    OpenGLContext();
    ~OpenGLContext();

    bool Initialize(HWND hwnd);
    void SwapBuffers();
    void MakeCurrent();
    void Cleanup();

    bool IsInitialized() const { return initialized; }

private:
    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;
    bool initialized;

    bool SetupPixelFormat();
};

#endif
