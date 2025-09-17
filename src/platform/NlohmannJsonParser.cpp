#include "NlohmannJsonParser.h"
#include <fstream>
#include <sstream>
#include <iostream>

NlohmannJsonParser::NlohmannJsonParser() : isValid_(false)
{
    clear();
}

bool NlohmannJsonParser::loadFile(const std::string &path)
{
    try
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            addError("Failed to open JSON file: " + path);
            return false;
        }

        file >> rootJson_;
        currentJson_ = rootJson_;
        isValid_ = true;
        return true;
    }
    catch (const nlohmann::json::parse_error &e)
    {
        addError("JSON parse error in file " + path + ": " + e.what());
        isValid_ = false;
        return false;
    }
    catch (const std::exception &e)
    {
        addError("Error loading JSON file " + path + ": " + e.what());
        isValid_ = false;
        return false;
    }
}

bool NlohmannJsonParser::loadString(const std::string &jsonContent)
{
    try
    {
        rootJson_ = nlohmann::json::parse(jsonContent);
        currentJson_ = rootJson_;
        isValid_ = true;
        return true;
    }
    catch (const nlohmann::json::parse_error &e)
    {
        addError("JSON parse error: " + std::string(e.what()));
        isValid_ = false;
        return false;
    }
    catch (const std::exception &e)
    {
        addError("Error parsing JSON string: " + std::string(e.what()));
        isValid_ = false;
        return false;
    }
}

const nlohmann::json &NlohmannJsonParser::getRootJson() const
{
    return rootJson_;
}

bool NlohmannJsonParser::hasKey(const std::string &key) const
{
    if (!isValid_ || !currentJson_.is_object())
        return false;

    return currentJson_.contains(key);
}

std::string NlohmannJsonParser::getString(const std::string &key, const std::string &defaultValue) const
{
    if (!hasKey(key))
        return defaultValue;

    try
    {
        return currentJson_[key].get<std::string>();
    }
    catch (const std::exception &)
    {
        return defaultValue;
    }
}

int NlohmannJsonParser::getInt(const std::string &key, int defaultValue) const
{
    if (!hasKey(key))
        return defaultValue;

    try
    {
        return currentJson_[key].get<int>();
    }
    catch (const std::exception &)
    {
        return defaultValue;
    }
}

float NlohmannJsonParser::getFloat(const std::string &key, float defaultValue) const
{
    if (!hasKey(key))
        return defaultValue;

    try
    {
        return currentJson_[key].get<float>();
    }
    catch (const std::exception &)
    {
        return defaultValue;
    }
}

bool NlohmannJsonParser::getBool(const std::string &key, bool defaultValue) const
{
    if (!hasKey(key))
        return defaultValue;

    try
    {
        return currentJson_[key].get<bool>();
    }
    catch (const std::exception &)
    {
        return defaultValue;
    }
}

std::vector<nlohmann::json> NlohmannJsonParser::getArray(const std::string &key) const
{
    std::vector<nlohmann::json> result;

    if (!hasKey(key))
        return result;

    try
    {
        const auto &jsonArray = currentJson_[key];
        if (jsonArray.is_array())
        {
            for (const auto &item : jsonArray)
            {
                result.push_back(item);
            }
        }
    }
    catch (const std::exception &)
    {
        // Return empty vector on error
    }

    return result;
}

nlohmann::json NlohmannJsonParser::getObject(const std::string &key) const
{
    if (!hasKey(key))
        return nlohmann::json::object();

    try
    {
        return currentJson_[key];
    }
    catch (const std::exception &)
    {
        return nlohmann::json::object();
    }
}

const nlohmann::json &NlohmannJsonParser::getCurrentJson() const
{
    return currentJson_;
}

void NlohmannJsonParser::addError(const std::string &error)
{
    errors_.push_back(error);
}

void NlohmannJsonParser::addWarning(const std::string &warning)
{
    warnings_.push_back(warning);
}

bool NlohmannJsonParser::hasErrors() const
{
    return !errors_.empty();
}

bool NlohmannJsonParser::hasWarnings() const
{
    return !warnings_.empty();
}

const std::vector<std::string> &NlohmannJsonParser::getErrors() const
{
    return errors_;
}

const std::vector<std::string> &NlohmannJsonParser::getWarnings() const
{
    return warnings_;
}

void NlohmannJsonParser::clear()
{
    errors_.clear();
    warnings_.clear();
    rootJson_ = nlohmann::json::object();
    currentJson_ = rootJson_;
    isValid_ = false;
}

void NlohmannJsonParser::setCurrentJson(const nlohmann::json &json)
{
    currentJson_ = json;
}

void NlohmannJsonParser::resetToRoot()
{
    currentJson_ = rootJson_;
}

bool NlohmannJsonParser::isValid() const
{
    return isValid_;
}
