#include "PugiXmlParser.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>

// Minimal stub implementation without pugixml dependency
// This allows the build to succeed while architectural changes are being made

PugiXmlParser::PugiXmlParser() {}
PugiXmlParser::~PugiXmlParser() = default;

bool PugiXmlParser::loadFile(const std::string &path)
{
    if (!std::filesystem::exists(path))
    {
        lastError_ = "File does not exist: " + path;
        return false;
    }

    std::ifstream file(path);
    if (!file.is_open())
    {
        lastError_ = "Cannot open file: " + path;
        return false;
    }

    // Read file content with better error handling
    try
    {
        std::string content((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());

        // Basic XML validation
        if (content.empty())
        {
            lastError_ = "File is empty: " + path;
            return false;
        }

        // Check for XML declaration or root element
        if (content.find('<') == std::string::npos)
        {
            lastError_ = "File does not appear to contain XML: " + path;
            return false;
        }

        // Store content for best-effort querying/validation
        lastLoadedContent_ = content;

        std::cout << "PugiXmlParser loaded file: " << path << " (" << content.size() << " bytes)" << std::endl;
        lastError_.clear();
        return true;
    }
    catch (const std::exception &e)
    {
        lastError_ = "Error reading file " + path + ": " + e.what();
        return false;
    }
}

bool PugiXmlParser::loadString(const std::string &xmlContent)
{
    try
    {
        if (xmlContent.empty())
        {
            lastError_ = "Empty XML content provided";
            return false;
        }

        // Basic XML validation
        if (xmlContent.find('<') == std::string::npos)
        {
            lastError_ = "Content does not appear to contain XML";
            return false;
        }

        lastLoadedContent_ = xmlContent;
        std::cout << "PugiXmlParser loaded string content (" << xmlContent.size() << " bytes)" << std::endl;
        lastError_.clear();
        return true;
    }
    catch (const std::exception &e)
    {
        lastError_ = "Error loading XML string: " + std::string(e.what());
        return false;
    }
}

void PugiXmlParser::clear()
{
    lastError_.clear();
    lastLoadedContent_.clear();
}

std::string PugiXmlParser::getRootElementName() const
{
    // Best-effort: find first element after optional XML declaration
    std::string content = lastLoadedContent_;
    std::smatch m;
    std::regex re("<\\s*([A-Za-z_][A-Za-z0-9_\-:]*)");
    if (std::regex_search(content, m, re) && m.size() > 1)
    {
        return m.str(1);
    }
    return "";
}

bool PugiXmlParser::hasElement(const std::string &elementName, const std::string &parentPath) const
{
    if (lastLoadedContent_.empty())
        return false;
    std::string needle = "<" + elementName;
    return lastLoadedContent_.find(needle) != std::string::npos;
}

std::string PugiXmlParser::getElementText(const std::string &elementPath) const
{
    // elementPath is expected as simple tag name for this best-effort parser
    if (lastLoadedContent_.empty())
        return "";
    std::string open = "<" + elementPath + ">";
    std::string close = "</" + elementPath + ">";
    auto p = lastLoadedContent_.find(open);
    if (p == std::string::npos)
        return "";
    p += open.size();
    auto q = lastLoadedContent_.find(close, p);
    if (q == std::string::npos)
        return "";
    return lastLoadedContent_.substr(p, q - p);
}

std::string PugiXmlParser::getElementAttribute(const std::string &elementPath, const std::string &attributeName) const
{
    // Best-effort: search for <elementPath ... attributeName="value"
    if (lastLoadedContent_.empty())
        return "";
    std::regex re("<\\s*" + elementPath + "[^>]*\\b" + attributeName + "\\s*=\\s*\"([^\"]*)\"");
    std::smatch m;
    if (std::regex_search(lastLoadedContent_, m, re) && m.size() > 1)
        return m.str(1);
    return "";
}

std::vector<std::string> PugiXmlParser::getChildElementNames(const std::string &parentPath) const
{
    std::vector<std::string> out;
    if (lastLoadedContent_.empty())
        return out;
    // Very basic: find tags immediately under parentPath if parentPath provided, otherwise top-level
    std::string section = lastLoadedContent_;
    if (!parentPath.empty())
    {
        std::string open = "<" + parentPath;
        auto p = section.find(open);
        if (p != std::string::npos)
        {
            auto start = section.find('>', p);
            if (start != std::string::npos)
            {
                auto end = section.find("</" + parentPath + ">", start);
                if (end != std::string::npos)
                    section = section.substr(start + 1, end - start - 1);
            }
        }
    }

    std::regex re("<\\s*([A-Za-z_][A-Za-z0-9_\-:]*)");
    auto begin = std::sregex_iterator(section.begin(), section.end(), re);
    auto end = std::sregex_iterator();
    for (auto it = begin; it != end; ++it)
    {
        std::smatch m = *it;
        if (m.size() > 1)
            out.push_back(m.str(1));
    }
    return out;
}

std::vector<std::string> PugiXmlParser::getElementsWithName(const std::string &elementName, const std::string &parentPath) const
{
    std::vector<std::string> out;
    if (lastLoadedContent_.empty())
        return out;
    std::regex re("<\\s*" + elementName + "(?:\\s+[^>]*)?>([\\s\\S]*?)</" + elementName + ">");
    auto begin = std::sregex_iterator(lastLoadedContent_.begin(), lastLoadedContent_.end(), re);
    auto end = std::sregex_iterator();
    for (auto it = begin; it != end; ++it)
    {
        std::smatch m = *it;
        if (m.size() > 1)
            out.push_back(m.str(1));
    }
    return out;
}

bool PugiXmlParser::validateAgainstSchema(const std::string &schemaPath, std::vector<std::string> &errors) const
{
    errors.clear();
    std::cout << "PugiXmlParser: best-effort validation against schema: " << schemaPath << std::endl;

    if (lastLoadedContent_.empty())
    {
        errors.push_back("No XML content loaded to validate");
        return false;
    }

    if (!std::filesystem::exists(schemaPath))
    {
        errors.push_back("Schema file not found: " + schemaPath);
        return false;
    }

    // Very small heuristic-based XSD inspection: collect declared element names from the XSD
    std::ifstream sfile(schemaPath);
    if (!sfile.is_open())
    {
        errors.push_back("Cannot open schema file: " + schemaPath);
        return false;
    }
    std::string schema((std::istreambuf_iterator<char>(sfile)), std::istreambuf_iterator<char>());

    std::set<std::string> declaredElements;
    try
    {
        std::regex re("<\\s*(?:xs:)?element\\s+[^>]*name\\s*=\\s*\"([^\"]+)\"");
        auto begin = std::sregex_iterator(schema.begin(), schema.end(), re);
        auto end = std::sregex_iterator();
        for (auto it = begin; it != end; ++it)
        {
            std::smatch m = *it;
            if (m.size() > 1)
                declaredElements.insert(m.str(1));
        }
    }
    catch (const std::regex_error &e)
    {
        errors.push_back(std::string("Schema regex parse error: ") + e.what());
        return false;
    }

    // If we couldn't find any elements in the XSD, warn but accept well-formedness
    if (declaredElements.empty())
    {
        // Basic well-formedness: check presence of a root element
        if (getRootElementName().empty())
        {
            errors.push_back("XML appears to be empty or malformed (no root element found)");
            return false;
        }
        return true;
    }

    // For each declared element, check it's present at least once in the document
    for (const auto &el : declaredElements)
    {
        if (lastLoadedContent_.find("<" + el) == std::string::npos)
        {
            errors.push_back("Declared element not found in XML: " + el);
        }
    }

    return errors.empty();
}

std::string PugiXmlParser::getLastError() const
{
    return lastError_;
}
