param([switch]$r)

if ($r) {
    $buildDir = "build-release"
} else {
    $buildDir = "build-debug"
}

if (Test-Path "$buildDir/fpv_fsim.exe") {
    Push-Location $buildDir
    .\fpv_fsim.exe
    Pop-Location
} else {
    Write-Host "Executable not found. Please build first."
}
