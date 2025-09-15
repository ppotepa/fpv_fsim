#!/usr/bin/env pwsh

# Demo script to showcase the asset-scene-compiler pipeline
# This script demonstrates both debug and release modes

param(
    [switch]$Debug,
    [switch]$Release,
    [switch]$Demo
)

$ErrorActionPreference = "Stop"

Write-Host "FPV Flight Simulator - Asset Pipeline Demo" -ForegroundColor Green
Write-Host "==========================================" -ForegroundColor Green
Write-Host ""

if (-not $Debug -and -not $Release -and -not $Demo) {
    Write-Host "Usage: .\demo_pipeline.ps1 [-Debug] [-Release] [-Demo]" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Options:" -ForegroundColor Cyan
    Write-Host "  -Debug    : Run debug mode (hot-reloading, XML sources)" -ForegroundColor White
    Write-Host "  -Release  : Run release mode (binary packs, optimized)" -ForegroundColor White
    Write-Host "  -Demo     : Run both modes for comparison" -ForegroundColor White
    Write-Host ""
    Write-Host "Example: .\demo_pipeline.ps1 -Debug" -ForegroundColor Yellow
    exit 0
}

# Check if build tools exist
$AssetCompilerPath = "build_tools\asset_compiler\asset_compiler.exe"
$CodegenPath = "build_tools\codegen\codegen.exe"

if (-not (Test-Path $AssetCompilerPath) -or -not (Test-Path $CodegenPath)) {
    Write-Host "Build tools not found. Building..." -ForegroundColor Yellow
    & "build_tools\build_scripts\build_assets.ps1"
    if ($LASTEXITCODE -ne 0) {
        Write-Error "Failed to build asset pipeline tools"
        exit 1
    }
}

function Show-AssetPipelineDemo {
    param([bool]$IsDebugMode)
    
    $Mode = if ($IsDebugMode) { "DEBUG" } else { "RELEASE" }
    Write-Host "=== $Mode MODE DEMONSTRATION ===" -ForegroundColor Magenta
    Write-Host ""
    
    if ($IsDebugMode) {
        Write-Host "Debug Mode Features:" -ForegroundColor Cyan
        Write-Host "  ✓ Hot-reloading of asset packages" -ForegroundColor Green
        Write-Host "  ✓ Live XML parsing and procedural generation" -ForegroundColor Green
        Write-Host "  ✓ Instant feedback for asset changes" -ForegroundColor Green
        Write-Host "  ✓ Developer-friendly error messages" -ForegroundColor Green
        Write-Host ""
        
        # Generate asset IDs for debug mode
        Write-Host "1. Generating Asset ID mappings..." -ForegroundColor Yellow
        & $CodegenPath -f "header" -o "src/core/AssetIds.h" -n "Assets" "assets/packages"
        
        # Process assets with debug flag
        Write-Host "2. Processing assets in debug mode..." -ForegroundColor Yellow
        & $AssetCompilerPath -d -o "runtime/data/packs" "assets/packages/DeveloperPackage/package.xml"
        
        Write-Host "3. Debug mode setup complete!" -ForegroundColor Green
        Write-Host "   → Asset sources: assets/packages/" -ForegroundColor Gray
        Write-Host "   → Asset IDs: src/core/AssetIds.h" -ForegroundColor Gray
        Write-Host "   → Hot-reload enabled: File watching active" -ForegroundColor Gray
    }
    else {
        Write-Host "Release Mode Features:" -ForegroundColor Cyan
        Write-Host "  ✓ Optimized binary asset packs (.pak files)" -ForegroundColor Green
        Write-Host "  ✓ Compressed textures and optimized meshes" -ForegroundColor Green
        Write-Host "  ✓ Fast loading with memory-mapped I/O" -ForegroundColor Green
        Write-Host "  ✓ Stable numeric asset IDs" -ForegroundColor Green
        Write-Host ""
        
        # Generate asset IDs for release mode
        Write-Host "1. Generating Asset ID mappings..." -ForegroundColor Yellow
        & $CodegenPath -f "header" -o "src/core/AssetIds.h" -n "Assets" "assets/packages"
        
        # Process assets without debug flag (release mode)
        Write-Host "2. Compiling assets for release..." -ForegroundColor Yellow
        & $AssetCompilerPath -O -o "runtime/data/packs" "assets/packages/DeveloperPackage/package.xml"
        
        # Generate additional outputs for release
        Write-Host "3. Generating binary lookup table..." -ForegroundColor Yellow
        & $CodegenPath -f "binary" -o "runtime/data/asset_ids.bin" "assets/packages"
        
        Write-Host "4. Release mode compilation complete!" -ForegroundColor Green
        Write-Host "   → Binary packs: runtime/data/packs/*.pak" -ForegroundColor Gray
        Write-Host "   → Asset IDs: src/core/AssetIds.h" -ForegroundColor Gray
        Write-Host "   → Lookup table: runtime/data/asset_ids.bin" -ForegroundColor Gray
    }
    
    Write-Host ""
}

function Show-AssetStatistics {
    Write-Host "=== ASSET STATISTICS ===" -ForegroundColor Magenta
    Write-Host ""
    
    # Generate JSON report for statistics
    & $CodegenPath -f "json" -o "runtime/data/asset_stats.json" "assets/packages"
    
    if (Test-Path "runtime/data/asset_stats.json") {
        $Stats = Get-Content "runtime/data/asset_stats.json" | ConvertFrom-Json
        Write-Host "Total Assets Discovered: $($Stats.total_assets)" -ForegroundColor Cyan
        
        # Count by type
        $TypeCounts = @{}
        foreach ($asset in $Stats.assets.PSObject.Properties) {
            $type = $asset.Value.type
            if ($TypeCounts.ContainsKey($type)) {
                $TypeCounts[$type]++
            } else {
                $TypeCounts[$type] = 1
            }
        }
        
        Write-Host "Assets by Type:" -ForegroundColor Yellow
        foreach ($type in $TypeCounts.Keys) {
            Write-Host "  $type : $($TypeCounts[$type])" -ForegroundColor White
        }
    }
    
    Write-Host ""
}

function Show-PipelineArchitecture {
    Write-Host "=== ASSET PIPELINE ARCHITECTURE ===" -ForegroundColor Magenta
    Write-Host ""
    Write-Host "Pipeline Components:" -ForegroundColor Cyan
    Write-Host "  📁 Source Assets      → assets/packages/DeveloperPackage/" -ForegroundColor White
    Write-Host "  🏗️  Asset Compiler     → build_tools/asset_compiler/" -ForegroundColor White
    Write-Host "  🔢 Codegen Tool       → build_tools/codegen/" -ForegroundColor White
    Write-Host "  📋 Schema Validation  → assets/schemas/" -ForegroundColor White
    Write-Host "  💾 Runtime Data       → runtime/data/" -ForegroundColor White
    Write-Host ""
    Write-Host "Asset Flow:" -ForegroundColor Cyan
    Write-Host "  XML Assets → Schema Validation → Procedural Generation → Binary Packs" -ForegroundColor White
    Write-Host "  Asset Names → ID Generation → Numeric Mapping → C++ Constants" -ForegroundColor White
    Write-Host ""
    Write-Host "Key Features:" -ForegroundColor Cyan
    Write-Host "  ✓ Two-mode system (debug hot-reload vs release binary)" -ForegroundColor Green
    Write-Host "  ✓ Strings only at edges (numeric IDs at runtime)" -ForegroundColor Green
    Write-Host "  ✓ Deterministic compilation and asset loading" -ForegroundColor Green
    Write-Host "  ✓ IoC and ECS integration for modularity" -ForegroundColor Green
    Write-Host "  ✓ Procedural asset generation support" -ForegroundColor Green
    Write-Host ""
}

# Execute based on parameters
if ($Demo) {
    Show-PipelineArchitecture
    Show-AssetStatistics
    Show-AssetPipelineDemo -IsDebugMode $true
    Show-AssetPipelineDemo -IsDebugMode $false
} elseif ($Debug) {
    Show-AssetPipelineDemo -IsDebugMode $true
    Show-AssetStatistics
} elseif ($Release) {
    Show-AssetPipelineDemo -IsDebugMode $false
    Show-AssetStatistics
}

Write-Host "🎉 Asset pipeline demonstration complete!" -ForegroundColor Green
Write-Host ""
Write-Host "Next Steps:" -ForegroundColor Cyan
Write-Host "  1. Compile the main application with the generated AssetIds.h" -ForegroundColor White
Write-Host "  2. Run the simulation to see the assets in action" -ForegroundColor White
Write-Host "  3. Try modifying assets/packages/DeveloperPackage/package.xml" -ForegroundColor White
Write-Host "  4. In debug mode, changes will hot-reload automatically!" -ForegroundColor White
