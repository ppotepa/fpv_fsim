#ifndef PUGI_XML_PARSER_H
#define PUGI_XML_PARSER_H

#include "IXmlParser.h"
#include <pugixml.hpp>
#include <memory>

/**
 * @brief Concrete implementation of IXmlParser using the pugixml library.
 *
 * This class provides XML parsing functionality using pugixml, offering
 * efficient parsing and XPath-like query support for the asset loading system.
 */
class PugiXmlParser : public IXmlParser
{
public:
    /**
     * @brief Construct a new PugiXmlParser.
     */
    PugiXmlParser();

    /**
     * @brief Destroy the parser and clean up resources.
     */
    ~PugiXmlParser() override;

    // IXmlParser interface implementation
    bool loadFile(const std::string &path) override;
    bool loadString(const std::string &xmlContent) override;
    std::string getRootElementName() const override;
    bool hasElement(const std::string &elementName, const std::string &parentPath = "") const override;
    std::string getElementText(const std::string &elementPath) const override;
    std::string getElementAttribute(const std::string &elementPath, const std::string &attributeName) const override;
    std::vector<std::string> getChildElementNames(const std::string &parentPath = "") const override;
    std::vector<std::string> getElementsWithName(const std::string &elementName, const std::string &parentPath = "") const override;
    bool validateAgainstSchema(const std::string &schemaPath, std::vector<std::string> &errors) const override;
    std::string getLastError() const override;
    void clear() override;

private:
    /**
     * @brief Helper method to find an element by path.
     *
     * @param elementPath XPath-like path to the element
     * @return pugi::xml_node representing the element, or empty node if not found
     */
    pugi::xml_node findElementByPath(const std::string &elementPath) const;

    /**
     * @brief Convert a simple path string to a pugixml XPath query.
     *
     * @param path Simple path like "assets/textures/texture"
     * @return XPath query string compatible with pugixml
     */
    std::string pathToXPath(const std::string &path) const;

private:
    std::unique_ptr<pugi::xml_document> document_; /**< The loaded XML document */
    std::string lastError_;                        /**< Last error message */
};

#endif // PUGI_XML_PARSER_H
