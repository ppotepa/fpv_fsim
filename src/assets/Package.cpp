#include "Package.h"
#include <sstream>
#include <algorithm>

namespace Assets
{

    // FNV-1a hash implementation for stable ID generation
    uint64_t AssetIdGenerator::fnv1a_hash(const std::string &str)
    {
        const uint64_t FNV_offset_basis = 14695981039346656037ULL;
        const uint64_t FNV_prime = 1099511628211ULL;

        uint64_t hash = FNV_offset_basis;
        for (char c : str)
        {
            hash ^= static_cast<uint64_t>(c);
            hash *= FNV_prime;
        }
        return hash;
    }

    AssetId AssetIdGenerator::generateAssetId(const std::string &packageId, const std::string &assetId)
    {
        uint64_t packageHash = fnv1a_hash(packageId);
        uint64_t assetHash = fnv1a_hash(assetId);

        // Combine hashes and truncate to 32-bit for compatibility with existing AssetId
        uint64_t combined = (packageHash << 32) | (assetHash & 0xFFFFFFFF);
        return static_cast<AssetId>(combined & 0xFFFFFFFF);
    }

    SceneId AssetIdGenerator::generateSceneId(const std::string &packageId, const std::string &sceneId)
    {
        std::string combined = packageId + ":" + sceneId;
        return static_cast<SceneId>(fnv1a_hash(combined));
    }

    EntityId AssetIdGenerator::generateEntityId(const std::string &sceneId, const std::string &entityId)
    {
        std::string combined = sceneId + ":" + entityId;
        return static_cast<EntityId>(fnv1a_hash(combined));
    }

    // BehaviorParams implementation
    template <>
    float BehaviorParams::get<float>(const std::string &name, const float &defaultValue) const
    {
        return getFloat(name, defaultValue);
    }

    template <>
    int BehaviorParams::get<int>(const std::string &name, const int &defaultValue) const
    {
        return getInt(name, defaultValue);
    }

    template <>
    bool BehaviorParams::get<bool>(const std::string &name, const bool &defaultValue) const
    {
        return getBool(name, defaultValue);
    }

    template <>
    std::string BehaviorParams::get<std::string>(const std::string &name, const std::string &defaultValue) const
    {
        return getString(name, defaultValue);
    }

    float BehaviorParams::getFloat(const std::string &name, float defaultValue) const
    {
        auto it = parameters.find(name);
        if (it == parameters.end())
        {
            return defaultValue;
        }

        try
        {
            return std::stof(it->second);
        }
        catch (const std::exception &)
        {
            return defaultValue;
        }
    }

    int BehaviorParams::getInt(const std::string &name, int defaultValue) const
    {
        auto it = parameters.find(name);
        if (it == parameters.end())
        {
            return defaultValue;
        }

        try
        {
            return std::stoi(it->second);
        }
        catch (const std::exception &)
        {
            return defaultValue;
        }
    }

    bool BehaviorParams::getBool(const std::string &name, bool defaultValue) const
    {
        auto it = parameters.find(name);
        if (it == parameters.end())
        {
            return defaultValue;
        }

        std::string value = it->second;
        std::transform(value.begin(), value.end(), value.begin(), ::tolower);

        return value == "true" || value == "1" || value == "yes";
    }

    std::string BehaviorParams::getString(const std::string &name, const std::string &defaultValue) const
    {
        auto it = parameters.find(name);
        return (it != parameters.end()) ? it->second : defaultValue;
    }

    BehaviorParams::Vector3 BehaviorParams::getVector3(const std::string &name, const Vector3 &defaultValue) const
    {
        auto it = parameters.find(name);
        if (it == parameters.end())
        {
            return defaultValue;
        }

        std::istringstream iss(it->second);
        Vector3 result = defaultValue;
        iss >> result.x >> result.y >> result.z;
        return result;
    }

    BehaviorParams::Vector2 BehaviorParams::getVector2(const std::string &name, const Vector2 &defaultValue) const
    {
        auto it = parameters.find(name);
        if (it == parameters.end())
        {
            return defaultValue;
        }

        std::istringstream iss(it->second);
        Vector2 result = defaultValue;
        iss >> result.x >> result.y;
        return result;
    }

    BehaviorParams::Color BehaviorParams::getColor(const std::string &name, const Color &defaultValue) const
    {
        auto it = parameters.find(name);
        if (it == parameters.end())
        {
            return defaultValue;
        }

        std::istringstream iss(it->second);
        Color result = defaultValue;
        iss >> result.r >> result.g >> result.b >> result.a;
        return result;
    }

} // namespace Assets
