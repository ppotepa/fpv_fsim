#include "DebugOverlayBehavior.h"
#include "../debug.h"
#include "../core/EventBus.h"
#include "../core/World.h"
#include <iostream>
#include <mmsystem.h>

// Static members
DebugOverlayBehavior* DebugOverlayBehavior::instance = nullptr;
bool DebugOverlayBehavior::keyHandlerRegistered = false;

void DebugOverlayBehavior::initialize(Entity& entity, const Assets::BehaviorParams& params) {
    // Store instance for static key handling
    instance = this;
    
    // Get parameters from package.xml
    toggleKey = params.getString("toggleKey", "F9");
    fontAsset = params.getString("fontAsset", "DebugFont");
    soundAsset = params.getString("soundAsset", "DebugToggleSound");
    backgroundAsset = params.getString("backgroundAsset", "DebugPanelBackground");
    
    // Load debug font
    loadDebugFont();
    
    DEBUG_LOG("✅ Debug overlay initialized (Press " + toggleKey + " to toggle)");
}

void DebugOverlayBehavior::update(float deltaTime) {
    if (!debugModeEnabled) return;
    
    // Only update the scene info periodically to avoid performance impact
    lastInfoUpdateTime += deltaTime;
    if (lastInfoUpdateTime >= INFO_UPDATE_INTERVAL) {
        gatherSceneInfo();
        lastInfoUpdateTime = 0.0f;
    }
}

void DebugOverlayBehavior::render() {
    if (!debugModeEnabled) return;
    
    // Save GL state
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    // Get window dimensions
    RECT rect;
    HDC hdc = wglGetCurrentDC();
    GetClientRect(WindowFromDC(hdc), &rect);
    glOrtho(0, rect.right, rect.bottom, 0, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // Render debug info
    renderDebugInfo();
    
    // Restore GL state
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void DebugOverlayBehavior::cleanup() {
    cleanupDebugFont();
    instance = nullptr;
}

void DebugOverlayBehavior::toggleDebugMode() {
    debugModeEnabled = !debugModeEnabled;
    
    // Play sound effect
    playToggleSound();
    
    if (debugModeEnabled) {
        DEBUG_LOG("🔍 Debug mode enabled");
    } else {
        DEBUG_LOG("🔍 Debug mode disabled");
    }
    
    if (debugModeEnabled) {
        gatherSceneInfo();
    }
}

void DebugOverlayBehavior::gatherSceneInfo() {
    sceneEntities.clear();
    
    // For now, add static info about the core package scene
    EntityDebugInfo cubeInfo;
    cubeInfo.name = "Red Test Cube";
    cubeInfo.type = "3D Object";
    cubeInfo.properties["Position"] = "(0, 0, 0)";
    cubeInfo.properties["Scale"] = "(1, 1, 1)";
    cubeInfo.properties["Material"] = "RedCubeMaterial";
    cubeInfo.properties["Mesh"] = "CubeMesh";
    cubeInfo.properties["Behavior"] = "SpinBehavior";
    sceneEntities.push_back(cubeInfo);
    
    EntityDebugInfo debugInfo;
    debugInfo.name = "Debug Overlay";
    debugInfo.type = "System";
    debugInfo.properties["Position"] = "(0, 0, -1)";
    debugInfo.properties["Behavior"] = "DebugOverlayBehavior";
    debugInfo.properties["Toggle Key"] = toggleKey;
    sceneEntities.push_back(debugInfo);
}

void DebugOverlayBehavior::renderDebugInfo() {
    // Disable depth testing for overlay
    glDisable(GL_DEPTH_TEST);
    
    // Semi-transparent background for debug panel
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(10, 10);
        glVertex2f(400, 10);
        glVertex2f(400, 500);
        glVertex2f(10, 500);
    glEnd();
    
    // Set text color to yellow for visibility
    glColor3f(1.0f, 1.0f, 0.0f);
    
    // Render title
    renderDebugText(20, 30, "=== DEBUG MODE (F9 to toggle) ===");
    
    int y = 70;
    renderDebugText(20, y, "CORE PACKAGE SYSTEM:");
    y += 20;
    renderDebugText(30, y, "• Active Package: core");
    y += 15;
    renderDebugText(30, y, "• Scene: DefaultScene");
    y += 15;
    renderDebugText(30, y, "• Assets loaded from package definitions");
    y += 25;
    
    renderDebugText(20, y, "SCENE OBJECTS:");
    y += 20;
    
    for (const auto& entity : sceneEntities) {
        renderDebugText(20, y, "• " + entity.name + " (" + entity.type + ")");
        y += 20;
        
        for (const auto& [key, value] : entity.properties) {
            renderDebugText(30, y, "- " + key + ": " + value);
            y += 15;
        }
        y += 5;
    }
    
    // Render system info
    y += 10;
    renderDebugText(20, y, "DEFAULT ASSETS:");
    y += 20;
    renderDebugText(30, y, "- Font: assets/default/default.ttf");
    y += 15;
    renderDebugText(30, y, "- Audio: assets/default/default.wav");
    y += 15;
    renderDebugText(30, y, "- Texture: assets/default/default.png");
    
    // Render controls info
    y += 25;
    renderDebugText(20, y, "CONTROLS:");
    y += 20;
    renderDebugText(30, y, toggleKey + " - Toggle debug");
    y += 15;
    renderDebugText(30, y, "ESC - Exit");
    
    // Restore states
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

bool DebugOverlayBehavior::loadDebugFont() {
    HDC hdc = wglGetCurrentDC();
    if (!hdc) return false;
    
    // Create font
    debugFont = CreateFont(
        14,                        // Height
        0,                         // Width
        0,                         // Escapement
        0,                         // Orientation
        FW_NORMAL,                 // Weight
        FALSE,                     // Italic
        FALSE,                     // Underline
        FALSE,                     // StrikeOut
        ANSI_CHARSET,              // CharSet
        OUT_TT_PRECIS,             // OutputPrecision
        CLIP_DEFAULT_PRECIS,       // ClipPrecision
        ANTIALIASED_QUALITY,       // Quality
        FF_DONTCARE | DEFAULT_PITCH, // PitchAndFamily
        "Arial"                    // Facename
    );
    
    if (!debugFont) {
        DEBUG_LOG("⚠️  Failed to create debug font, using system font");
        return false;
    }
    
    // Create display lists for font rendering
    fontDisplayLists = glGenLists(256);
    if (!fontDisplayLists) {
        DEBUG_LOG("⚠️  Failed to create font display lists");
        return false;
    }
    
    // Select font into device context
    HFONT oldFont = (HFONT)SelectObject(hdc, debugFont);
    
    // Build display lists for ASCII characters
    wglUseFontBitmaps(hdc, 0, 256, fontDisplayLists);
    
    // Restore previous font
    SelectObject(hdc, oldFont);
    
    DEBUG_LOG("✅ Debug font loaded successfully");
    return true;
}

void DebugOverlayBehavior::renderDebugText(float x, float y, const std::string& text) {
    if (!fontDisplayLists) return;
    
    // Position text
    glRasterPos2f(x, y);
    
    // Render each character using display lists
    glPushAttrib(GL_LIST_BIT);
    glListBase(fontDisplayLists);
    glCallLists(text.length(), GL_UNSIGNED_BYTE, text.c_str());
    glPopAttrib();
}

void DebugOverlayBehavior::cleanupDebugFont() {
    if (fontDisplayLists) {
        glDeleteLists(fontDisplayLists, 256);
        fontDisplayLists = 0;
    }
    
    if (debugFont) {
        DeleteObject(debugFont);
        debugFont = NULL;
    }
}

void DebugOverlayBehavior::playToggleSound() {
    // Play default audio file asynchronously
    std::string audioPath = "assets\\default\\default.wav";
    
    // Use Windows PlaySound API to play the default audio
    if (!PlaySoundA(audioPath.c_str(), NULL, SND_FILENAME | SND_ASYNC)) {
        // If file doesn't exist, play system sound
        PlaySoundA("SystemDefault", NULL, SND_ALIAS | SND_ASYNC);
        DEBUG_LOG("🔊 Debug sound (system default)");
    } else {
        DEBUG_LOG("🔊 Debug sound (default.wav)");
    }
}

// Static key handler
void DebugOverlayBehavior::handleKeyPress(int key) {
    if (instance && key == VK_F9) {
        instance->toggleDebugMode();
    }
}
