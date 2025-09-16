#include <iostream>
#include "../../../src/debug.h"

int main(int argc, char *argv[])
{
    try
    {
        if (Debug())
        {
            std::cout << "Asset Compiler CLI Tool - Debug Mode Enabled" << std::endl;
            std::cout << "Command line arguments: " << argc << std::endl;
            for (int i = 0; i < argc; ++i)
            {
                std::cout << "  argv[" << i << "]: " << argv[i] << std::endl;
            }
        }

        if (Debug())
        {
            std::cout << "Starting asset compilation process..." << std::endl;
        }

        // TODO: Implement XML -> IR -> cooked binaries

        if (Debug())
        {
            std::cout << "Asset compilation completed successfully" << std::endl;
        }

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Asset Compiler Error: " << e.what() << std::endl;
        if (Debug())
        {
            std::cerr << "Exception occurred in main function" << std::endl;
        }
        return 1;
    }
    catch (...)
    {
        std::cerr << "Asset Compiler: Unknown error occurred" << std::endl;
        return 1;
    }
}
