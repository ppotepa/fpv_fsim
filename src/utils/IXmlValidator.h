#ifndef IXML_VALIDATOR_H
#define IXML_VALIDATOR_H

#include <string>
#include <vector>

/**
 * @brief Interface for XML validation operations.
 *
 * Follows Single Responsibility Principle by focusing solely on XML validation.
 */
class IXmlValidator
{
public:
    virtual ~IXmlValidator() = default;

    /**
     * @brief Validate XML against schema.
     * @param schemaPath Path to the schema file
     * @param errors Vector to collect validation errors
     * @return true if validation passes, false otherwise
     */
    virtual bool validateAgainstSchema(const std::string &schemaPath, std::vector<std::string> &errors) const = 0;
};

#endif // IXML_VALIDATOR_H
