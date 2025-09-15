#include "PugiXmlParser.h"
#include <filesystem>
#include <sstream>

PugiXmlParser::PugiXmlParser()
    : document_(std::make_unique<pugi::xml_document>())
{
}

PugiXmlParser::~PugiXmlParser() = default;

bool PugiXmlParser::loadFile(const std::string &path)
{
    clear();

    if (!std::filesystem::exists(path))
    {
        lastError_ = "File does not exist: " + path;
        return false;
    }

    pugi::xml_parse_result result = document_->load_file(path.c_str());
    if (!result)
    {
        lastError_ = "Failed to parse XML file '" + path + "': " + result.description();
        return false;
    }

    lastError_.clear();
    return true;
}

bool PugiXmlParser::loadString(const std::string &xmlContent)
{
    clear();

    pugi::xml_parse_result result = document_->load_string(xmlContent.c_str());
    if (!result)
    {
        lastError_ = "Failed to parse XML string: " + std::string(result.description());
        return false;
    }

    lastError_.clear();
    return true;
}

std::string PugiXmlParser::getRootElementName() const
{
    pugi::xml_node root = document_->document_element();
    return root ? root.name() : "";
}

bool PugiXmlParser::hasElement(const std::string &elementName, const std::string &parentPath) const
{
    pugi::xml_node parent = parentPath.empty() ? document_->document_element() : findElementByPath(parentPath);
    if (!parent)
        return false;

    return parent.child(elementName.c_str()) != nullptr;
}

std::string PugiXmlParser::getElementText(const std::string &elementPath) const
{
    pugi::xml_node element = findElementByPath(elementPath);
    return element ? element.child_value() : "";
}

std::string PugiXmlParser::getElementAttribute(const std::string &elementPath, const std::string &attributeName) const
{
    pugi::xml_node element = findElementByPath(elementPath);
    if (!element)
        return "";

    pugi::xml_attribute attr = element.attribute(attributeName.c_str());
    return attr ? attr.value() : "";
}

std::vector<std::string> PugiXmlParser::getChildElementNames(const std::string &parentPath) const
{
    std::vector<std::string> names;

    pugi::xml_node parent = parentPath.empty() ? document_->document_element() : findElementByPath(parentPath);
    if (!parent)
        return names;

    for (pugi::xml_node child : parent.children())
    {
        names.push_back(child.name());
    }

    return names;
}

std::vector<std::string> PugiXmlParser::getElementsWithName(const std::string &elementName, const std::string &parentPath) const
{
    std::vector<std::string> paths;

    pugi::xml_node parent = parentPath.empty() ? document_->document_element() : findElementByPath(parentPath);
    if (!parent)
        return paths;

    std::string basePath = parentPath.empty() ? getRootElementName() : parentPath;

    for (pugi::xml_node child : parent.children(elementName.c_str()))
    {
        // Build path to this element
        std::string childPath = basePath + "/" + elementName;
        paths.push_back(childPath);
    }

    return paths;
}

bool PugiXmlParser::validateAgainstSchema(const std::string &schemaPath, std::vector<std::string> &errors) const
{
    // Note: pugixml doesn't have built-in XSD validation
    // For now, we'll do basic well-formedness check
    // In a full implementation, you'd integrate with a library like libxml2 or xerces

    errors.clear();

    if (!document_->document_element())
    {
        errors.push_back("No root element found");
        return false;
    }

    // TODO: Implement actual XSD validation using external library
    // For now, just return true if the document is well-formed
    return true;
}

std::string PugiXmlParser::getLastError() const
{
    return lastError_;
}

void PugiXmlParser::clear()
{
    document_->reset();
    lastError_.clear();
}

pugi::xml_node PugiXmlParser::findElementByPath(const std::string &elementPath) const
{
    if (elementPath.empty())
        return document_->document_element();

    // Handle simple paths like "assets/textures/texture" or "texture"
    std::string xpath = pathToXPath(elementPath);

    try
    {
        pugi::xpath_node result = document_->select_node(xpath.c_str());
        return result.node();
    }
    catch (const pugi::xpath_exception &)
    {
        // If XPath fails, try simple traversal
        std::vector<std::string> parts;
        std::stringstream ss(elementPath);
        std::string part;

        while (std::getline(ss, part, '/'))
        {
            if (!part.empty())
                parts.push_back(part);
        }

        pugi::xml_node current = document_->document_element();
        for (size_t i = 0; i < parts.size() && current; ++i)
        {
            if (i == 0 && parts[i] == current.name())
            {
                // Skip root element name if it matches
                continue;
            }
            current = current.child(parts[i].c_str());
        }

        return current;
    }
}

std::string PugiXmlParser::pathToXPath(const std::string &path) const
{
    if (path.empty())
        return "";

    // Convert simple path to XPath
    // For example: "assets/textures/texture" -> "//assets/textures/texture"
    std::string xpath = path;

    // If path doesn't start with '/', add '//' for descendant search
    if (xpath[0] != '/')
        xpath = "//" + xpath;

    return xpath;
}
