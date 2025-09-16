#include "IoContainer.h"
#include <algorithm>

namespace Core {

IoContainer::IoContainer() : parent(nullptr) {}

IoContainer::IoContainer(IoContainer* parentContainer) : parent(parentContainer) {}

IoContainer::~IoContainer() = default;

void IoContainer::clear() {
    registrations.clear();
}

std::unique_ptr<IoContainer> IoContainer::createChild() {
    return std::unique_ptr<IoContainer>(new IoContainer(this));
}

std::vector<std::string> IoContainer::getRegisteredTypes() const {
    std::vector<std::string> types;
    types.reserve(registrations.size());
    
    for (const auto& [key, reg] : registrations) {
        types.push_back(reg.typeName);
    }
    
    // Include parent types if we have a parent
    if (parent) {
        auto parentTypes = parent->getRegisteredTypes();
        types.insert(types.end(), parentTypes.begin(), parentTypes.end());
    }
    
    // Remove duplicates
    std::sort(types.begin(), types.end());
    types.erase(std::unique(types.begin(), types.end()), types.end());
    
    return types;
}

IoContainer::Registration* IoContainer::findRegistration(const std::string& key) {
    auto it = registrations.find(key);
    if (it != registrations.end()) {
        return &it->second;
    }
    
    // Check parent if not found locally
    if (parent) {
        return parent->findRegistration(key);
    }
    
    return nullptr;
}

} // namespace Core
