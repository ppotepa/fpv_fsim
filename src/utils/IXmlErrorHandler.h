#ifndef IXML_ERROR_HANDLER_H
#define IXML_ERROR_HANDLER_H

#include <string>

/**
 * @brief Interface for XML error handling operations.
 *
 * Follows Single Responsibility Principle by focusing solely on error management.
 */
class IXmlErrorHandler
{
public:
    virtual ~IXmlErrorHandler() = default;

    /**
     * @brief Get the last error message.
     * @return Last error message, or empty string if no error
     */
    virtual std::string getLastError() const = 0;
};

#endif // IXML_ERROR_HANDLER_H
