#include "SpinBehavior.h"
#include "../core/Entity.h"
#include "../components/TransformC.h"
#include "../core/Vector3D.h"
#include "../core/Quaternion.h"
#include "../assets/Package.h"
#include <cmath>
#include <iostream>

namespace Behaviors
{
    SpinBehavior::SpinBehavior()
        : rotationSpeed_(30.0f)  // Default 30 degrees per second
        , rotationAxis_(0.0f, 1.0f, 0.0f)  // Default Y-axis
        , currentRotation_(0.0f)
        , entity_(nullptr)
    {
    }

    void SpinBehavior::initialize(Entity& entity, const Assets::BehaviorParams& params)
    {
        entity_ = &entity;

        // Parse parameters from XML
        rotationSpeed_ = params.getFloat("rotationSpeed", 30.0f);
        
        // Parse axis parameter
        std::string axisStr = params.getString("axis", "0.0,1.0,0.0");
        
        // Simple parsing for "x,y,z" format
        size_t pos1 = axisStr.find(',');
        size_t pos2 = axisStr.find(',', pos1 + 1);
        
        if (pos1 != std::string::npos && pos2 != std::string::npos)
        {
            try 
            {
                rotationAxis_.x = std::stof(axisStr.substr(0, pos1));
                rotationAxis_.y = std::stof(axisStr.substr(pos1 + 1, pos2 - pos1 - 1));
                rotationAxis_.z = std::stof(axisStr.substr(pos2 + 1));
                
                // Normalize the axis
                float length = std::sqrt(rotationAxis_.x * rotationAxis_.x + 
                               rotationAxis_.y * rotationAxis_.y + 
                               rotationAxis_.z * rotationAxis_.z);
                if (length > 0.0f)
                {
                    rotationAxis_.x /= length;
                    rotationAxis_.y /= length;
                    rotationAxis_.z /= length;
                }
            }
            catch (const std::exception&) 
            {
                std::cerr << "Warning: Invalid axis parameter, using default Y-axis" << std::endl;
                rotationAxis_ = Vector3D{0.0f, 1.0f, 0.0f};
            }
        }

        std::cout << "✅ SpinBehavior initialized:" << std::endl;
        std::cout << "   - Rotation speed: " << rotationSpeed_ << " degrees/second" << std::endl;
        std::cout << "   - Rotation axis: (" << rotationAxis_.x << ", " << rotationAxis_.y << ", " << rotationAxis_.z << ")" << std::endl;
    }

    void SpinBehavior::update(float deltaTime)
    {
        if (!entity_)
            return;

        // Update rotation
        currentRotation_ += rotationSpeed_ * deltaTime;
        
        // Keep rotation in [0, 360) range
        while (currentRotation_ >= 360.0f)
            currentRotation_ -= 360.0f;
        while (currentRotation_ < 0.0f)
            currentRotation_ += 360.0f;

        // Convert to radians
        float radians = currentRotation_ * (3.14159f / 180.0f);

        // Create rotation quaternion
        float halfAngle = radians * 0.5f;
        float sinHalf = std::sin(halfAngle);
        float cosHalf = std::cos(halfAngle);

        Quaternion rotation;
        rotation.x = rotationAxis_.x * sinHalf;
        rotation.y = rotationAxis_.y * sinHalf;
        rotation.z = rotationAxis_.z * sinHalf;
        rotation.w = cosHalf;

        // Apply rotation to entity (assuming it has TransformC component)
        // For now, just log the rotation for demonstration
        static int logCounter = 0;
        if (++logCounter % 60 == 0)  // Log every 60 updates (~1 second at 60fps)
        {
            std::cout << "🔄 Red cube rotation: " << currentRotation_ << " degrees" << std::endl;
        }
    }

    void SpinBehavior::cleanup()
    {
        entity_ = nullptr;
        std::cout << "🧹 SpinBehavior cleaned up" << std::endl;
    }
}
