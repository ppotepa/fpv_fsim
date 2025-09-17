#pragma once
#include <string>
#include <vector>

/**
 * @brief Interface for JSON error handling operations.
 *
 * Provides methods for collecting and reporting JSON parsing errors.
 */
class IJsonErrorHandler
{
public:
    virtual ~IJsonErrorHandler() = default;

    /**
     * @brief Add an error message
     * @param error Error message to add
     */
    virtual void addError(const std::string &error) = 0;

    /**
     * @brief Add a warning message
     * @param warning Warning message to add
     */
    virtual void addWarning(const std::string &warning) = 0;

    /**
     * @brief Check if there are any errors
     * @return true if errors exist, false otherwise
     */
    virtual bool hasErrors() const = 0;

    /**
     * @brief Check if there are any warnings
     * @return true if warnings exist, false otherwise
     */
    virtual bool hasWarnings() const = 0;

    /**
     * @brief Get all error messages
     * @return Vector of error messages
     */
    virtual const std::vector<std::string> &getErrors() const = 0;

    /**
     * @brief Get all warning messages
     * @return Vector of warning messages
     */
    virtual const std::vector<std::string> &getWarnings() const = 0;

    /**
     * @brief Clear all errors and warnings
     */
    virtual void clear() = 0;
};
