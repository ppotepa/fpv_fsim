#!/usr/bin/env pwsh
# build-clean.ps1 - Full clean build script for FPV Flight Simulator
# Created on September 17, 2025
# This script performs a complete cleanup and rebuild

param(
    [switch]$r,         # Release build (default is debug)
    [switch]$verbose,   # Verbose output
    [switch]$help       # Show help
)

if ($help) {
    Write-Host "=================================" -ForegroundColor Cyan
    Write-Host " FPV Flight Simulator Build-Clean " -ForegroundColor Cyan
    Write-Host "=================================" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "This script performs a complete clean build:" -ForegroundColor Yellow
    Write-Host "  1. Stops any running fpv_fsim processes"
    Write-Host "  2. Removes all build directories"
    Write-Host "  3. Cleans all cached assets"
    Write-Host "  4. Removes log files"
    Write-Host "  5. Performs a fresh CMake configuration"
    Write-Host "  6. Builds the project from scratch"
    Write-Host ""
    Write-Host "Usage:" -ForegroundColor Green
    Write-Host "  .\build-clean.ps1          - Clean build debug version"
    Write-Host "  .\build-clean.ps1 -r       - Clean build release version"
    Write-Host "  .\build-clean.ps1 -verbose - Show detailed output"
    Write-Host "  .\build-clean.ps1 -help    - Show this help"
    Write-Host ""
    Write-Host "Examples:" -ForegroundColor Magenta
    Write-Host "  .\build-clean.ps1           # Clean debug build"
    Write-Host "  .\build-clean.ps1 -r        # Clean release build"
    Write-Host "  .\build-clean.ps1 -r -verbose # Verbose clean release build"
    Write-Host ""
    return
}

# Header
Write-Host "=========================================" -ForegroundColor Cyan
Write-Host " FPV Flight Simulator - Full Clean Build " -ForegroundColor Cyan
Write-Host "=========================================" -ForegroundColor Cyan
Write-Host ""

$buildType = if ($r) { "Release" } else { "Debug" }
$buildDir = if ($r) { "build-release" } else { "build-debug" }

Write-Host "Build Configuration:" -ForegroundColor Yellow
Write-Host "  Build Type: $buildType"
Write-Host "  Build Directory: $buildDir"
Write-Host "  Verbose: $($verbose ? 'Yes' : 'No')"
Write-Host ""

# Function to log with timestamp
function Write-TimestampedLog {
    param([string]$message, [string]$color = "White")
    $timestamp = Get-Date -Format "HH:mm:ss"
    Write-Host "[$timestamp] $message" -ForegroundColor $color
}

# Function to remove directory safely
function Remove-DirectorySafely {
    param([string]$path, [string]$description)
    
    if (Test-Path -Path $path) {
        Write-TimestampedLog "Removing $description..." "Yellow"
        try {
            Remove-Item -Path $path -Recurse -Force -ErrorAction Stop
            Write-TimestampedLog "✓ Successfully removed $description" "Green"
        }
        catch {
            Write-TimestampedLog "✗ Failed to remove $description`: $_" "Red"
            return $false
        }
    }
    else {
        if ($verbose) {
            Write-TimestampedLog "$description not found (already clean)" "Gray"
        }
    }
    return $true
}

# Function to remove file safely
function Remove-FileSafely {
    param([string]$path, [string]$description)
    
    if (Test-Path -Path $path) {
        Write-TimestampedLog "Removing $description..." "Yellow"
        try {
            Remove-Item -Path $path -Force -ErrorAction Stop
            Write-TimestampedLog "✓ Successfully removed $description" "Green"
        }
        catch {
            Write-TimestampedLog "✗ Failed to remove $description`: $_" "Red"
            return $false
        }
    }
    else {
        if ($verbose) {
            Write-TimestampedLog "$description not found (already clean)" "Gray"
        }
    }
    return $true
}

# Step 1: Stop any running processes
Write-TimestampedLog "=== STEP 1: Stopping running processes ===" "Cyan"
try {
    $processes = Get-Process fpv_fsim -ErrorAction SilentlyContinue
    if ($processes) {
        Write-TimestampedLog "Found $($processes.Count) running fpv_fsim process(es)" "Yellow"
        Stop-Process -Name fpv_fsim -Force -ErrorAction SilentlyContinue
        Start-Sleep -Seconds 2
        Write-TimestampedLog "✓ Stopped fpv_fsim processes" "Green"
    }
    else {
        Write-TimestampedLog "No running fpv_fsim processes found" "Gray"
    }
}
catch {
    Write-TimestampedLog "Error stopping processes: $_" "Red"
}

# Step 2: Clean build directories
Write-TimestampedLog "=== STEP 2: Cleaning build directories ===" "Cyan"
$buildDirs = @("build", "build-debug", "build-release", "build-json")
foreach ($dir in $buildDirs) {
    Remove-DirectorySafely $dir "build directory ($dir)"
}

# Step 3: Clean CMake artifacts
Write-TimestampedLog "=== STEP 3: Cleaning CMake artifacts ===" "Cyan"
Remove-FileSafely "CMakeCache.txt" "CMake cache"
Remove-DirectorySafely "CMakeFiles" "CMake files directory"

# Step 4: Clean asset caches
Write-TimestampedLog "=== STEP 4: Cleaning asset caches ===" "Cyan"
$assetCacheDirs = @(
    "runtime\data\cache",
    "runtime\data\compiled", 
    "assets\cache",
    "assets\build",
    "internal_assets\cache",
    ".cache"
)

foreach ($dir in $assetCacheDirs) {
    Remove-DirectorySafely $dir "asset cache ($dir)"
}

# Clean asset cache files
$assetCachePatterns = @("*.asset.cache", "*.compiled", "*.cache")
foreach ($pattern in $assetCachePatterns) {
    $files = Get-ChildItem -Path . -Name $pattern -Recurse -ErrorAction SilentlyContinue
    foreach ($file in $files) {
        Remove-FileSafely $file "cache file ($file)"
    }
}

# Step 5: Clean log files
Write-TimestampedLog "=== STEP 5: Cleaning log files ===" "Cyan"
Remove-DirectorySafely "log" "log directory"
$logFiles = @("*.log", "output*.txt", "run_output*.txt", "build.log")
foreach ($pattern in $logFiles) {
    $files = Get-ChildItem -Path . -Name $pattern -ErrorAction SilentlyContinue
    foreach ($file in $files) {
        Remove-FileSafely $file "log file ($file)"
    }
}

# Step 6: Clean temporary files
Write-TimestampedLog "=== STEP 6: Cleaning temporary files ===" "Cyan"
$tempPatterns = @("*.tmp", "*.temp", "tmp*", "~*")
foreach ($pattern in $tempPatterns) {
    $files = Get-ChildItem -Path . -Name $pattern -Recurse -ErrorAction SilentlyContinue
    foreach ($file in $files) {
        Remove-FileSafely $file "temporary file ($file)"
    }
}

# Step 7: Clean Visual Studio artifacts
Write-TimestampedLog "=== STEP 7: Cleaning Visual Studio artifacts ===" "Cyan"
$vsDirs = @(".vs", ".vscode\.cache", ".vscode\.history")
foreach ($dir in $vsDirs) {
    Remove-DirectorySafely $dir "Visual Studio cache ($dir)"
}

# Step 8: Clean runtime data (preserve structure)
Write-TimestampedLog "=== STEP 8: Cleaning runtime data ===" "Cyan"
if (Test-Path -Path "runtime/data") {
    $runtimeFiles = Get-ChildItem -Path "runtime/data" -Recurse -File -ErrorAction SilentlyContinue
    if ($runtimeFiles) {
        Write-TimestampedLog "Cleaning $($runtimeFiles.Count) runtime data files..." "Yellow"
        $runtimeFiles | Remove-Item -Force -ErrorAction SilentlyContinue
        Write-TimestampedLog "✓ Runtime data cleaned" "Green"
    }
}

# Step 9: Create build directory and configure
Write-TimestampedLog "=== STEP 9: Configuring CMake ===" "Cyan"
try {
    if (-not (Test-Path $buildDir)) {
        New-Item -ItemType Directory -Path $buildDir -Force | Out-Null
        Write-TimestampedLog "✓ Created build directory: $buildDir" "Green"
    }
    
    Set-Location $buildDir
    Write-TimestampedLog "Configuring CMake for $buildType build..." "Yellow"
    
    $cmakeArgs = @(
        "..",
        "-DCMAKE_BUILD_TYPE=$buildType"
    )
    
    if ($verbose) {
        & cmake @cmakeArgs
    }
    else {
        & cmake @cmakeArgs 2>&1 | Out-Null
    }
    
    if ($LASTEXITCODE -eq 0) {
        Write-TimestampedLog "✓ CMake configuration successful" "Green"
    }
    else {
        Write-TimestampedLog "✗ CMake configuration failed with exit code $LASTEXITCODE" "Red"
        Set-Location ..
        exit 1
    }
}
catch {
    Write-TimestampedLog "✗ CMake configuration error: $_" "Red"
    Set-Location ..
    exit 1
}

# Step 10: Build the project
Write-TimestampedLog "=== STEP 10: Building project ===" "Cyan"
try {
    Write-TimestampedLog "Building $buildType configuration..." "Yellow"
    
    if ($verbose) {
        & cmake --build . --config $buildType
    }
    else {
        $buildOutput = & cmake --build . --config $buildType 2>&1
        if ($LASTEXITCODE -ne 0) {
            Write-Host $buildOutput
        }
    }
    
    if ($LASTEXITCODE -eq 0) {
        Write-TimestampedLog "✓ Build successful!" "Green"
        
        # Find the executable
        $exe = Get-ChildItem -Path . -Name "fpv_fsim.exe" -Recurse -ErrorAction SilentlyContinue | Select-Object -First 1
        
        if ($exe) {
            Write-TimestampedLog "✓ Executable created: $exe" "Green"
        }
    }
    else {
        Write-TimestampedLog "✗ Build failed with exit code $LASTEXITCODE" "Red"
        Set-Location ..
        exit 1
    }
}
catch {
    Write-TimestampedLog "✗ Build error: $_" "Red"
    Set-Location ..
    exit 1
}

Set-Location ..

# Final summary
Write-Host ""
Write-TimestampedLog "=========================================" "Cyan"
Write-TimestampedLog " Clean Build Complete!" "Green"
Write-TimestampedLog "=========================================" "Cyan"
Write-TimestampedLog "Build Type: $buildType" "Yellow"
Write-TimestampedLog "Build Directory: $buildDir" "Yellow"
Write-TimestampedLog "Executable: $buildDir/fpv_fsim.exe" "Yellow"
Write-Host ""
Write-TimestampedLog "To run the application:" "Cyan"
Write-TimestampedLog "  .\run.ps1" "Green"
Write-Host ""
