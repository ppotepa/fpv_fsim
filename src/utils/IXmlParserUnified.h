#ifndef IXML_PARSER_UNIFIED_H
#define IXML_PARSER_UNIFIED_H

#include "IXmlLoader.h"
#include "IXmlQuery.h"
#include "IXmlValidator.h"
#include "IXmlErrorHandler.h"

/**
 * @brief Unified interface combining all XML operations.
 *
 * This interface aggregates all XML functionality for clients that need
 * complete XML processing capabilities. Clients can also use individual
 * interfaces (IXmlLoader, IXmlQuery, etc.) to depend only on what they need,
 * following the Interface Segregation Principle.
 */
class IXmlParserUnified : public IXmlLoader, public IXmlQuery, public IXmlValidator, public IXmlErrorHandler
{
public:
    virtual ~IXmlParserUnified() = default;
};

#endif // IXML_PARSER_UNIFIED_H
