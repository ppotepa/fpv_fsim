#!/usr/bin/env pwsh
# run.ps1 - Unified run script for FPV Flight Simulator
# Intelligently finds and runs the built executable

param(
    [switch]$d,         # Force debug version
    [switch]$r,         # Force release version
    [switch]$rebuild,   # Rebuild before running
    [switch]$help,      # Show help
    [string[]]$args     # Pass-through arguments to executable
)

if ($help) {
    Write-Host "=================================" -ForegroundColor Cyan
    Write-Host " FPV Flight Simulator Run " -ForegroundColor Cyan
    Write-Host "=================================" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Usage:" -ForegroundColor White
    Write-Host "  .\run.ps1              - Run most recent build"
    Write-Host "  .\run.ps1 -d           - Force run debug version"
    Write-Host "  .\run.ps1 -r           - Force run release version"
    Write-Host "  .\run.ps1 -rebuild     - Rebuild then run"
    Write-Host "  .\run.ps1 -help        - Show this help"
    Write-Host ""
    Write-Host "Examples:" -ForegroundColor Green
    Write-Host "  .\run.ps1              # Run latest build"
    Write-Host "  .\run.ps1 -d           # Run debug build"
    Write-Host "  .\run.ps1 -r           # Run release build"
    Write-Host "  .\run.ps1 -rebuild     # Clean build then run"
    return
}

# Rebuild if requested
if ($rebuild) {
    Write-Host "Rebuilding before run..." -ForegroundColor Yellow
    if ($r) {
        & .\build.ps1 -r
    } else {
        & .\build.ps1
    }
    if ($LASTEXITCODE -ne 0) {
        Write-Host "❌ Build failed, cannot run" -ForegroundColor Red
        exit 1
    }
}

# Define possible executable locations
$possibleBuilds = @()

if ($d) {
    # Force debug
    $possibleBuilds += @{
        Type = "Debug"
        Paths = @(
            "build-debug\Debug\fpv_fsim.exe",
            "build-debug\fpv_fsim.exe"
        )
    }
} elseif ($r) {
    # Force release
    $possibleBuilds += @{
        Type = "Release"
        Paths = @(
            "build-release\Release\fpv_fsim.exe",
            "build-release\fpv_fsim.exe"
        )
    }
} else {
    # Auto-detect: prefer most recent build
    $possibleBuilds += @{
        Type = "Debug"
        Paths = @(
            "build-debug\Debug\fpv_fsim.exe",
            "build-debug\fpv_fsim.exe"
        )
    }
    $possibleBuilds += @{
        Type = "Release"
        Paths = @(
            "build-release\Release\fpv_fsim.exe",
            "build-release\fpv_fsim.exe"
        )
    }
}

# Find executable
$foundExe = $null
$foundType = $null

Write-Host "Searching for executable..." -ForegroundColor Yellow

foreach ($build in $possibleBuilds) {
    foreach ($path in $build.Paths) {
        if (Test-Path $path) {
            $foundExe = $path
            $foundType = $build.Type
            break
        }
    }
    if ($foundExe) { break }
}

if (-not $foundExe) {
    Write-Host "❌ No executable found!" -ForegroundColor Red
    Write-Host ""
    Write-Host "Searched locations:" -ForegroundColor Yellow
    foreach ($build in $possibleBuilds) {
        Write-Host "  $($build.Type):" -ForegroundColor White
        foreach ($path in $build.Paths) {
            Write-Host "    $path" -ForegroundColor Gray
        }
    }
    Write-Host ""
    Write-Host "To build the project first:" -ForegroundColor Yellow
    Write-Host "  .\build.ps1              # Build debug"
    Write-Host "  .\build.ps1 -r           # Build release"
    exit 1
}

Write-Host "✓ Found executable: $foundExe ($foundType)" -ForegroundColor Green

# Check if executable is current
$exeLastWrite = (Get-Item $foundExe).LastWriteTime
$sourceLastWrite = (Get-ChildItem -Path "src" -Recurse -Include "*.cpp","*.h" | Sort-Object LastWriteTime -Descending | Select-Object -First 1).LastWriteTime

if ($sourceLastWrite -gt $exeLastWrite) {
    Write-Host "⚠️  Warning: Source files are newer than executable" -ForegroundColor Yellow
    Write-Host "   Consider rebuilding with: .\run.ps1 -rebuild" -ForegroundColor Yellow
}

# Run the executable
Write-Host ""
Write-Host "=========================================" -ForegroundColor Cyan
Write-Host " Running FPV Flight Simulator " -ForegroundColor Cyan
Write-Host "=========================================" -ForegroundColor Cyan
Write-Host "Executable: $foundExe" -ForegroundColor White
Write-Host "Build Type: $foundType" -ForegroundColor White
Write-Host "Working Directory: $(Get-Location)" -ForegroundColor White

if ($args) {
    Write-Host "Arguments: $($args -join ' ')" -ForegroundColor White
}

Write-Host ""
Write-Host "Starting application..." -ForegroundColor Green
Write-Host "Press Ctrl+C to stop" -ForegroundColor Gray
Write-Host ""

# Execute with proper error handling
try {
    if ($args) {
        & $foundExe @args
    } else {
        & $foundExe
    }
    
    $exitCode = $LASTEXITCODE
    Write-Host ""
    
    if ($exitCode -eq 0) {
        Write-Host "✓ Application exited successfully" -ForegroundColor Green
    } else {
        Write-Host "❌ Application exited with code: $exitCode" -ForegroundColor Red
    }
    
    exit $exitCode
    
} catch {
    Write-Host ""
    Write-Host "❌ Error running application:" -ForegroundColor Red
    Write-Host $_.Exception.Message -ForegroundColor Red
    exit 1
}
