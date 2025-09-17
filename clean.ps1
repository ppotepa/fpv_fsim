#!/usr/bin/env pwsh
# clean.ps1 - Script to clean all build artifacts and cache files
# Created on September 17, 2025

# Print header
Write-Host "====================================" -ForegroundColor Cyan
Write-Host " Drone Sim GGL - Clean Build Script " -ForegroundColor Cyan
Write-Host "====================================" -ForegroundColor Cyan
Write-Host ""

# Function to remove a directory if it exists
function Remove-DirectoryIfExists {
    param([string]$path)
    
    if (Test-Path -Path $path) {
        Write-Host "Removing $path..." -ForegroundColor Yellow
        Remove-Item -Path $path -Recurse -Force -ErrorAction SilentlyContinue
        if (-not (Test-Path -Path $path)) {
            Write-Host "✓ Successfully removed $path" -ForegroundColor Green
        }
        else {
            Write-Host "✗ Failed to remove $path" -ForegroundColor Red
        }
    }
}

# Function to remove a file if it exists
function Remove-FileIfExists {
    param([string]$path)
    
    if (Test-Path -Path $path) {
        Write-Host "Removing $path..." -ForegroundColor Yellow
        Remove-Item -Path $path -Force -ErrorAction SilentlyContinue
        if (-not (Test-Path -Path $path)) {
            Write-Host "✓ Successfully removed $path" -ForegroundColor Green
        }
        else {
            Write-Host "✗ Failed to remove $path" -ForegroundColor Red
        }
    }
}

Write-Host "Starting cleanup process..." -ForegroundColor Yellow
Write-Host ""

# Remove main build directories
Write-Host "Removing build directories..." -ForegroundColor Magenta
Remove-DirectoryIfExists "build"
Remove-DirectoryIfExists "build-debug"
Remove-DirectoryIfExists "build-release"

# Remove build artifacts
Write-Host "Removing build artifacts..." -ForegroundColor Magenta
Remove-FileIfExists "build.log"
Remove-FileIfExists "output.log"

# Clean CMake cache and artifacts
Write-Host "Removing CMake files and caches..." -ForegroundColor Magenta
Remove-FileIfExists "CMakeCache.txt"
Remove-DirectoryIfExists "CMakeFiles"

# Clean log files
Write-Host "Removing log files..." -ForegroundColor Magenta
Remove-DirectoryIfExists "log"
Remove-FileIfExists "*.log"

# Remove any Visual Studio Code cache
Write-Host "Cleaning Visual Studio Code cache..." -ForegroundColor Magenta
Remove-DirectoryIfExists ".vscode/.cache"
Remove-DirectoryIfExists ".vscode/.history"

# Clean any test outputs
Write-Host "Removing test outputs..." -ForegroundColor Magenta
Remove-FileIfExists "tests/*.out"
Remove-FileIfExists "tests/*.log"

# Remove temp files
Write-Host "Removing temporary files..." -ForegroundColor Magenta
Remove-FileIfExists "*.tmp"
Remove-FileIfExists "*.temp"
Remove-FileIfExists "tmp*"

# Clean asset caches
Write-Host "Cleaning asset caches..." -ForegroundColor Magenta
$cacheDirs = @(
    "runtime\data\cache",
    "runtime\data\compiled",
    "assets\build",
    "assets\cache",
    ".cache"
)

foreach ($dir in $cacheDirs) {
    Remove-DirectoryIfExists $dir
}

# Clean specific asset cache files
$cacheFiles = @(
    "*.asset.cache",
    "*.compiled",
    "*.cache",
    "runtime\data\*.cache"
)

foreach ($pattern in $cacheFiles) {
    $files = Get-ChildItem -Path . -Name $pattern -Recurse -ErrorAction SilentlyContinue
    foreach ($file in $files) {
        Write-Host "Removing cache file: $file..." -ForegroundColor Yellow
        Remove-Item $file -Force
        Write-Host "✓ Cache file removed" -ForegroundColor Green
    }
}

# Remove the contents of runtime/data (but keep the directory structure)
Write-Host "Cleaning runtime data..." -ForegroundColor Magenta
if (Test-Path -Path "runtime/data") {
    Get-ChildItem -Path "runtime/data" -Recurse -File | Remove-Item -Force
    Write-Host "✓ Runtime data cleaned" -ForegroundColor Green
}

Write-Host ""
Write-Host "====================================" -ForegroundColor Cyan
Write-Host " Cleanup complete!" -ForegroundColor Green
Write-Host "====================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "To rebuild the project, run:"
Write-Host "  .\build.ps1" -ForegroundColor Yellow
Write-Host ""
