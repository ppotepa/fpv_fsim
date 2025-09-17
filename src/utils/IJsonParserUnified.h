#pragma once
#include "IJsonLoader.h"
#include "IJsonQuery.h"
#include "IJsonErrorHandler.h"
#include <nlohmann/json.hpp>

/**
 * @brief Unified interface combining all JSON operations.
 *
 * Provides a single interface for loading, querying, and error handling of JSON documents.
 */
class IJsonParserUnified : public IJsonLoader, public IJsonQuery, public IJsonErrorHandler
{
public:
    virtual ~IJsonParserUnified() = default;

    /**
     * @brief Set current JSON context for queries
     * @param json JSON object to set as current context
     */
    virtual void setCurrentJson(const nlohmann::json &json) = 0;

    /**
     * @brief Reset to root JSON context
     */
    virtual void resetToRoot() = 0;

    /**
     * @brief Check if JSON document is loaded and valid
     * @return true if document is ready for queries
     */
    virtual bool isValid() const = 0;
};
