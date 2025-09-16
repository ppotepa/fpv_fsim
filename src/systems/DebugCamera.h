#ifndef DEBUGCAMERA_H
#define DEBUGCAMERA_H

#include "core/ISystem.h"
#include "core/EventBus.h"
#include "events/InputEvents.h"
#include "systems/InputSystem.h"
#include "config/InputConfig.h"
#include <windows.h>
#include <cmath>

/**
 * @class DebugCamera
 * @brief Debug camera controller for free-look navigation with WASD movement
 *
 * This class handles debug camera movement and rotation controls when debug mode
 * is active. It provides WASD movement and mouse look functionality for developers.
 */
class DebugCamera
{
public:
    struct Vector3
    {
        float x, y, z;
        Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

        Vector3 operator+(const Vector3& other) const {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }

        Vector3 operator-(const Vector3& other) const {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }

        Vector3 operator*(float scalar) const {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }

        Vector3& operator+=(const Vector3& other) {
            x += other.x; y += other.y; z += other.z;
            return *this;
        }

        Vector3& operator-=(const Vector3& other) {
            x -= other.x; y -= other.y; z -= other.z;
            return *this;
        }

        float length() const {
            return sqrt(x * x + y * y + z * z);
        }

        Vector3 normalized() const {
            float len = length();
            if (len > 0.001f) {
                return Vector3(x / len, y / len, z / len);
            }
            return Vector3(0, 0, 0);
        }

        Vector3 cross(const Vector3& other) const {
            return Vector3(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
            );
        }
    };

    struct CameraState
    {
        Vector3 position;
        Vector3 direction;
        Vector3 up;
        float pitch;  // Rotation around X axis
        float yaw;    // Rotation around Y axis
        float speed;  // Movement speed
        float sensitivity; // Mouse sensitivity
    };

private:
    EventBus& eventBus_;
    CameraState state_;
    bool debugModeActive_;
    
    // Mouse tracking for look controls
    POINT lastMousePos_;
    bool mouseInitialized_;

    // Camera transition for smooth movement
    Vector3 originalPosition_;
    Vector3 originalDirection_;
    Vector3 originalUp_;
    Vector3 debugTargetPosition_;
    Vector3 debugTargetDirection_;
    float transitionTime_;
    float transitionDuration_;
    bool isTransitioning_;
    bool transitioningToDebug_;

public:
    /**
     * @brief Construct a new Debug Camera
     * @param eventBus Reference to the event bus for listening to debug mode events
     */
    DebugCamera(EventBus& eventBus);

    /**
     * @brief Update camera based on input (called each frame when debug mode is active)
     * @param deltaTime Time elapsed since last frame
     */
    void update(float deltaTime);

    /**
     * @brief Get current camera state
     * @return Current camera position, direction, and up vectors
     */
    const CameraState& getCameraState() const { return state_; }

    /**
     * @brief Set camera state (used to sync with normal camera when entering debug mode)
     * @param position Camera position
     * @param direction Camera direction  
     * @param up Camera up vector
     */
    void setCameraState(const Vector3& position, const Vector3& direction, const Vector3& up);

    /**
     * @brief Check if debug mode is currently active
     * @return True if debug mode is active
     */
    bool isDebugModeActive() const { return debugModeActive_; }

    /**
     * @brief Check if camera is currently transitioning
     * @return True if camera is transitioning
     */
    bool isTransitioning() const { return isTransitioning_; }

private:
    /**
     * @brief Handle debug mode toggle events
     * @param event Debug mode toggle event
     */
    void onDebugModeToggled(const DebugModeToggled& event);

    /**
     * @brief Process WASD movement input
     * @param deltaTime Time elapsed since last frame
     */
    void processMovementInput(float deltaTime);

    /**
     * @brief Process mouse look input
     * @param deltaTime Time elapsed since last frame
     */
    void processMouseLookInput(float deltaTime);

    /**
     * @brief Update camera direction vectors based on pitch and yaw
     */
    void updateDirectionVectors();

    /**
     * @brief Check if a key is currently pressed
     * @param key Virtual key code
     * @return True if key is pressed
     */
    bool isKeyPressed(int key) const;

    /**
     * @brief Update camera transition interpolation
     * @param deltaTime Time elapsed since last frame
     */
    void updateTransition(float deltaTime);

    /**
     * @brief Linear interpolation between two Vector3 values
     * @param a Start vector
     * @param b End vector
     * @param t Interpolation factor (0.0 to 1.0)
     * @return Interpolated vector
     */
    Vector3 lerp(const Vector3& a, const Vector3& b, float t) const;
};

#endif // DEBUGCAMERA_H
