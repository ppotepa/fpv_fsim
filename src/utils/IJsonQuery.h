#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

/**
 * @brief Interface for JSON document query operations.
 *
 * Provides methods for navigating and extracting data from JSON structures.
 */
class IJsonQuery
{
public:
    virtual ~IJsonQuery() = default;

    /**
     * @brief Check if a key exists in the current JSON object
     * @param key The key to check
     * @return true if key exists, false otherwise
     */
    virtual bool hasKey(const std::string &key) const = 0;

    /**
     * @brief Get string value from JSON object
     * @param key The key to query
     * @param defaultValue Default value if key not found
     * @return String value or default
     */
    virtual std::string getString(const std::string &key, const std::string &defaultValue = "") const = 0;

    /**
     * @brief Get integer value from JSON object
     * @param key The key to query
     * @param defaultValue Default value if key not found
     * @return Integer value or default
     */
    virtual int getInt(const std::string &key, int defaultValue = 0) const = 0;

    /**
     * @brief Get float value from JSON object
     * @param key The key to query
     * @param defaultValue Default value if key not found
     * @return Float value or default
     */
    virtual float getFloat(const std::string &key, float defaultValue = 0.0f) const = 0;

    /**
     * @brief Get boolean value from JSON object
     * @param key The key to query
     * @param defaultValue Default value if key not found
     * @return Boolean value or default
     */
    virtual bool getBool(const std::string &key, bool defaultValue = false) const = 0;

    /**
     * @brief Get array of objects from JSON
     * @param key The key to query
     * @return Vector of JSON objects
     */
    virtual std::vector<nlohmann::json> getArray(const std::string &key) const = 0;

    /**
     * @brief Get nested JSON object
     * @param key The key to query
     * @return JSON object
     */
    virtual nlohmann::json getObject(const std::string &key) const = 0;

    /**
     * @brief Get the current JSON object
     * @return Reference to current JSON object
     */
    virtual const nlohmann::json &getCurrentJson() const = 0;
};
