#include "OpenGLContext.h"
#include <iostream>
#include "../debug.h"

OpenGLContext::OpenGLContext()
    : hwnd(nullptr), hdc(nullptr), hglrc(nullptr), initialized(false)
{
}

OpenGLContext::~OpenGLContext()
{
    Cleanup();
}

bool OpenGLContext::Initialize(HWND windowHandle)
{
    hwnd = windowHandle;
    hdc = GetDC(hwnd);

    if (!hdc)
    {
        std::cerr << "Failed to get device context" << std::endl;
        return false;
    }

    if (!SetupPixelFormat())
    {
        std::cerr << "Failed to setup pixel format" << std::endl;
        return false;
    }

    hglrc = wglCreateContext(hdc);
    if (!hglrc)
    {
        std::cerr << "Failed to create OpenGL context" << std::endl;
        return false;
    }

    if (!wglMakeCurrent(hdc, hglrc))
    {
        std::cerr << "Failed to make OpenGL context current" << std::endl;
        return false;
    }

    // Basic OpenGL setup
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set clear color to dark blue
    glClearColor(20.0f / 255.0f, 30.0f / 255.0f, 50.0f / 255.0f, 1.0f);

    initialized = true;
    DEBUG_LOG("OpenGL context initialized successfully");
    DEBUG_LOG("OpenGL Version: " << glGetString(GL_VERSION));
    DEBUG_LOG("OpenGL Vendor: " << glGetString(GL_VENDOR));

    return true;
}

void OpenGLContext::SwapBuffers()
{
    if (hdc)
    {
        ::SwapBuffers(hdc);
    }
}

void OpenGLContext::MakeCurrent()
{
    if (hdc && hglrc)
    {
        wglMakeCurrent(hdc, hglrc);
    }
}

void OpenGLContext::Cleanup()
{
    if (hglrc)
    {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(hglrc);
        hglrc = nullptr;
    }

    if (hdc && hwnd)
    {
        ReleaseDC(hwnd, hdc);
        hdc = nullptr;
    }

    initialized = false;
}

bool OpenGLContext::SetupPixelFormat()
{
    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    if (pixelFormat == 0)
    {
        std::cerr << "Failed to choose pixel format" << std::endl;
        return false;
    }

    if (!SetPixelFormat(hdc, pixelFormat, &pfd))
    {
        std::cerr << "Failed to set pixel format" << std::endl;
        return false;
    }

    return true;
}
