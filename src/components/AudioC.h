#pragma once
#include "../core/IComponent.h"
#include <string>

/**
 * @file AudioC.h
 * @brief Component for entities that produce sound.
 *
 * The AudioC component defines the audio properties of an entity,
 * including sound assets, volume, and playback controls.
 * Entities with this component can emit sounds in the simulation.
 */

/**
 * @struct AudioC
 * @brief Component that defines audio properties for an entity.
 *
 * This component inherits from IComponent and provides the necessary
 * information for audio systems to play sounds for the entity.
 * It references sound assets by ID and controls volume and looping.
 */
struct AudioC : public IComponent
{
    /** @brief ID of the sound asset to play */
    std::string soundId;

    /** @brief Volume level (0.0 = silent, 1.0 = full volume) */
    float volume;

    /** @brief Whether the sound should loop continuously */
    bool loop;

    /** @brief Whether the sound is currently playing */
    bool isPlaying;

    /**
     * @brief Construct a new AudioC component.
     *
     * @param sound ID of the sound asset (empty string for no sound)
     * @param vol Volume level (default: 1.0)
     * @param l Whether the sound should loop (default: false)
     */
    AudioC(std::string sound = "",
           float vol = 1.0f,
           bool l = false)
        : soundId(sound), volume(vol), loop(l), isPlaying(false) {}
};

