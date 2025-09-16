#ifndef IXML_PARSER_H
#define IXML_PARSER_H

#include <string>
#include <vector>

/**
 * @brief Abstract interface for XML parsing implementations.
 *
 * This interface defines a platform-independent way to parse XML files,
 * adhering to the IoC principle. Concrete implementations can use different
 * XML libraries (e.g., pugixml, rapidxml, tinyxml) while providing a
 * consistent interface for the asset loading system.
 */
class IXmlParser
{
public:
    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~IXmlParser() = default;

    /**
     * @brief Load and parse an XML file from the filesystem.
     *
     * @param path Absolute path to the XML file to load
     * @return true if the file was successfully loaded and parsed, false otherwise
     */
    virtual bool loadFile(const std::string &path) = 0;

    /**
     * @brief Parse XML content from a string.
     *
     * @param xmlContent The XML content as a string
     * @return true if the content was successfully parsed, false otherwise
     */
    virtual bool loadString(const std::string &xmlContent) = 0;

    /**
     * @brief Get the root element name of the parsed XML document.
     *
     * @return The name of the root element, or empty string if no document is loaded
     */
    virtual std::string getRootElementName() const = 0;

    /**
     * @brief Check if a child element exists with the given name.
     *
     * @param elementName Name of the child element to search for
     * @param parentPath Optional XPath-like path to the parent element (empty = root)
     * @return true if the element exists, false otherwise
     */
    virtual bool hasElement(const std::string &elementName, const std::string &parentPath = "") const = 0;

    /**
     * @brief Get the text content of an element.
     *
     * @param elementPath XPath-like path to the element
     * @return The text content of the element, or empty string if not found
     */
    virtual std::string getElementText(const std::string &elementPath) const = 0;

    /**
     * @brief Get an attribute value from an element.
     *
     * @param elementPath XPath-like path to the element
     * @param attributeName Name of the attribute to retrieve
     * @return The attribute value, or empty string if not found
     */
    virtual std::string getElementAttribute(const std::string &elementPath, const std::string &attributeName) const = 0;

    /**
     * @brief Get all child element names under a parent element.
     *
     * @param parentPath XPath-like path to the parent element (empty = root)
     * @return Vector of child element names
     */
    virtual std::vector<std::string> getChildElementNames(const std::string &parentPath = "") const = 0;

    /**
     * @brief Get all elements with a specific name under a parent.
     *
     * @param elementName Name of the elements to find
     * @param parentPath XPath-like path to the parent element (empty = root)
     * @return Vector of element paths that match the criteria
     */
    virtual std::vector<std::string> getElementsWithName(const std::string &elementName, const std::string &parentPath = "") const = 0;

    /**
     * @brief Validate the current XML document against an XSD schema.
     *
     * @param schemaPath Path to the XSD schema file
     * @param errors Output vector to collect validation errors
     * @return true if validation passes, false if there are errors
     */
    virtual bool validateAgainstSchema(const std::string &schemaPath, std::vector<std::string> &errors) const = 0;

    /**
     * @brief Get the last error message from parsing operations.
     *
     * @return Description of the last error that occurred, or empty string if no error
     */
    virtual std::string getLastError() const = 0;

    /**
     * @brief Clear the current document and reset the parser state.
     */
    virtual void clear() = 0;
};

#endif // IXML_PARSER_H

