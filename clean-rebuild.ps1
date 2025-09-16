param(
    [switch]$r,      # Release build
    [switch]$help,   # Show help
    [string]$m = ""  # Commit message
)

if ($help) {
    Write-Host "FPV Flight Simulator Clean Rebuild Script" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "This script performs a complete clean rebuild with git commit." -ForegroundColor Gray
    Write-Host ""
    Write-Host "Usage:" -ForegroundColor Yellow
    Write-Host "  .\clean-rebuild.ps1                    - Clean rebuild debug with auto commit message"
    Write-Host "  .\clean-rebuild.ps1 -r                 - Clean rebuild release with auto commit message"
    Write-Host "  .\clean-rebuild.ps1 -m 'Your message'  - Clean rebuild debug with custom commit message"
    Write-Host "  .\clean-rebuild.ps1 -r -m 'Message'    - Clean rebuild release with custom commit message"
    Write-Host "  .\clean-rebuild.ps1 -help              - Show this help"
    Write-Host ""
    Write-Host "Process:" -ForegroundColor Yellow
    Write-Host "  1. Git commit current changes"
    Write-Host "  2. Clean all build directories"
    Write-Host "  3. Clean all cached assets"
    Write-Host "  4. Fresh CMake configuration"
    Write-Host "  5. Complete rebuild"
    Write-Host ""
    return
}

if ($r) {
    $buildType = "Release"
    $buildDir = "build-release"
}
else {
    $buildType = "Debug" 
    $buildDir = "build-debug"
}

Write-Host "=== FPV Flight Simulator Clean Rebuild ($buildType) ===" -ForegroundColor Cyan
Write-Host ""

# ====================================================================
# Step 1: Git Commit
# ====================================================================
Write-Host "📝 Step 1: Committing current changes to Git..." -ForegroundColor Yellow

# Check if we're in a git repository
if (!(Test-Path ".git")) {
    Write-Host "❌ Error: Not in a git repository!" -ForegroundColor Red
    exit 1
}

# Check if there are any changes to commit
$gitStatus = git status --porcelain
if ($gitStatus) {
    # Auto-generate commit message if not provided
    if ([string]::IsNullOrEmpty($m)) {
        $timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
        $m = "Clean rebuild checkpoint - $timestamp"
    }
    
    Write-Host "   Adding all changes..." -ForegroundColor Gray
    git add .
    
    Write-Host "   Committing with message: '$m'" -ForegroundColor Gray
    git commit -m $m
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "❌ Git commit failed!" -ForegroundColor Red
        exit 1
    }
    
    Write-Host "✅ Changes committed successfully!" -ForegroundColor Green
} else {
    Write-Host "ℹ️  No changes to commit - working directory is clean" -ForegroundColor Cyan
}

Write-Host ""

# ====================================================================
# Step 2: Clean Build Directories
# ====================================================================
Write-Host "🧹 Step 2: Cleaning build directories..." -ForegroundColor Yellow

$buildDirs = @("build-debug", "build-release", "build")
foreach ($dir in $buildDirs) {
    if (Test-Path $dir) {
        Write-Host "   Removing $dir..." -ForegroundColor Gray
        Remove-Item $dir -Recurse -Force
        Write-Host "   ✅ Removed $dir" -ForegroundColor Green
    }
}

Write-Host ""

# ====================================================================
# Step 3: Clean Cached Assets
# ====================================================================
Write-Host "🗑️  Step 3: Cleaning cached assets..." -ForegroundColor Yellow

# Asset cache directories to clean
$cacheDirs = @(
    "runtime\data\cache",
    "runtime\data\compiled",
    "assets\build",
    "assets\cache",
    ".cache"
)

foreach ($dir in $cacheDirs) {
    if (Test-Path $dir) {
        Write-Host "   Removing asset cache: $dir..." -ForegroundColor Gray
        Remove-Item $dir -Recurse -Force
        Write-Host "   ✅ Removed $dir" -ForegroundColor Green
    }
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
        Write-Host "   Removing cache file: $file..." -ForegroundColor Gray
        Remove-Item $file -Force
        Write-Host "   ✅ Removed $file" -ForegroundColor Green
    }
}

Write-Host ""

# ====================================================================
# Step 4: Fresh CMake Configuration
# ====================================================================
Write-Host "⚙️  Step 4: Fresh CMake configuration..." -ForegroundColor Yellow

# Create build directory
if (!(Test-Path $buildDir)) {
    Write-Host "   Creating build directory: $buildDir" -ForegroundColor Gray
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

# Use MinGW-w64 toolchain
$env:PATH = "C:\msys64\mingw64\bin;$env:PATH"

try {
    Push-Location $buildDir
    
    Write-Host "   Configuring with CMake..." -ForegroundColor Gray
    $configResult = cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=$buildType -DCMAKE_C_COMPILER=gcc.exe -DCMAKE_CXX_COMPILER=g++.exe -DCMAKE_MAKE_PROGRAM=mingw32-make.exe ..
    
    if ($LASTEXITCODE -ne 0) {
        throw "CMake configuration failed"
    }
    
    Write-Host "   ✅ CMake configuration completed!" -ForegroundColor Green
}
catch {
    Write-Host "❌ CMake configuration failed: $_" -ForegroundColor Red
    exit 1
}
finally {
    Pop-Location
}

Write-Host ""

# ====================================================================
# Step 5: Complete Rebuild
# ====================================================================
Write-Host "🔨 Step 5: Complete rebuild..." -ForegroundColor Yellow

try {
    Push-Location $buildDir
    
    Write-Host "   Building with $env:NUMBER_OF_PROCESSORS parallel jobs..." -ForegroundColor Gray
    $buildResult = cmake --build . --parallel $env:NUMBER_OF_PROCESSORS
    
    if ($LASTEXITCODE -ne 0) {
        throw "Build failed"
    }
    
    Write-Host "   ✅ Build completed successfully!" -ForegroundColor Green
}
catch {
    Write-Host "❌ Build failed: $_" -ForegroundColor Red
    exit 1
}
finally {
    Pop-Location
}

Write-Host ""

# ====================================================================
# Step 6: Copy Runtime Assets
# ====================================================================
Write-Host "📦 Step 6: Copying runtime assets..." -ForegroundColor Yellow

# Copy packages directory to build output
if (Test-Path "packages") {
    Write-Host "   Copying packages to build directory..." -ForegroundColor Gray
    Copy-Item "packages" "$buildDir\" -Recurse -Force
    Write-Host "   ✅ Packages copied" -ForegroundColor Green
}

# Copy configs if they exist
if (Test-Path "configs") {
    Write-Host "   Copying configs to build directory..." -ForegroundColor Gray
    Copy-Item "configs" "$buildDir\" -Recurse -Force
    Write-Host "   ✅ Configs copied" -ForegroundColor Green
}

Write-Host ""

# ====================================================================
# Success Summary
# ====================================================================
Write-Host "🎉 Clean Rebuild Completed Successfully!" -ForegroundColor Green
Write-Host ""
Write-Host "Summary:" -ForegroundColor Cyan
Write-Host "   📝 Git: Changes committed" -ForegroundColor White
Write-Host "   🧹 Build: All build directories cleaned" -ForegroundColor White  
Write-Host "   🗑️  Cache: All asset caches cleared" -ForegroundColor White
Write-Host "   ⚙️  Config: Fresh CMake configuration" -ForegroundColor White
Write-Host "   🔨 Build: Complete rebuild successful" -ForegroundColor White
Write-Host "   📦 Assets: Runtime assets copied" -ForegroundColor White
Write-Host ""
Write-Host "Executable: $buildDir\fpv_fsim.exe" -ForegroundColor Green
Write-Host ""
Write-Host "Ready to run! Use: .\run.ps1" -ForegroundColor Yellow
