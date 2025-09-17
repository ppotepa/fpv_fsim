#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

/**
 * @brief Interface for JSON document loading operations.
 *
 * Follows Single Responsibility Principle by focusing solely on JSON loading.
 */
class IJsonLoader
{
public:
    virtual ~IJsonLoader() = default;

    /**
     * @brief Load JSON from file.
     * @param path Path to the JSON file
     * @return true if load successful, false otherwise
     */
    virtual bool loadFile(const std::string &path) = 0;

    /**
     * @brief Load JSON from string content.
     * @param jsonContent JSON content as string
     * @return true if load successful, false otherwise
     */
    virtual bool loadString(const std::string &jsonContent) = 0;

    /**
     * @brief Get the root JSON object
     * @return Reference to the root JSON object
     */
    virtual const nlohmann::json &getRootJson() const = 0;
};
