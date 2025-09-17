#pragma once

#include "Package.h"
#include "PackageJsonParser.h"
#include <unordered_map>
#include <functional>
#include <memory>
#include <vector>
#include <string>

namespace Assets
{

    // Package discovery result
    struct PackageDiscoveryResult
    {
        std::vector<std::string> packagePaths;
        std::vector<std::string> errors;
    };

    // Package manager for loading and managing packages
    class PackageManager
    {
    public:
        PackageManager();
        ~PackageManager();

        // Package discovery and loading
        PackageDiscoveryResult discoverPackages(const std::string &packagesDirectory);
        PackageLoadResult loadPackage(const std::string &packagePath);
        bool unloadPackage(const std::string &packageId);

        // Package access
        const Package *getPackage(const std::string &packageId) const;
        std::vector<const Package *> getAllPackages() const;
        bool isPackageLoaded(const std::string &packageId) const;

        // Dependency management
        std::vector<std::string> getLoadOrder(const std::vector<std::string> &packageIds) const;
        bool validateDependencies(const Package &package) const;
        std::vector<std::string> getMissingDependencies(const Package &package) const;

        // Asset resolution
        AssetId resolveAssetReference(const std::string &packageId,
                                      const std::string &assetRef) const;
        const Package *findPackageContainingAsset(AssetId assetId) const;

        // Events
        using PackageLoadedCallback = std::function<void(const Package &)>;
        using PackageUnloadedCallback = std::function<void(const std::string &)>;

        void setPackageLoadedCallback(PackageLoadedCallback callback)
        {
            packageLoadedCallback = callback;
        }

        void setPackageUnloadedCallback(PackageUnloadedCallback callback)
        {
            packageUnloadedCallback = callback;
        }

    private:
        // Internal storage
        std::unordered_map<std::string, std::unique_ptr<Package>> loadedPackages;
        PackageJsonParser parser;

        // Callbacks
        PackageLoadedCallback packageLoadedCallback;
        PackageUnloadedCallback packageUnloadedCallback;

        // Utility methods
        std::vector<std::string> findPackageFiles(const std::string &directory) const;
        bool hasCyclicDependencies(const std::vector<std::string> &packageIds) const;
        void buildDependencyGraph(const std::vector<std::string> &packageIds,
                                  std::unordered_map<std::string, std::vector<std::string>> &graph) const;
        std::vector<std::string> topologicalSort(const std::unordered_map<std::string,
                                                                          std::vector<std::string>> &graph) const;
    };

} // namespace Assets
