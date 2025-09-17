#!/usr/bin/env pwsh
# run_simple_test.ps1 - Script to build and run the simple scene test
# Created on September 17, 2025

# Print header
Write-Host "====================================" -ForegroundColor Cyan
Write-Host " Running Simple Scene Renderer Test " -ForegroundColor Cyan
Write-Host "====================================" -ForegroundColor Cyan
Write-Host ""

# Set environment variables for MinGW
$env:PATH = "C:\msys64\mingw64\bin;$env:PATH"

# Build the test
Write-Host "Building simple_scene_test..." -ForegroundColor Yellow

$buildCommand = 'g++ -std=c++17 -o tests/simple_scene_test.exe tests/simple_scene_test.cpp -I.'
Write-Host "Command: $buildCommand" -ForegroundColor Gray
Invoke-Expression $buildCommand

if ($LASTEXITCODE -ne 0) {
    Write-Host "❌ Build failed!" -ForegroundColor Red
    exit $LASTEXITCODE
}

Write-Host "✅ Build successful!" -ForegroundColor Green
Write-Host ""

# Run the test
Write-Host "Running simple_scene_test..." -ForegroundColor Yellow
Write-Host ""

$runCommand = './tests/simple_scene_test.exe'
Invoke-Expression $runCommand

if ($LASTEXITCODE -ne 0) {
    Write-Host ""
    Write-Host "❌ Test failed!" -ForegroundColor Red
    exit $LASTEXITCODE
}

Write-Host ""
Write-Host "✅ All tests passed!" -ForegroundColor Green
Write-Host ""
