#include "DebugCamera.h"
#include "../debug.h"
#include <cmath>
#include <algorithm>

DebugCamera::DebugCamera(EventBus &eventBus)
    : eventBus_(eventBus), debugModeActive_(false), mouseInitialized_(false),
      transitionTime_(0.0f), transitionDuration_(1.0f), isTransitioning_(false), transitioningToDebug_(false)
{
    // Initialize camera state with default values
    state_.position = Vector3(0.0f, 5.0f, 15.0f);
    state_.direction = Vector3(0.0f, 0.0f, -1.0f);
    state_.up = Vector3(0.0f, 1.0f, 0.0f);
    state_.pitch = 0.0f;
    state_.yaw = -90.0f;       // Start looking forward (negative Z)
    state_.speed = 10.0f;      // Units per second
    state_.sensitivity = 0.1f; // Mouse sensitivity

    // Initialize debug target position (looking at origin from above and behind)
    debugTargetPosition_ = Vector3(10.0f, 10.0f, 10.0f);
    debugTargetDirection_ = (Vector3(0.0f, 0.0f, 0.0f) - debugTargetPosition_).normalized();

    // Subscribe to debug mode events
    eventBus_.subscribe(EventType::DebugModeToggled, [this](const IEvent &event)
                        {
        const auto& debugEvent = static_cast<const DebugModeToggled&>(event);
        onDebugModeToggled(debugEvent); });

    DEBUG_LOG("DebugCamera initialized");
}

void DebugCamera::update(float deltaTime)
{
    // Always update transition if it's active
    if (isTransitioning_)
    {
        updateTransition(deltaTime);
        return; // Don't process input while transitioning
    }

    if (!debugModeActive_)
    {
        return;
    }

    processMovementInput(deltaTime);
    processMouseLookInput(deltaTime);
    updateDirectionVectors();
}

void DebugCamera::setCameraState(const Vector3 &position, const Vector3 &direction, const Vector3 &up)
{
    state_.position = position;
    state_.direction = direction.normalized();
    state_.up = up.normalized();

    // Calculate initial pitch and yaw from direction vector
    state_.yaw = atan2(direction.x, -direction.z) * 180.0f / 3.14159f;
    state_.pitch = asin(direction.y) * 180.0f / 3.14159f;

    DEBUG_LOG("Debug camera state set - Position: (" << position.x << ", " << position.y << ", " << position.z << ")");
}

void DebugCamera::onDebugModeToggled(const DebugModeToggled &event)
{
    if (event.isActive)
    {
        // Store current camera state as original
        originalPosition_ = state_.position;
        originalDirection_ = state_.direction;
        originalUp_ = state_.up;

        // Start transition to debug position
        transitionTime_ = 0.0f;
        isTransitioning_ = true;
        transitioningToDebug_ = true;

        DEBUG_LOG("Debug camera activated - starting transition to origin");
    }
    else
    {
        // Start transition back to original position
        transitionTime_ = 0.0f;
        isTransitioning_ = true;
        transitioningToDebug_ = false;

        DEBUG_LOG("Debug camera deactivated - starting transition back to original");
    }

    debugModeActive_ = event.isActive;
}

void DebugCamera::processMovementInput(float deltaTime)
{
    Vector3 movement(0.0f, 0.0f, 0.0f);
    float speed = state_.speed * deltaTime;

    // WASD movement
    if (isKeyPressed('W'))
    {
        movement += state_.direction * speed;
    }
    if (isKeyPressed('S'))
    {
        movement -= state_.direction * speed;
    }
    if (isKeyPressed('A'))
    {
        Vector3 right = state_.direction.cross(state_.up).normalized();
        movement -= right * speed;
    }
    if (isKeyPressed('D'))
    {
        Vector3 right = state_.direction.cross(state_.up).normalized();
        movement += right * speed;
    }

    // Optional: Q/E for up/down movement
    if (isKeyPressed('Q'))
    {
        movement.y -= speed;
    }
    if (isKeyPressed('E'))
    {
        movement.y += speed;
    }

    state_.position += movement;
}

void DebugCamera::processMouseLookInput(float deltaTime)
{
    POINT currentMousePos;
    if (!GetCursorPos(&currentMousePos))
    {
        return;
    }

    if (!mouseInitialized_)
    {
        lastMousePos_ = currentMousePos;
        mouseInitialized_ = true;
        return;
    }

    // Calculate mouse delta
    float deltaX = static_cast<float>(currentMousePos.x - lastMousePos_.x);
    float deltaY = static_cast<float>(currentMousePos.y - lastMousePos_.y);

    // Apply sensitivity
    deltaX *= state_.sensitivity;
    deltaY *= state_.sensitivity;

    // Update yaw and pitch
    state_.yaw += deltaX;
    state_.pitch -= deltaY; // Invert Y axis for natural look

    // Clamp pitch to prevent camera flipping
    state_.pitch = std::max(-89.0f, std::min(89.0f, state_.pitch));

    // Keep yaw in 0-360 range
    if (state_.yaw > 360.0f)
        state_.yaw -= 360.0f;
    if (state_.yaw < 0.0f)
        state_.yaw += 360.0f;

    lastMousePos_ = currentMousePos;
}

void DebugCamera::updateDirectionVectors()
{
    // Convert yaw and pitch to direction vector
    float yawRad = state_.yaw * 3.14159f / 180.0f;
    float pitchRad = state_.pitch * 3.14159f / 180.0f;

    state_.direction.x = cos(pitchRad) * sin(yawRad);
    state_.direction.y = sin(pitchRad);
    state_.direction.z = -cos(pitchRad) * cos(yawRad);

    state_.direction = state_.direction.normalized();

    // Recalculate up vector to maintain orthogonal basis
    Vector3 right = state_.direction.cross(Vector3(0.0f, 1.0f, 0.0f)).normalized();
    state_.up = right.cross(state_.direction).normalized();
}

bool DebugCamera::isKeyPressed(int key) const
{
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}

void DebugCamera::updateTransition(float deltaTime)
{
    transitionTime_ += deltaTime;
    float t = transitionTime_ / transitionDuration_;

    if (t >= 1.0f)
    {
        // Transition complete
        t = 1.0f;
        isTransitioning_ = false;

        if (transitioningToDebug_)
        {
            // Reset mouse tracking when entering debug mode
            mouseInitialized_ = false;
        }
    }

    // Smooth ease-in-out interpolation
    t = t * t * (3.0f - 2.0f * t);

    if (transitioningToDebug_)
    {
        // Transition to debug position (looking at origin)
        state_.position = lerp(originalPosition_, debugTargetPosition_, t);
        state_.direction = lerp(originalDirection_, debugTargetDirection_, t).normalized();

        // Recalculate up vector to maintain orthogonal basis
        Vector3 right = state_.direction.cross(Vector3(0.0f, 1.0f, 0.0f)).normalized();
        state_.up = right.cross(state_.direction).normalized();
    }
    else
    {
        // Transition back to original position
        state_.position = lerp(debugTargetPosition_, originalPosition_, t);
        state_.direction = lerp(debugTargetDirection_, originalDirection_, t).normalized();
        state_.up = lerp(Vector3(0.0f, 1.0f, 0.0f), originalUp_, t).normalized();
    }

    // Update pitch and yaw based on direction
    state_.yaw = atan2(state_.direction.x, -state_.direction.z) * 180.0f / 3.14159f;
    state_.pitch = asin(state_.direction.y) * 180.0f / 3.14159f;
}

DebugCamera::Vector3 DebugCamera::lerp(const Vector3 &a, const Vector3 &b, float t) const
{
    return Vector3(
        a.x + t * (b.x - a.x),
        a.y + t * (b.y - a.y),
        a.z + t * (b.z - a.z));
}
