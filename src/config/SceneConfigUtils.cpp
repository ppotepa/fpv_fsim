#include "SceneConfigParser.h"
#include <sstream>
#include <algorithm>
#include <regex>
#include <cmath>

namespace SceneConfig
{
    namespace Utils
    {

        // ============================================================================
        // String Conversion Utilities
        // ============================================================================

        VoxelPrimitive::Type stringToVoxelType(const std::string &str)
        {
            std::string lower = str;
            std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

            if (lower == "cube")
                return VoxelPrimitive::Type::Cube;
            if (lower == "sphere")
                return VoxelPrimitive::Type::Sphere;
            if (lower == "cylinder")
                return VoxelPrimitive::Type::Cylinder;
            if (lower == "plane")
                return VoxelPrimitive::Type::Plane;

            return VoxelPrimitive::Type::Cube; // Default fallback
        }

        std::string voxelTypeToString(VoxelPrimitive::Type type)
        {
            switch (type)
            {
            case VoxelPrimitive::Type::Cube:
                return "cube";
            case VoxelPrimitive::Type::Sphere:
                return "sphere";
            case VoxelPrimitive::Type::Cylinder:
                return "cylinder";
            case VoxelPrimitive::Type::Plane:
                return "plane";
            default:
                return "cube";
            }
        }

        Light::Type stringToLightType(const std::string &str)
        {
            std::string lower = str;
            std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

            if (lower == "directional")
                return Light::Type::Directional;
            if (lower == "point")
                return Light::Type::Point;
            if (lower == "spot")
                return Light::Type::Spot;
            if (lower == "ambient")
                return Light::Type::Ambient;

            return Light::Type::Directional; // Default fallback
        }

        std::string lightTypeToString(Light::Type type)
        {
            switch (type)
            {
            case Light::Type::Directional:
                return "directional";
            case Light::Type::Point:
                return "point";
            case Light::Type::Spot:
                return "spot";
            case Light::Type::Ambient:
                return "ambient";
            default:
                return "directional";
            }
        }

        Camera::Type stringToCameraType(const std::string &str)
        {
            std::string lower = str;
            std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

            if (lower == "perspective")
                return Camera::Type::Perspective;
            if (lower == "orthographic" || lower == "ortho")
                return Camera::Type::Orthographic;

            return Camera::Type::Perspective; // Default fallback
        }

        std::string cameraTypeToString(Camera::Type type)
        {
            switch (type)
            {
            case Camera::Type::Perspective:
                return "perspective";
            case Camera::Type::Orthographic:
                return "orthographic";
            default:
                return "perspective";
            }
        }

        // ============================================================================
        // Transform Utilities
        // ============================================================================

        Transform combineTransforms(const Transform &parent, const Transform &child)
        {
            Transform result;

            // Combine positions (parent.position + parent.rotation * child.position)
            // Simplified - in real implementation would use proper quaternion math
            result.position.x = parent.position.x + child.position.x;
            result.position.y = parent.position.y + child.position.y;
            result.position.z = parent.position.z + child.position.z;

            // Combine rotations (quaternion multiplication)
            // Simplified - in real implementation would use proper quaternion multiplication
            result.rotation = child.rotation; // For now, just use child rotation

            // Combine scales (component-wise multiplication)
            result.scale.x = parent.scale.x * child.scale.x;
            result.scale.y = parent.scale.y * child.scale.y;
            result.scale.z = parent.scale.z * child.scale.z;

            return result;
        }

        Transform interpolateTransforms(const Transform &a, const Transform &b, float t)
        {
            t = std::clamp(t, 0.0f, 1.0f);
            Transform result;

            // Linear interpolation for position
            result.position.x = a.position.x + t * (b.position.x - a.position.x);
            result.position.y = a.position.y + t * (b.position.y - a.position.y);
            result.position.z = a.position.z + t * (b.position.z - a.position.z);

            // Spherical linear interpolation for rotation (simplified)
            result.rotation.x = a.rotation.x + t * (b.rotation.x - a.rotation.x);
            result.rotation.y = a.rotation.y + t * (b.rotation.y - a.rotation.y);
            result.rotation.z = a.rotation.z + t * (b.rotation.z - a.rotation.z);
            result.rotation.w = a.rotation.w + t * (b.rotation.w - a.rotation.w);
            normalizeQuaternion(result.rotation);

            // Linear interpolation for scale
            result.scale.x = a.scale.x + t * (b.scale.x - a.scale.x);
            result.scale.y = a.scale.y + t * (b.scale.y - a.scale.y);
            result.scale.z = a.scale.z + t * (b.scale.z - a.scale.z);

            return result;
        }

        // ============================================================================
        // Color Utilities
        // ============================================================================

        Material::Color parseColorString(const std::string &colorStr)
        {
            Material::Color color = {1.0f, 1.0f, 1.0f, 1.0f}; // Default white

            std::string trimmed = colorStr;
            // Remove whitespace
            trimmed.erase(std::remove_if(trimmed.begin(), trimmed.end(), ::isspace), trimmed.end());

            if (trimmed.empty())
            {
                return color;
            }

            // Handle hex colors (#RRGGBB or #RRGGBBAA)
            if (trimmed[0] == '#')
            {
                std::string hex = trimmed.substr(1);

                if (hex.length() == 6 || hex.length() == 8)
                {
                    try
                    {
                        unsigned long value = std::stoul(hex, nullptr, 16);

                        if (hex.length() == 6)
                        {
                            // RGB format
                            color.r = ((value >> 16) & 0xFF) / 255.0f;
                            color.g = ((value >> 8) & 0xFF) / 255.0f;
                            color.b = (value & 0xFF) / 255.0f;
                            color.a = 1.0f;
                        }
                        else
                        {
                            // RGBA format
                            color.r = ((value >> 24) & 0xFF) / 255.0f;
                            color.g = ((value >> 16) & 0xFF) / 255.0f;
                            color.b = ((value >> 8) & 0xFF) / 255.0f;
                            color.a = (value & 0xFF) / 255.0f;
                        }
                    }
                    catch (...)
                    {
                        // Invalid hex format, return default
                    }
                }
                return color;
            }

            // Handle RGB/RGBA format: "r,g,b" or "r,g,b,a"
            if (trimmed.find(',') != std::string::npos)
            {
                std::vector<float> components;
                std::stringstream ss(trimmed);
                std::string component;

                while (std::getline(ss, component, ','))
                {
                    try
                    {
                        components.push_back(std::stof(component));
                    }
                    catch (...)
                    {
                        // Invalid component, skip
                    }
                }

                if (components.size() >= 3)
                {
                    color.r = std::clamp(components[0], 0.0f, 1.0f);
                    color.g = std::clamp(components[1], 0.0f, 1.0f);
                    color.b = std::clamp(components[2], 0.0f, 1.0f);

                    if (components.size() >= 4)
                    {
                        color.a = std::clamp(components[3], 0.0f, 1.0f);
                    }
                }
                return color;
            }

            // Handle named colors
            std::string lower = trimmed;
            std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

            if (lower == "red")
                return {1.0f, 0.0f, 0.0f, 1.0f};
            if (lower == "green")
                return {0.0f, 1.0f, 0.0f, 1.0f};
            if (lower == "blue")
                return {0.0f, 0.0f, 1.0f, 1.0f};
            if (lower == "white")
                return {1.0f, 1.0f, 1.0f, 1.0f};
            if (lower == "black")
                return {0.0f, 0.0f, 0.0f, 1.0f};
            if (lower == "yellow")
                return {1.0f, 1.0f, 0.0f, 1.0f};
            if (lower == "cyan")
                return {0.0f, 1.0f, 1.0f, 1.0f};
            if (lower == "magenta")
                return {1.0f, 0.0f, 1.0f, 1.0f};
            if (lower == "gray" || lower == "grey")
                return {0.5f, 0.5f, 0.5f, 1.0f};
            if (lower == "orange")
                return {1.0f, 0.5f, 0.0f, 1.0f};
            if (lower == "purple")
                return {0.5f, 0.0f, 0.5f, 1.0f};
            if (lower == "brown")
                return {0.6f, 0.3f, 0.0f, 1.0f};
            if (lower == "pink")
                return {1.0f, 0.7f, 0.8f, 1.0f};

            return color; // Return default if no match
        }

        std::string colorToString(const Material::Color &color)
        {
            std::ostringstream oss;
            oss << std::fixed;
            oss.precision(3);
            oss << color.r << "," << color.g << "," << color.b << "," << color.a;
            return oss.str();
        }

        Material::Color interpolateColors(const Material::Color &a, const Material::Color &b, float t)
        {
            t = std::clamp(t, 0.0f, 1.0f);

            return {
                a.r + t * (b.r - a.r),
                a.g + t * (b.g - a.g),
                a.b + t * (b.b - a.b),
                a.a + t * (b.a - a.a)};
        }

        // ============================================================================
        // Validation Utilities
        // ============================================================================

        bool isValidFloat(const std::string &str)
        {
            if (str.empty())
                return false;

            try
            {
                std::stof(str);
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        bool isValidColor(const std::string &str)
        {
            if (str.empty())
                return false;

            // Check hex format
            if (str[0] == '#')
            {
                if (str.length() != 7 && str.length() != 9)
                    return false;

                for (size_t i = 1; i < str.length(); ++i)
                {
                    if (!std::isxdigit(str[i]))
                        return false;
                }
                return true;
            }

            // Check RGB/RGBA format
            if (str.find(',') != std::string::npos)
            {
                std::stringstream ss(str);
                std::string component;
                int componentCount = 0;

                while (std::getline(ss, component, ','))
                {
                    if (!isValidFloat(component))
                        return false;
                    componentCount++;
                }

                return (componentCount == 3 || componentCount == 4);
            }

            // Check named colors (simplified)
            std::string lower = str;
            std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

            static const std::vector<std::string> namedColors = {
                "red", "green", "blue", "white", "black", "yellow", "cyan",
                "magenta", "gray", "grey", "orange", "purple", "brown", "pink"};

            return std::find(namedColors.begin(), namedColors.end(), lower) != namedColors.end();
        }

        bool isValidId(const std::string &id)
        {
            if (id.empty())
                return false;

            // ID must start with letter or underscore
            if (!std::isalpha(id[0]) && id[0] != '_')
                return false;

            // ID can contain letters, digits, underscores, and hyphens
            for (size_t i = 1; i < id.length(); ++i)
            {
                if (!std::isalnum(id[i]) && id[i] != '_' && id[i] != '-')
                {
                    return false;
                }
            }

            return true;
        }

        bool isValidPath(const std::string &path)
        {
            if (path.empty())
                return false;

            // Basic path validation - check for invalid characters
            static const std::string invalidChars = "<>:\"|?*";
            for (char c : invalidChars)
            {
                if (path.find(c) != std::string::npos)
                {
                    return false;
                }
            }

            return true;
        }

        // ============================================================================
        // Math Utilities
        // ============================================================================

        float degreesToRadians(float degrees)
        {
            return degrees * static_cast<float>(M_PI) / 180.0f;
        }

        float radiansToDegrees(float radians)
        {
            return radians * 180.0f / static_cast<float>(M_PI);
        }

        void normalizeQuaternion(Transform::Rotation &quat)
        {
            float length = std::sqrt(quat.x * quat.x + quat.y * quat.y + quat.z * quat.z + quat.w * quat.w);

            if (length > 0.0f)
            {
                float invLength = 1.0f / length;
                quat.x *= invLength;
                quat.y *= invLength;
                quat.z *= invLength;
                quat.w *= invLength;
            }
            else
            {
                // Default to identity quaternion
                quat.x = 0.0f;
                quat.y = 0.0f;
                quat.z = 0.0f;
                quat.w = 1.0f;
            }
        }

        // ============================================================================
        // File Utilities
        // ============================================================================

        std::string getFileExtension(const std::string &path)
        {
            size_t dotPos = path.find_last_of('.');
            if (dotPos == std::string::npos || dotPos == path.length() - 1)
            {
                return "";
            }

            std::string ext = path.substr(dotPos + 1);
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            return ext;
        }

        std::string getBasePath(const std::string &path)
        {
            size_t slashPos = path.find_last_of("/\\");
            if (slashPos == std::string::npos)
            {
                return "";
            }

            return path.substr(0, slashPos + 1);
        }

        std::string resolvePath(const std::string &basePath, const std::string &relativePath)
        {
            if (relativePath.empty())
                return basePath;

            // If relative path is actually absolute, return it as-is
            if (relativePath[0] == '/' || (relativePath.length() > 1 && relativePath[1] == ':'))
            {
                return relativePath;
            }

            // Combine base path with relative path
            std::string result = basePath;
            if (!result.empty() && result.back() != '/' && result.back() != '\\')
            {
                result += "/";
            }
            result += relativePath;

            // Normalize path separators
            std::replace(result.begin(), result.end(), '\\', '/');

            // Resolve relative path components (., ..)
            std::vector<std::string> components;
            std::stringstream ss(result);
            std::string component;

            while (std::getline(ss, component, '/'))
            {
                if (component.empty() || component == ".")
                {
                    continue;
                }
                else if (component == "..")
                {
                    if (!components.empty())
                    {
                        components.pop_back();
                    }
                }
                else
                {
                    components.push_back(component);
                }
            }

            // Rebuild path
            result.clear();
            for (size_t i = 0; i < components.size(); ++i)
            {
                if (i > 0)
                    result += "/";
                result += components[i];
            }

            return result;
        }

        bool fileExists(const std::string &path)
        {
            std::ifstream file(path);
            return file.good();
        }

    } // namespace Utils
} // namespace SceneConfig
