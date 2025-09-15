# AssetHotReloadSystem.h / AssetHotReloadSystem.cpp

## Constructors

- `AssetHotReloadSystem(AssetRegistry &registry, AssetPackLoader &loader)`

  **Summary:** Constructor taking references to asset registry and loader.

## Destructors

- `~AssetHotReloadSystem()`

  **Summary:** Destructor.

## Public Methods

- `void update(World &world, float deltaTime) override`

  **Summary:** Updates the system, checking for file changes and reloading if necessary.

- `void watchPackage(const std::string &packagePath)`

  **Summary:** Adds a package file to the watch list for hot reloading.

- `bool checkForChanges()`

  **Summary:** Checks if any watched files have been modified.

- `void reloadChangedPackages()`

  **Summary:** Reloads packages that have been detected as changed.

## Private Methods

- `std::chrono::system_clock::time_point getFileModifiedTime(const std::string &path)`

  **Summary:** Gets the last modified time of a file.
