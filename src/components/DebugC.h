#pragma once
#include "../core/IComponent.h"
#include <unordered_map>
#include <string>

/**
 * @file DebugC.h
 * @brief Component for entities that require debug visualization or information.
 *
 * The DebugC component provides debugging capabilities for entities,
 * including debug names, visualization options, and debug data storage.
 * This component is typically used during development and debugging phases.
 */

/**
 * @struct DebugC
 * @brief Component that provides debugging information and visualization for an entity.
 *
 * This component inherits from IComponent and adds debugging capabilities
 * such as entity naming, debug rendering options, and custom debug data.
 * Debug components are usually processed by debug rendering systems.
 */
struct DebugC : public IComponent
{
    /** @brief Human-readable name for the entity (for debugging purposes) */
    std::string debugName;

    /** @brief Whether to show debug visualization for this entity */
    bool showDebugInfo;

    /** @brief Whether to render debug bounding boxes or wireframes */
    bool showBoundingBox;

    /** @brief Custom debug data as key-value pairs */
    std::unordered_map<std::string, std::string> debugData;

    /**
     * @brief Construct a new DebugC component.
     *
     * @param name Debug name for the entity (default: empty string)
     * @param showInfo Whether to show debug information (default: false)
     * @param showBox Whether to show bounding box (default: false)
     */
    DebugC(std::string name = "", bool showInfo = false, bool showBox = false)
        : debugName(name), showDebugInfo(showInfo), showBoundingBox(showBox) {}
};

