#include "PackageManager.h"
#include <filesystem>
#include <algorithm>
#include <queue>
#include <unordered_set>

namespace Assets {

PackageManager::PackageManager() = default;
PackageManager::~PackageManager() = default;

PackageDiscoveryResult PackageManager::discoverPackages(const std::string& packagesDirectory) {
    PackageDiscoveryResult result;
    
    try {
        if (!std::filesystem::exists(packagesDirectory)) {
            result.errors.push_back("Packages directory does not exist: " + packagesDirectory);
            return result;
        }
        
        result.packagePaths = findPackageFiles(packagesDirectory);
        
    } catch (const std::exception& e) {
        result.errors.push_back("Error discovering packages: " + std::string(e.what()));
    }
    
    return result;
}

PackageLoadResult PackageManager::loadPackage(const std::string& packagePath) {
    auto result = parser.loadPackage(packagePath);
    
    if (result.success) {
        // Check if package is already loaded
        if (isPackageLoaded(result.package.metadata.id)) {
            result.errors.push_back("Package already loaded: " + result.package.metadata.id);
            result.success = false;
            return result;
        }
        
        // Validate dependencies
        if (!validateDependencies(result.package)) {
            auto missing = getMissingDependencies(result.package);
            for (const auto& dep : missing) {
                result.errors.push_back("Missing dependency: " + dep);
            }
            result.success = false;
            return result;
        }
        
        // Store the package
        auto packagePtr = std::make_unique<Package>(std::move(result.package));
        const auto& packageRef = *packagePtr;
        loadedPackages[packageRef.metadata.id] = std::move(packagePtr);
        
        // Notify callback
        if (packageLoadedCallback) {
            packageLoadedCallback(packageRef);
        }
    }
    
    return result;
}

bool PackageManager::unloadPackage(const std::string& packageId) {
    auto it = loadedPackages.find(packageId);
    if (it == loadedPackages.end()) {
        return false;
    }
    
    // Check if other packages depend on this one
    for (const auto& [id, package] : loadedPackages) {
        if (id != packageId) {
            for (const auto& dep : package->metadata.dependencies) {
                if (dep.packageId == packageId && dep.required) {
                    // Cannot unload - other packages depend on it
                    return false;
                }
            }
        }
    }
    
    // Notify callback before removal
    if (packageUnloadedCallback) {
        packageUnloadedCallback(packageId);
    }
    
    loadedPackages.erase(it);
    return true;
}

const Package* PackageManager::getPackage(const std::string& packageId) const {
    auto it = loadedPackages.find(packageId);
    return (it != loadedPackages.end()) ? it->second.get() : nullptr;
}

std::vector<const Package*> PackageManager::getAllPackages() const {
    std::vector<const Package*> packages;
    packages.reserve(loadedPackages.size());
    
    for (const auto& [id, package] : loadedPackages) {
        packages.push_back(package.get());
    }
    
    return packages;
}

bool PackageManager::isPackageLoaded(const std::string& packageId) const {
    return loadedPackages.find(packageId) != loadedPackages.end();
}

std::vector<std::string> PackageManager::getLoadOrder(const std::vector<std::string>& packageIds) const {
    std::unordered_map<std::string, std::vector<std::string>> dependencyGraph;
    buildDependencyGraph(packageIds, dependencyGraph);
    
    if (hasCyclicDependencies(packageIds)) {
        return {}; // Return empty if cyclic dependencies detected
    }
    
    return topologicalSort(dependencyGraph);
}

bool PackageManager::validateDependencies(const Package& package) const {
    for (const auto& dep : package.metadata.dependencies) {
        if (dep.required && !isPackageLoaded(dep.packageId)) {
            return false;
        }
    }
    return true;
}

std::vector<std::string> PackageManager::getMissingDependencies(const Package& package) const {
    std::vector<std::string> missing;
    
    for (const auto& dep : package.metadata.dependencies) {
        if (!isPackageLoaded(dep.packageId)) {
            missing.push_back(dep.packageId);
        }
    }
    
    return missing;
}

std::optional<AssetId> PackageManager::resolveAssetReference(const std::string& packageId, 
                                                           const std::string& assetRef) const {
    const auto* package = getPackage(packageId);
    if (!package) {
        return std::nullopt;
    }
    
    // Check if asset exists in the package
    const auto* asset = package->findAsset(assetRef);
    if (asset) {
        return AssetIdGenerator::generateAssetId(packageId, assetRef);
    }
    
    // Asset not found in specified package
    return std::nullopt;
}

const Package* PackageManager::findPackageContainingAsset(AssetId assetId) const {
    // This would need a reverse lookup table for efficiency in a real implementation
    for (const auto& [id, package] : loadedPackages) {
        for (const auto& asset : package->assets) {
            AssetId generatedId = AssetIdGenerator::generateAssetId(id, asset.id);
            if (generatedId == assetId) {
                return package.get();
            }
        }
    }
    return nullptr;
}

std::vector<std::string> PackageManager::findPackageFiles(const std::string& directory) const {
    std::vector<std::string> packagePaths;
    
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
            if (entry.is_regular_file() && entry.path().filename() == "package.xml") {
                packagePaths.push_back(entry.path().string());
            }
        }
    } catch (const std::exception&) {
        // Directory iteration failed - return empty list
    }
    
    return packagePaths;
}

bool PackageManager::hasCyclicDependencies(const std::vector<std::string>& packageIds) const {
    std::unordered_map<std::string, std::vector<std::string>> graph;
    buildDependencyGraph(packageIds, graph);
    
    std::unordered_set<std::string> visiting;
    std::unordered_set<std::string> visited;
    
    std::function<bool(const std::string&)> hasCycle = [&](const std::string& node) -> bool {
        if (visiting.count(node)) {
            return true; // Back edge found - cycle detected
        }
        if (visited.count(node)) {
            return false; // Already processed
        }
        
        visiting.insert(node);
        
        auto it = graph.find(node);
        if (it != graph.end()) {
            for (const auto& neighbor : it->second) {
                if (hasCycle(neighbor)) {
                    return true;
                }
            }
        }
        
        visiting.erase(node);
        visited.insert(node);
        return false;
    };
    
    for (const auto& packageId : packageIds) {
        if (!visited.count(packageId)) {
            if (hasCycle(packageId)) {
                return true;
            }
        }
    }
    
    return false;
}

void PackageManager::buildDependencyGraph(const std::vector<std::string>& packageIds,
                                        std::unordered_map<std::string, std::vector<std::string>>& graph) const {
    for (const auto& packageId : packageIds) {
        const auto* package = getPackage(packageId);
        if (package) {
            graph[packageId] = {};
            for (const auto& dep : package->metadata.dependencies) {
                if (std::find(packageIds.begin(), packageIds.end(), dep.packageId) != packageIds.end()) {
                    graph[packageId].push_back(dep.packageId);
                }
            }
        }
    }
}

std::vector<std::string> PackageManager::topologicalSort(const std::unordered_map<std::string, 
                                                        std::vector<std::string>>& graph) const {
    std::vector<std::string> result;
    std::unordered_map<std::string, int> inDegree;
    
    // Calculate in-degrees
    for (const auto& [node, neighbors] : graph) {
        if (inDegree.find(node) == inDegree.end()) {
            inDegree[node] = 0;
        }
        for (const auto& neighbor : neighbors) {
            inDegree[neighbor]++;
        }
    }
    
    // Find nodes with no incoming edges
    std::queue<std::string> queue;
    for (const auto& [node, degree] : inDegree) {
        if (degree == 0) {
            queue.push(node);
        }
    }
    
    // Process nodes
    while (!queue.empty()) {
        std::string current = queue.front();
        queue.pop();
        result.push_back(current);
        
        auto it = graph.find(current);
        if (it != graph.end()) {
            for (const auto& neighbor : it->second) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    queue.push(neighbor);
                }
            }
        }
    }
    
    return result;
}

} // namespace Assets
