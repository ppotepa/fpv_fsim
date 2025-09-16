param(
    [switch]$r,      # Release build
    [switch]$clean,  # Clean build directories
    [switch]$help    # Show help
)

if ($help) {
    Write-Host "FPV Flight Simulator Build Script" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Usage:" -ForegroundColor Yellow
    Write-Host "  .\build.ps1          - Build debug version"
    Write-Host "  .\build.ps1 -r       - Build release version"
    Write-Host "  .\build.ps1 -clean   - Clean all build directories"
    Write-Host "  .\build.ps1 -help    - Show this help"
    Write-Host ""
    Write-Host "Examples:" -ForegroundColor Yellow
    Write-Host "  .\build.ps1 -clean   # Clean everything"
    Write-Host "  .\build.ps1          # Build debug"
    Write-Host "  .\build.ps1 -r       # Build release"
    return
}

if ($clean) {
    Write-Host "Cleaning build directories..." -ForegroundColor Yellow
    if (Test-Path "build-debug") {
        Remove-Item "build-debug" -Recurse -Force
        Write-Host "Removed build-debug" -ForegroundColor Green
    }
    if (Test-Path "build-release") {
        Remove-Item "build-release" -Recurse -Force  
        Write-Host "Removed build-release" -ForegroundColor Green
    }
    Write-Host "Clean completed!" -ForegroundColor Green
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

Write-Host "Building fpv_fsim ($buildType)..." -ForegroundColor Cyan

# Create build directory if it doesn't exist
if (!(Test-Path $buildDir)) {
    Write-Host "Creating build directory: $buildDir" -ForegroundColor Yellow
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

# Use MinGW-w64 toolchain instead of Visual Studio
$env:PATH = "C:\msys64\mingw64\bin;$env:PATH"

try {
    Push-Location $buildDir
    
    Write-Host "Configuring with CMake..." -ForegroundColor Yellow
    $configResult = cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=$buildType -DCMAKE_C_COMPILER=gcc.exe -DCMAKE_CXX_COMPILER=g++.exe -DCMAKE_MAKE_PROGRAM=mingw32-make.exe ..
    
    if ($LASTEXITCODE -ne 0) {
        throw "CMake configuration failed"
    }
    
    Write-Host "Building..." -ForegroundColor Yellow
    $buildResult = cmake --build . --parallel $env:NUMBER_OF_PROCESSORS
    
    if ($LASTEXITCODE -ne 0) {
        throw "Build failed"
    }
    
    Write-Host "Build completed successfully!" -ForegroundColor Green
    Write-Host "Executable: $buildDir\fpv_fsim.exe" -ForegroundColor Green
}
catch {
    Write-Host "Build failed: $_" -ForegroundColor Red
    exit 1
}
finally {
    Pop-Location
}
