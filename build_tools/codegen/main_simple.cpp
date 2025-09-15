#include "AssetIdGenerator_Simple.h"
#include <iostream>
#include <string>
#include <vector>

void printUsage(const char *programName)
{
    std::cout << "Asset ID Generator Demo - Simple version for demonstration\n\n";
    std::cout << "Usage: " << programName << " [options] <package-files...>\n\n";
    std::cout << "Options:\n";
    std::cout << "  -o <file>    Output header file (default: src/core/AssetIds.h)\n";
    std::cout << "  -h           Show this help\n\n";
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printUsage(argv[0]);
        return 1;
    }

    AssetIdGenerator generator;
    std::vector<std::string> packageFiles;
    std::string outputFile = "src/core/AssetIds.h";

    // Simple argument parsing
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help")
        {
            printUsage(argv[0]);
            return 0;
        }
        else if (arg == "-o" || arg == "--output")
        {
            if (i + 1 < argc)
            {
                outputFile = argv[++i];
            }
            else
            {
                std::cerr << "Error: -o requires output file\n";
                return 1;
            }
        }
        else if (arg[0] != '-')
        {
            packageFiles.push_back(arg);
        }
        else
        {
            std::cerr << "Unknown option: " << arg << "\n";
            return 1;
        }
    }

    if (packageFiles.empty())
    {
        std::cerr << "Error: No package files specified\n";
        printUsage(argv[0]);
        return 1;
    }

    std::cout << "Asset ID Generator Demo" << std::endl;
    std::cout << "======================" << std::endl;
    std::cout << "Output file: " << outputFile << std::endl;

    // Process package files
    bool success = true;
    for (const std::string &packageFile : packageFiles)
    {
        std::cout << "\nProcessing: " << packageFile << std::endl;
        if (!generator.scanPackageFile(packageFile))
        {
            std::cerr << "Failed to process: " << packageFile << std::endl;
            success = false;
        }
    }

    if (!success)
    {
        std::cout << "\nSome files failed to process!" << std::endl;
        return 1;
    }

    // Generate output
    std::cout << "\nGenerating output..." << std::endl;
    if (!generator.generateCppHeader(outputFile))
    {
        std::cerr << "Failed to generate output file: " << outputFile << std::endl;
        return 1;
    }

    // Print statistics
    generator.printStatistics();

    std::cout << "\nAsset ID generation completed successfully!" << std::endl;
    return 0;
}
