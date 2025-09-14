param([switch]$r)

if ($r) {
    $buildType = "Release"
    $buildDir = "build-release"
} else {
    $buildType = "Debug"
    $buildDir = "build-debug"
}

if (!(Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir
}

Push-Location $buildDir
cmake -DCMAKE_BUILD_TYPE=$buildType ..
cmake --build .
Pop-Location
