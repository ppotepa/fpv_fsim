#ifndef IXML_LOADER_H
#define IXML_LOADER_H

#include <string>

/**
 * @brief Interface for XML document loading operations.
 *
 * Follows Single Responsibility Principle by focusing solely on XML loading.
 */
class IXmlLoader
{
public:
    virtual ~IXmlLoader() = default;

    /**
     * @brief Load XML from file.
     * @param path Path to the XML file
     * @return true if loading succeeded, false otherwise
     */
    virtual bool loadFile(const std::string &path) = 0;

    /**
     * @brief Load XML from string content.
     * @param xmlContent XML content as string
     * @return true if loading succeeded, false otherwise
     */
    virtual bool loadString(const std::string &xmlContent) = 0;

    /**
     * @brief Clear loaded XML document and reset state.
     */
    virtual void clear() = 0;
};

#endif // IXML_LOADER_H
