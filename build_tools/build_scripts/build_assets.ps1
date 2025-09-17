#!/usr/bin/env pwsh

# Asset Pipeline Build Script for Windows
# This script builds the asset compiler and codegen tools, then processes assets

param(
    [switch]$Debug,
    [switch]$Clean,
    [switch]$SkipBuild,
    [string]$OutputDir = "runtime/data/packs",
    [string]$AssetsDir = "assets/packages"
)

$ErrorActionPreference = "Stop"

Write-Host "Asset Pipeline Build Script" -ForegroundColor Green
Write-Host "===========================" -ForegroundColor Green

# Determine script directory and project root
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$BuildToolsDir = Split-Path -Parent $ScriptDir
$ProjectRoot = Split-Path -Parent $BuildToolsDir

# Configuration - paths relative to build_tools directory
$BuildDir = Join-Path $BuildToolsDir "build-tools"
$AssetCompilerExe = Join-Path $BuildDir "asset_compiler\Release\asset_compiler.exe"
$CodegenExe = Join-Path $BuildDir "codegen\Release\codegen.exe"
$OutputDir = Join-Path $ProjectRoot $OutputDir
$AssetsDir = Join-Path $ProjectRoot $AssetsDir

# Clean if requested
if ($Clean) {
    Write-Host "Cleaning build directory..." -ForegroundColor Yellow
    if (Test-Path $BuildDir) {
        Remove-Item -Recurse -Force $BuildDir
    }
    if (Test-Path $OutputDir) {
        Remove-Item -Recurse -Force $OutputDir
    }
}

# Build tools if not skipping
if (-not $SkipBuild) {
    Write-Host "Building asset pipeline tools..." -ForegroundColor Yellow
    
    # Create build directory
    if (-not (Test-Path $BuildDir)) {
        New-Item -ItemType Directory -Path $BuildDir | Out-Null
    }
    
    Set-Location $BuildDir
    
    try {
        # Configure CMake
        $CMakeArgs = @(
            $BuildToolsDir
            "-G", "Visual Studio 17 2022"
            "-A", "x64"
        )
        
        if ($Debug) {
            $CMakeArgs += "-DCMAKE_BUILD_TYPE=Debug"
        } else {
            $CMakeArgs += "-DCMAKE_BUILD_TYPE=Release"
        }
        
        Write-Host "Configuring CMake..." -ForegroundColor Cyan
        & cmake @CMakeArgs
        if ($LASTEXITCODE -ne 0) { throw "CMake configuration failed" }
        
        # Build tools
        $BuildConfig = if ($Debug) { "Debug" } else { "Release" }
        Write-Host "Building tools ($BuildConfig)..." -ForegroundColor Cyan
        & cmake --build . --config $BuildConfig --parallel $env:NUMBER_OF_PROCESSORS
        if ($LASTEXITCODE -ne 0) { throw "Build failed" }
        
        # Copy executables to expected locations
        $ConfigDir = "$BuildDir/$BuildConfig"
        if (Test-Path "$ConfigDir/asset_compiler.exe") {
            Copy-Item "$ConfigDir/asset_compiler.exe" "asset_compiler/" -Force
        }
        if (Test-Path "$ConfigDir/codegen.exe") {
            Copy-Item "$ConfigDir/codegen.exe" "codegen/" -Force
        }
    }
    finally {
        Set-Location $ProjectRoot
    }
}

# Check if tools exist
if (-not (Test-Path $AssetCompilerExe)) {
    Write-Error "Asset compiler not found: $AssetCompilerExe"
    exit 1
}

if (-not (Test-Path $CodegenExe)) {
    Write-Error "Codegen tool not found: $CodegenExe"
    exit 1
}

# Create output directory
if (-not (Test-Path $OutputDir)) {
    New-Item -ItemType Directory -Path $OutputDir -Force | Out-Null
}

# Process assets
Write-Host "Processing assets..." -ForegroundColor Yellow

# Generate asset IDs from JSON packages
Write-Host "Generating asset ID mappings..." -ForegroundColor Cyan
$CodegenArgs = @(
    "-o", "src/core/AssetIds.h"
    "assets/packages/core/package.json"
)

& $CodegenExe @CodegenArgs
if ($LASTEXITCODE -ne 0) {
    Write-Error "Asset ID generation failed"
    exit 1
}

# Process each JSON package
$PackageFiles = Get-ChildItem -Path $AssetsDir -Name "package.json" -Recurse

foreach ($PackageFile in $PackageFiles) {
    $FullPath = Join-Path $AssetsDir $PackageFile
    Write-Host "Processing package: $FullPath" -ForegroundColor Cyan
    
    $CompilerArgs = @(
        "-o", $OutputDir
    )
    
    if ($Debug) {
        $CompilerArgs += "-d"
    }
    
    $CompilerArgs += $FullPath
    
    & $AssetCompilerExe @CompilerArgs
    if ($LASTEXITCODE -ne 0) {
        Write-Error "Asset compilation failed for $FullPath"
        exit 1
    }
}

Write-Host "Asset pipeline completed successfully!" -ForegroundColor Green

# Generate JSON mapping for debugging if in debug mode
if ($Debug) {
    Write-Host "Generating debug asset mapping..." -ForegroundColor Cyan
    $DebugArgs = @(
        "-f", "json"
        "-o", "$OutputDir/asset_debug.json"
        $AssetsDir
    )
    
    & $CodegenExe @DebugArgs
    if ($LASTEXITCODE -ne 0) {
        Write-Warning "Debug asset mapping generation failed"
    }
}

Write-Host "All assets processed successfully!" -ForegroundColor Green
