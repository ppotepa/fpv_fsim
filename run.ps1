param(
    [switch]$r,     # Run release version
    [switch]$help   # Show help
)

if ($help) {
    Write-Host "FPV Flight Simulator Run Script" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Usage:" -ForegroundColor Yellow
    Write-Host "  .\run.ps1       - Run debug version"
    Write-Host "  .\run.ps1 -r    - Run release version"
    Write-Host "  .\run.ps1 -help - Show this help"
    Write-Host ""
    Write-Host "Note: Make sure to build first using .\build.ps1" -ForegroundColor Yellow
    return
}

if ($r) {
    $buildDir = "build-release"
    $exePath = "$buildDir\fpv_fsim.exe"
    $buildType = "Release"
}
else {
    $buildDir = "build-debug"
    $exePath = "$buildDir\fpv_fsim.exe"
    $buildType = "Debug"
}

Write-Host "Running fpv_fsim ($buildType)..." -ForegroundColor Cyan

# Check if build directory exists
if (!(Test-Path $buildDir)) {
    Write-Host "Build directory '$buildDir' not found. Please build first using .\build.ps1" -ForegroundColor Red
    exit 1
}

# Check if executable exists
if (Test-Path $exePath) {
    Write-Host "Starting: $exePath" -ForegroundColor Yellow
    try {
        & $exePath
        if ($LASTEXITCODE -ne 0) {
            Write-Host "Application exited with code: $LASTEXITCODE" -ForegroundColor Yellow
        }
    }
    catch {
        Write-Host "Failed to run executable: $_" -ForegroundColor Red
        exit 1
    }
}
else {
    Write-Host "Executable not found: $exePath" -ForegroundColor Red
    Write-Host "Please build first using: .\build.ps1" -ForegroundColor Yellow
    exit 1
}
