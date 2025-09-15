# IXmlParser.h

## Methods

- `virtual ~IXmlParser() = default;`

  **Summary:** Virtual destructor for XML parser interface.

- `virtual bool loadFile(const std::string &path) = 0;`

  **Summary:** Pure virtual method to load an XML file from the given path.
