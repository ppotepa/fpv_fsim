#pragma once
#include "../core/IComponent.h"

/**
 * Renderable component for entities that can be visually displayed.
 */
struct RenderableC : public IComponent
{
    std::string meshId;     // ID of the mesh asset
    std::string materialId; // ID of the material asset
    bool isVisible;         // Whether the entity should be rendered

    RenderableC(std::string mesh = "", std::string material = "", bool visible = true)
        : meshId(mesh), materialId(material), isVisible(visible) {}
};
