#pragma once
#include "../core/IComponent.h"

/**
 * @file RenderableC.h
 * @brief Component for entities that can be visually rendered in the scene.
 *
 * The RenderableC component defines the visual properties of an entity,
 * including mesh geometry, material appearance, and visibility state.
 * Entities with this component can be processed by rendering systems.
 */

/**
 * @struct RenderableC
 * @brief Component that defines visual rendering properties for an entity.
 *
 * This component inherits from IComponent and provides the necessary
 * information for rendering systems to display the entity. It references
 * mesh and material assets by ID and controls visibility.
 */
struct RenderableC : public IComponent
{
    /** @brief ID of the mesh asset used for rendering geometry */
    std::string meshId;

    /** @brief ID of the material asset used for surface appearance */
    std::string materialId;

    /** @brief Whether the entity should be rendered (true) or hidden (false) */
    bool isVisible;

    /**
     * @brief Construct a new RenderableC component.
     *
     * @param mesh ID of the mesh asset (empty string for no mesh)
     * @param material ID of the material asset (empty string for no material)
     * @param visible Initial visibility state (default: true)
     */
    RenderableC(std::string mesh = "", std::string material = "", bool visible = true)
        : meshId(mesh), materialId(material), isVisible(visible) {}
};

