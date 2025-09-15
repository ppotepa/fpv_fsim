#ifndef PUGIXMLPARSER_H
#define PUGIXMLPARSER_H

#include "IXmlParser.h"

class PugiXmlParser : public IXmlParser {
public:
    bool loadFile(const std::string& path) override;
    // Add more methods
};

#endif
