#!/usr/bin/env pwsh
# build.ps1 - Unified build script for FPV Flight Simulator
# Always performs clean build to ensure consistency

param(
    [switch]$r,         # Release build (default is debug)
    [switch]$verbose,   # Verbose output
    [switch]$help       # Show help
)

if ($help) {
    Write-Host "=================================" -ForegroundColor Cyan
    Write-Host " FPV Flight Simulator Build " -ForegroundColor Cyan
    Write-Host "=================================" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Always performs clean build for consistency" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Usage:" -ForegroundColor White
    Write-Host "  .\build.ps1          - Clean build debug version"
    Write-Host "  .\build.ps1 -r       - Clean build release version"  
    Write-Host "  .\build.ps1 -verbose - Show detailed build output"
    Write-Host "  .\build.ps1 -help    - Show this help"
    Write-Host ""
    Write-Host "Examples:" -ForegroundColor Green
    Write-Host "  .\build.ps1          # Clean build debug"
    Write-Host "  .\build.ps1 -r       # Clean build release"
    Write-Host "  .\build.ps1 -verbose # Verbose debug build"
    return
}

# Determine build configuration
if ($r) {
    $buildType = "Release"
    $buildDir = "build-release"
} else {
    $buildType = "Debug"
    $buildDir = "build-debug"
}

Write-Host "==========================================" -ForegroundColor Cyan
Write-Host " FPV Flight Simulator - Clean Build " -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Build Configuration:" -ForegroundColor White
Write-Host "  Build Type: $buildType" -ForegroundColor Yellow
Write-Host "  Build Directory: $buildDir" -ForegroundColor Yellow
Write-Host "  Verbose: $(if ($verbose) { 'Yes' } else { 'No' })" -ForegroundColor Yellow
Write-Host ""

function Write-Step {
    param($stepNum, $description)
    $timestamp = Get-Date -Format "HH:mm:ss"
    Write-Host "[$timestamp] === STEP $stepNum`: $description ===" -ForegroundColor Green
}

# STEP 1: Stop running processes
Write-Step 1 "Stopping running processes"
$runningProcesses = Get-Process -Name "fpv_fsim" -ErrorAction SilentlyContinue
if ($runningProcesses) {
    $runningProcesses | Stop-Process -Force
    Write-Host "✓ Stopped $($runningProcesses.Count) running fpv_fsim processes" -ForegroundColor Green
} else {
    Write-Host "No running fpv_fsim processes found" -ForegroundColor Gray
}

# STEP 2: Clean build directories
Write-Step 2 "Cleaning build directories"
if (Test-Path $buildDir) {
    Write-Host "Removing build directory ($buildDir)..." -ForegroundColor Yellow
    Remove-Item -Path $buildDir -Recurse -Force
    Write-Host "✓ Successfully removed build directory ($buildDir)" -ForegroundColor Green
}

# Also remove the other build directory to avoid confusion
$otherBuildDir = if ($buildType -eq "Debug") { "build-release" } else { "build-debug" }
if (Test-Path $otherBuildDir) {
    Remove-Item -Path $otherBuildDir -Recurse -Force
    Write-Host "✓ Also removed $otherBuildDir for consistency" -ForegroundColor Green
}

# STEP 3: Clean CMake artifacts
Write-Step 3 "Cleaning CMake artifacts"
@("CMakeCache.txt", "CMakeFiles", "cmake_install.cmake") | ForEach-Object {
    if (Test-Path $_) { Remove-Item -Path $_ -Recurse -Force }
}

# STEP 4: Clean asset caches
Write-Step 4 "Cleaning asset caches"
@("assets/cache", "assets/compiled", "runtime/cache", "build/cache", ".cache", "temp") | ForEach-Object {
    if (Test-Path $_) { Remove-Item -Path $_ -Recurse -Force }
}

# STEP 5: Clean log files
Write-Step 5 "Cleaning log files"
if (Test-Path "logs") {
    Write-Host "Removing log directory..." -ForegroundColor Yellow
    Remove-Item -Path "logs" -Recurse -Force
    Write-Host "✓ Successfully removed log directory" -ForegroundColor Green
}
@("*.log", "source*.txt", "source*.ltxt") | ForEach-Object {
    Get-ChildItem -Path . -Name $_ | Remove-Item -Force
}

# STEP 6: Configure CMake
Write-Step 6 "Configuring CMake"
if (!(Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
    Write-Host "✓ Created build directory: $buildDir" -ForegroundColor Green
}

Set-Location $buildDir

Write-Host "Configuring CMake for $buildType build..." -ForegroundColor Yellow

$cmakeArgs = @(
    ".."
    "-G", "Visual Studio 17 2022"
    "-A", "x64"
    "-DCMAKE_BUILD_TYPE=$buildType"
)

if ($verbose) {
    $cmakeArgs += "--verbose"
}

& cmake @cmakeArgs 2>&1 | Out-Host

if ($LASTEXITCODE -ne 0) {
    Write-Host "❌ CMake configuration failed" -ForegroundColor Red
    Set-Location ..
    exit 1
}

Write-Host "✓ CMake configuration successful" -ForegroundColor Green

# STEP 7: Build project
Write-Step 7 "Building project"
Write-Host "Building $buildType configuration..." -ForegroundColor Yellow

$buildArgs = @(
    "--build", "."
    "--config", $buildType
)

if ($verbose) {
    $buildArgs += "--verbose"
}

& cmake @buildArgs 2>&1 | Out-Host

Set-Location ..

if ($LASTEXITCODE -ne 0) {
    Write-Host "❌ Build failed" -ForegroundColor Red
    exit 1
}

# Determine actual executable path
$exePaths = @(
    "$buildDir\$buildType\fpv_fsim.exe",  # Visual Studio typical path
    "$buildDir\fpv_fsim.exe"              # Alternative path
)

$actualExePath = $null
foreach ($path in $exePaths) {
    if (Test-Path $path) {
        $actualExePath = $path
        break
    }
}

if ($actualExePath) {
    Write-Host "✓ Build successful!" -ForegroundColor Green
    Write-Host "✓ Executable created: $actualExePath" -ForegroundColor Green
} else {
    Write-Host "❌ Build completed but executable not found" -ForegroundColor Red
    Write-Host "Expected locations:" -ForegroundColor Yellow
    $exePaths | ForEach-Object { Write-Host "  $_" -ForegroundColor Gray }
    exit 1
}

Write-Host ""
Write-Host "=========================================" -ForegroundColor Cyan
Write-Host " Build Complete!" -ForegroundColor Cyan
Write-Host "=========================================" -ForegroundColor Cyan
Write-Host "Build Type: $buildType" -ForegroundColor White
Write-Host "Build Directory: $buildDir" -ForegroundColor White
Write-Host "Executable: $actualExePath" -ForegroundColor White
Write-Host ""
Write-Host "To run the application:" -ForegroundColor Yellow
Write-Host "  .\run.ps1" -ForegroundColor Green
