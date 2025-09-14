param([switch]$r)

if ($r) {
    $buildDir = "build-release"
    $exePath = "$buildDir/Release/fpv_fsim.exe"
} else {
    $buildDir = "build-debug"
    $exePath = "$buildDir/Debug/fpv_fsim.exe"
}

if (Test-Path $exePath) {
    & $exePath
} else {
    Write-Host "Executable not found. Please build first."
}
