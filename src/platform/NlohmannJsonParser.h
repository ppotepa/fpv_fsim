#pragma once
#include "utils/IJsonParserUnified.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <string>

/**
 * @brief Concrete implementation of JSON parser using nlohmann/json.
 *
 * Provides complete JSON parsing functionality for the engine.
 */
class NlohmannJsonParser : public IJsonParserUnified
{
private:
    nlohmann::json rootJson_;
    nlohmann::json currentJson_;
    std::vector<std::string> errors_;
    std::vector<std::string> warnings_;
    bool isValid_;

public:
    NlohmannJsonParser();
    virtual ~NlohmannJsonParser() = default;

    // IJsonLoader implementation
    bool loadFile(const std::string &path) override;
    bool loadString(const std::string &jsonContent) override;
    const nlohmann::json &getRootJson() const override;

    // IJsonQuery implementation
    bool hasKey(const std::string &key) const override;
    std::string getString(const std::string &key, const std::string &defaultValue = "") const override;
    int getInt(const std::string &key, int defaultValue = 0) const override;
    float getFloat(const std::string &key, float defaultValue = 0.0f) const override;
    bool getBool(const std::string &key, bool defaultValue = false) const override;
    std::vector<nlohmann::json> getArray(const std::string &key) const override;
    nlohmann::json getObject(const std::string &key) const override;
    const nlohmann::json &getCurrentJson() const override;

    // IJsonErrorHandler implementation
    void addError(const std::string &error) override;
    void addWarning(const std::string &warning) override;
    bool hasErrors() const override;
    bool hasWarnings() const override;
    const std::vector<std::string> &getErrors() const override;
    const std::vector<std::string> &getWarnings() const override;
    void clear() override;

    // IJsonParserUnified implementation
    void setCurrentJson(const nlohmann::json &json) override;
    void resetToRoot() override;
    bool isValid() const override;
};
