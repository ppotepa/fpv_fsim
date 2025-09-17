# Build Scripts Documentation

This document describes the various build scripts available for the FPV Flight Simulator project.

## 📁 Available Scripts

### 🔨 `build.ps1` - Standard Build Script
**Purpose**: Builds the project in debug or release mode without cleaning.

**Usage**:
```powershell
.\build.ps1          # Build debug version
.\build.ps1 -r       # Build release version  
.\build.ps1 -clean   # Clean build directories only
.\build.ps1 -help    # Show help
```

**Features**:
- Fast incremental builds
- Preserves cached assets and logs
- Good for regular development

---

### 🧹 `clean.ps1` - Cleanup Script
**Purpose**: Removes all build artifacts, caches, and temporary files without rebuilding.

**Usage**:
```powershell
.\clean.ps1          # Clean everything
```

**What it cleans**:
- Build directories (build, build-debug, build-release)
- CMake cache files
- Asset caches
- Log files
- Temporary files
- Runtime data caches

---

### 🚀 `build-clean.ps1` - Full Clean Build Script
**Purpose**: Performs a complete cleanup followed by a fresh build.

**Usage**:
```powershell
.\build-clean.ps1          # Clean build debug version
.\build-clean.ps1 -r       # Clean build release version
.\build-clean.ps1 -verbose # Show detailed output
.\build-clean.ps1 -help    # Show help
```

**Process**:
1. ✅ Stops any running fpv_fsim processes
2. ✅ Removes all build directories
3. ✅ Cleans all cached assets
4. ✅ Removes log files and temporary files
5. ✅ Cleans Visual Studio artifacts
6. ✅ Cleans runtime data caches
7. ✅ Performs fresh CMake configuration
8. ✅ Builds the project from scratch

**Features**:
- Timestamped logging
- Comprehensive cleanup
- Automatic process termination
- Verbose mode for debugging
- Success/failure reporting

---

### 🏃 `run.ps1` - Run Script
**Purpose**: Runs the built application.

**Usage**:
```powershell
.\run.ps1            # Run the application
```

---

## 🎯 When to Use Each Script

### Use `build.ps1` when:
- ✅ Making code changes during development
- ✅ You want fast incremental builds
- ✅ Asset caches are valid and helpful

### Use `clean.ps1` when:
- ✅ You need to free up disk space
- ✅ You want to clean without rebuilding
- ✅ Preparing for a fresh build later

### Use `build-clean.ps1` when:
- ✅ **Build issues or errors** occur
- ✅ **Asset caches are corrupted** or outdated
- ✅ **Major changes** to build configuration
- ✅ **CI/CD pipelines** need consistent builds
- ✅ **Package JSON structure changes** (like our XML→JSON transition)
- ✅ **CMake configuration changes**
- ✅ **Starting fresh** after switching branches
- ✅ **Before important demos** or releases

---

## 🔧 Technical Details

### Build Directories Created:
- `build-debug/` - Debug build artifacts
- `build-release/` - Release build artifacts
- `build-json/` - Legacy build directory (cleaned)

### Cleaned Locations:
```
build*/                    # All build directories
log/                       # Application logs
runtime/data/cache/        # Runtime asset caches  
assets/cache/              # Asset compilation caches
*.cache, *.tmp, *.temp     # Temporary files
CMakeCache.txt             # CMake configuration cache
.vs/, .vscode/.cache/      # IDE caches
```

### Executables:
- Debug: `build-debug/fpv_fsim.exe`
- Release: `build-release/fpv_fsim.exe`

---

## 🚨 Troubleshooting

### If build-clean.ps1 fails:
1. Check if you have admin permissions
2. Ensure no antivirus is blocking file operations
3. Run with `-verbose` flag to see detailed output
4. Manually stop any fpv_fsim processes

### If assets don't load:
1. Run `.\build-clean.ps1` to clear all caches
2. Check that package JSON files are valid
3. Verify working directory is correct

### If CMake fails:
1. Ensure CMake is installed and in PATH
2. Check for missing dependencies
3. Try deleting CMakeCache.txt manually

---

## 📊 Performance Comparison

| Script | Time | Use Case |
|--------|------|----------|
| `build.ps1` | ~10-30s | Development |
| `build-clean.ps1` | ~30-60s | Clean slate |
| `clean.ps1` | ~5-10s | Cleanup only |

---

*Created: September 17, 2025*  
*Project: FPV Flight Simulator*  
*Author: Build System Team*
