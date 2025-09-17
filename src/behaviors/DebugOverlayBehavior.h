#pragma once

#include "../components/EntityBehavior.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <windows.h>
#include <GL/gl.h>

class DebugOverlayBehavior : public Components::EntityBehavior {
public:
    void initialize(Entity& entity, const Assets::BehaviorParams& params) override;
    void update(float deltaTime) override;
    void cleanup() override;
    
    // Custom render method (not from base class)
    void render();
    
private:
    // Debug state
    bool debugModeEnabled = false;
    std::string toggleKey = "F9";
    
    // Asset references
    std::string fontAsset;
    std::string soundAsset;
    std::string backgroundAsset;
    
    // Font rendering
    HFONT debugFont = NULL;
    GLuint fontDisplayLists = 0;
    
    // Cached scene data for display
    struct EntityDebugInfo {
        std::string name;
        std::string type;
        std::unordered_map<std::string, std::string> properties;
    };
    std::vector<EntityDebugInfo> sceneEntities;
    
    // Last update time to prevent gathering info every frame
    float lastInfoUpdateTime = 0.0f;
    const float INFO_UPDATE_INTERVAL = 0.5f; // Update debug info twice per second
    
    // Methods
    void toggleDebugMode();
    void gatherSceneInfo();
    void renderDebugInfo();
    bool loadDebugFont();
    void renderDebugText(float x, float y, const std::string& text);
    void cleanupDebugFont();
    void playToggleSound();
    
    // Static key handling
    static DebugOverlayBehavior* instance;
    static bool keyHandlerRegistered;
public:
    static void handleKeyPress(int key);
};
