param([switch]$r)

if ($r) {
    $buildType = "Release"
    $buildDir = "build-release"
}
else {
    $buildType = "Debug"
    $buildDir = "build-debug"
}

if (!(Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir
}

# Use MinGW-w64 toolchain instead of Visual Studio
$env:PATH = "C:\msys64\mingw64\bin;$env:PATH"

Push-Location $buildDir
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=$buildType -DCMAKE_C_COMPILER=gcc.exe -DCMAKE_CXX_COMPILER=g++.exe -DCMAKE_MAKE_PROGRAM=mingw32-make.exe ..
cmake --build . --parallel $env:NUMBER_OF_PROCESSORS
Pop-Location
