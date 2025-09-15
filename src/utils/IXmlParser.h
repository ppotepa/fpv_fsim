#ifndef IXMLPARSER_H
#define IXMLPARSER_H

#include <string>
#include <vector>

/**
 * @brief Abstract interface for XML parsing operations.
 *
 * Note: This interface currently combines multiple responsibilities
 * (loading, querying, validation) which violates SRP/ISP.
 * Consider refactoring into separate interfaces in future iterations.
 */
class IXmlParser
{
public:
    virtual ~IXmlParser() = default;

    // XML Loading
    virtual bool loadFile(const std::string &path) = 0;
    virtual bool loadString(const std::string &xmlContent) = 0;

    // XML Querying
    virtual std::string getRootElementName() const = 0;
    virtual bool hasElement(const std::string &elementName, const std::string &parentPath = "") const = 0;
    virtual std::string getElementText(const std::string &elementPath) const = 0;
    virtual std::string getElementAttribute(const std::string &elementPath, const std::string &attributeName) const = 0;
    virtual std::vector<std::string> getChildElementNames(const std::string &parentPath = "") const = 0;
    virtual std::vector<std::string> getElementsWithName(const std::string &elementName, const std::string &parentPath = "") const = 0;

    // XML Validation
    virtual bool validateAgainstSchema(const std::string &schemaPath, std::vector<std::string> &errors) const = 0;

    // Error Handling & State Management
    virtual std::string getLastError() const = 0;
    virtual void clear() = 0;
};

#endif
