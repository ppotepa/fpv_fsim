# Build script for scene renderer test
Write-Host "Building scene_renderer_test..."

# Create build directory if it doesn't exist
if (-not (Test-Path -Path "tests\build")) {
    New-Item -ItemType Directory -Path "tests\build"
}

# Change to build directory
Set-Location -Path "tests\build"

# Generate build files with CMake
cmake -G "Ninja" ..

# Build the test
cmake --build .

# Return to original directory
Set-Location -Path "..\..\"

# Run the test
Write-Host "Running scene_renderer_test..."
.\tests\build\scene_renderer_test.exe
