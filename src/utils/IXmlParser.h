#ifndef IXMLPARSER_H
#define IXMLPARSER_H

#include <string>

class IXmlParser {
public:
    virtual ~IXmlParser() = default;
    virtual bool loadFile(const std::string& path) = 0;
    // Add more methods as needed
};

#endif
