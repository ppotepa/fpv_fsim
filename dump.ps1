# Get current date in YYYY-MM-DD format
$dateStr = Get-Date -Format "yyyy-MM-dd"
$outputFile = "source.$dateStr.log"

# Create or clear output file
"# Source Code Collection - $dateStr" | Out-File -FilePath $outputFile

# Find and process all .cpp, .h, .hpp and .xsd files recursively
Get-ChildItem -Path . -Include *.cpp, *.h, *.hpp, *.json -Recurse | ForEach-Object {
    # Get relative path
    $relativePath = $_.FullName -replace [regex]::Escape((Get-Location).Path + "\"), ""
    
    # Add file separator with path
    "`n`n" + "=" * 80 + "`n" + "FILE: $relativePath" + "`n" + "=" * 80 + "`n" | Out-File -FilePath $outputFile -Append
    
    # Add file content
    Get-Content $_.FullName | Out-File -FilePath $outputFile -Append
}

Write-Host "Source code collected in $outputFile"
