#include "AssetCompiler.h"
#include <iostream>
#include <string>

void printUsage(const char *programName)
{
    std::cout << "Asset Compiler Demo - Simple version for demonstration\n\n";
    std::cout << "Usage: " << programName << " [options] <input-file>\n\n";
    std::cout << "Options:\n";
    std::cout << "  -o <dir>     Output directory (default: runtime/data/packs)\n";
    std::cout << "  -d           Enable debug mode\n";
    std::cout << "  -h           Show this help\n\n";
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printUsage(argv[0]);
        return 1;
    }

    AssetCompiler compiler;
    std::string inputFile;
    std::string outputDir;
    bool debugMode = false;

    // Simple argument parsing
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help")
        {
            printUsage(argv[0]);
            return 0;
        }
        else if (arg == "-d" || arg == "--debug")
        {
            debugMode = true;
        }
        else if (arg == "-o" || arg == "--output")
        {
            if (i + 1 < argc)
            {
                outputDir = argv[++i];
            }
            else
            {
                std::cerr << "Error: -o requires output directory\n";
                return 1;
            }
        }
        else if (arg[0] != '-')
        {
            inputFile = arg;
        }
        else
        {
            std::cerr << "Unknown option: " << arg << "\n";
            return 1;
        }
    }

    if (inputFile.empty())
    {
        std::cerr << "Error: No input file specified\n";
        printUsage(argv[0]);
        return 1;
    }

    // Configure compiler
    if (!outputDir.empty())
    {
        compiler.setOutputDirectory(outputDir);
    }

    compiler.setDebugMode(debugMode);

    std::cout << "Asset Compiler Demo" << std::endl;
    std::cout << "==================" << std::endl;
    std::cout << "Input file: " << inputFile << std::endl;
    std::cout << "Debug mode: " << (debugMode ? "enabled" : "disabled") << std::endl;

    // Process the input file
    bool success = compiler.processAssetConfiguration(inputFile);

    // Report results
    const auto &errors = compiler.getErrors();
    const auto &warnings = compiler.getWarnings();

    if (!warnings.empty())
    {
        std::cout << "\nWarnings:" << std::endl;
        for (const auto &warning : warnings)
        {
            std::cout << "  " << warning.file << ":" << warning.line
                      << " " << warning.message << std::endl;
        }
    }

    if (!errors.empty())
    {
        std::cout << "\nErrors:" << std::endl;
        for (const auto &error : errors)
        {
            std::cout << "  " << error.file << ":" << error.line
                      << " " << error.message << std::endl;
        }
    }

    if (success)
    {
        std::cout << "\nAsset compilation completed successfully!" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "\nAsset compilation failed!" << std::endl;
        return 1;
    }
}
