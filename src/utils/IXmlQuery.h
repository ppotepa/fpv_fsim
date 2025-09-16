#ifndef IXML_QUERY_H
#define IXML_QUERY_H

#include <string>
#include <vector>

/**
 * @brief Interface for XML document querying operations.
 *
 * Follows Single Responsibility Principle by focusing solely on XML querying.
 */
class IXmlQuery
{
public:
    virtual ~IXmlQuery() = default;

    /**
     * @brief Get the root element name.
     * @return Name of the root element
     */
    virtual std::string getRootElementName() const = 0;

    /**
     * @brief Check if element exists.
     * @param elementName Name of the element to check
     * @param parentPath Optional parent path
     * @return true if element exists, false otherwise
     */
    virtual bool hasElement(const std::string &elementName, const std::string &parentPath = "") const = 0;

    /**
     * @brief Get element text content.
     * @param elementPath Path to the element
     * @return Text content of the element
     */
    virtual std::string getElementText(const std::string &elementPath) const = 0;

    /**
     * @brief Get element attribute value.
     * @param elementPath Path to the element
     * @param attributeName Name of the attribute
     * @return Attribute value
     */
    virtual std::string getElementAttribute(const std::string &elementPath, const std::string &attributeName) const = 0;

    /**
     * @brief Get child element names.
     * @param parentPath Path to the parent element
     * @return Vector of child element names
     */
    virtual std::vector<std::string> getChildElementNames(const std::string &parentPath = "") const = 0;

    /**
     * @brief Get elements with specific name.
     * @param elementName Name to search for
     * @param parentPath Optional parent path
     * @return Vector of element paths
     */
    virtual std::vector<std::string> getElementsWithName(const std::string &elementName, const std::string &parentPath = "") const = 0;
};

#endif // IXML_QUERY_H

