#!/bin/bash

# Asset Pipeline Build Script for Linux/macOS
# This script builds the asset compiler and codegen tools, then processes assets

set -e

# Default values
DEBUG=false
CLEAN=false
SKIP_BUILD=false
OUTPUT_DIR="runtime/data/packs"
ASSETS_DIR="assets/packages"

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --debug)
            DEBUG=true
            shift
            ;;
        --clean)
            CLEAN=true
            shift
            ;;
        --skip-build)
            SKIP_BUILD=true
            shift
            ;;
        --output-dir)
            OUTPUT_DIR="$2"
            shift 2
            ;;
        --assets-dir)
            ASSETS_DIR="$2"
            shift 2
            ;;
        -h|--help)
            echo "Usage: $0 [options]"
            echo "Options:"
            echo "  --debug          Build in debug mode"
            echo "  --clean          Clean build directory"
            echo "  --skip-build     Skip building tools"
            echo "  --output-dir     Output directory for compiled assets"
            echo "  --assets-dir     Assets source directory"
            echo "  -h, --help       Show this help"
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

echo "Asset Pipeline Build Script"
echo "==========================="

# Configuration
BUILD_DIR="build-tools"
ASSET_COMPILER_EXE="$BUILD_DIR/asset_compiler/asset_compiler"
CODEGEN_EXE="$BUILD_DIR/codegen/codegen"

# Clean if requested
if [ "$CLEAN" = true ]; then
    echo "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
    rm -rf "$OUTPUT_DIR"
fi

# Build tools if not skipping
if [ "$SKIP_BUILD" = false ]; then
    echo "Building asset pipeline tools..."
    
    # Create build directory
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    
    # Configure CMake
    CMAKE_ARGS=(
        ".."
        "-G" "Unix Makefiles"
    )
    
    if [ "$DEBUG" = true ]; then
        CMAKE_ARGS+=("-DCMAKE_BUILD_TYPE=Debug")
    else
        CMAKE_ARGS+=("-DCMAKE_BUILD_TYPE=Release")
    fi
    
    echo "Configuring CMake..."
    cmake "${CMAKE_ARGS[@]}"
    
    # Build tools
    echo "Building tools..."
    make -j$(nproc)
    
    cd ..
fi

# Check if tools exist
if [ ! -f "$ASSET_COMPILER_EXE" ]; then
    echo "Error: Asset compiler not found: $ASSET_COMPILER_EXE"
    exit 1
fi

if [ ! -f "$CODEGEN_EXE" ]; then
    echo "Error: Codegen tool not found: $CODEGEN_EXE"
    exit 1
fi

# Create output directory
mkdir -p "$OUTPUT_DIR"

# Process assets
echo "Processing assets..."

# Generate asset IDs
echo "Generating asset ID mappings..."
CODEGEN_ARGS=(
    "-f" "header"
    "-o" "src/core/AssetIds.h"
    "-n" "Assets"
    "$ASSETS_DIR"
)

"$CODEGEN_EXE" "${CODEGEN_ARGS[@]}"

# Process each package
find "$ASSETS_DIR" -name "package.xml" -type f | while read -r PACKAGE_FILE; do
    echo "Processing package: $PACKAGE_FILE"
    
    COMPILER_ARGS=(
        "-o" "$OUTPUT_DIR"
    )
    
    if [ "$DEBUG" = true ]; then
        COMPILER_ARGS+=("-d")
    fi
    
    COMPILER_ARGS+=("$PACKAGE_FILE")
    
    "$ASSET_COMPILER_EXE" "${COMPILER_ARGS[@]}"
done

echo "Asset pipeline completed successfully!"

# Generate JSON mapping for debugging if in debug mode
if [ "$DEBUG" = true ]; then
    echo "Generating debug asset mapping..."
    DEBUG_ARGS=(
        "-f" "json"
        "-o" "$OUTPUT_DIR/asset_debug.json"
        "$ASSETS_DIR"
    )
    
    "$CODEGEN_EXE" "${DEBUG_ARGS[@]}" || echo "Warning: Debug asset mapping generation failed"
fi

echo "All assets processed successfully!"
