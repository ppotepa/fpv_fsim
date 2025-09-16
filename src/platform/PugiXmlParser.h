#ifndef PUGI_XML_PARSER_H
#define PUGI_XML_PARSER_H

#include "utils/IXmlLoader.h"
#include "utils/IXmlQuery.h"
#include "utils/IXmlValidator.h"
#include "utils/IXmlErrorHandler.h"
#include "utils/IXmlParserUnified.h"
#include <memory>
#include <string>

/**
 * @brief Stub implementation of XML interfaces.
 *
 * This is a minimal stub implementation that allows the build to succeed
 * while architectural changes are being made. In production, this would
 * use a proper XML parsing library like pugixml.
 *
 * Implements multiple focused interfaces following ISP (Interface Segregation Principle)
 * to reduce coupling and improve flexibility.
 */
class PugiXmlParser : public IXmlParserUnified
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

    // IXmlLoader interface implementation
    bool loadFile(const std::string &path) override;
    bool loadString(const std::string &xmlContent) override;
    void clear() override;

    // IXmlQuery interface implementation
    std::string getRootElementName() const override;
    bool hasElement(const std::string &elementName, const std::string &parentPath = "") const override;
    std::string getElementText(const std::string &elementPath) const override;
    std::string getElementAttribute(const std::string &elementPath, const std::string &attributeName) const override;
    std::vector<std::string> getChildElementNames(const std::string &parentPath = "") const override;
    std::vector<std::string> getElementsWithName(const std::string &elementName, const std::string &parentPath = "") const override;

    // IXmlValidator interface implementation
    bool validateAgainstSchema(const std::string &schemaPath, std::vector<std::string> &errors) const override;

    // IXmlErrorHandler interface implementation
    std::string getLastError() const override;

private:
    std::string lastError_;         /**< Last error message */
    std::string lastLoadedContent_; /**< Raw XML content last loaded (for best-effort validation/query) */
};

#endif // PUGI_XML_PARSER_H

