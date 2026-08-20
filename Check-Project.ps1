<#
.SYNOPSIS
    Basic pre-build sanity check for a C++ project directory.

.DESCRIPTION
    Scans a project folder for .cpp / .h / .hpp source files, skipping
    known vendor/third-party directories, flags any file over a size
    threshold, and writes a timestamped summary to report.txt.

.EXAMPLE
    .\Check-Project.ps1
    .\Check-Project.ps1 -Path . -MaxSizeKB 200
#>

param(
    [string]$Path = ".",
    [int]$MaxSizeKB = 100,
    [string[]]$ExcludeDirs = @("SFML-2.5.1", ".git", ".vscode", "build", "bin", "obj")
)

$ErrorActionPreference = "Stop"

# 1. Find source files, excluding vendor/build directories
$sourceFiles = Get-ChildItem -Path $Path -Recurse -File -Include *.cpp, *.h, *.hpp |
    Where-Object {
        $file = $_
        -not ($ExcludeDirs | Where-Object { $file.FullName -match [regex]::Escape("\$_\") })
    }

$cppCount = ($sourceFiles | Where-Object { $_.Extension -eq ".cpp" }).Count
$headerCount = ($sourceFiles | Where-Object { $_.Extension -in ".h", ".hpp" }).Count
$totalCount = $sourceFiles.Count

# 2. Flag oversized files
$largeFiles = $sourceFiles | Where-Object { $_.Length -gt ($MaxSizeKB * 1KB) }

# 3. Build the report
$timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
$reportLines = @()
$reportLines += "Project Sanity Check Report"
$reportLines += "Generated: $timestamp"
$reportLines += "Scanned path: $((Resolve-Path $Path).Path)"
$reportLines += "Excluded dirs: $($ExcludeDirs -join ', ')"
$reportLines += ""
$reportLines += "Source files found: $totalCount ($cppCount .cpp, $headerCount headers)"
$reportLines += ""

if ($largeFiles.Count -gt 0) {
    $reportLines += "WARNING: $($largeFiles.Count) file(s) exceed ${MaxSizeKB}KB:"
    foreach ($f in $largeFiles) {
        $sizeKB = [math]::Round($f.Length / 1KB, 1)
        $reportLines += "  - $($f.FullName) ($sizeKB KB)"
    }
} else {
    $reportLines += "No files exceed the ${MaxSizeKB}KB threshold."
}

$reportPath = Join-Path $Path "report.txt"
$reportLines | Out-File -FilePath $reportPath -Encoding utf8

# 4. Print summary to console too
$reportLines | ForEach-Object { Write-Host $_ }

# 5. Exit code: 0 = clean, 1 = problem found
if ($largeFiles.Count -gt 0) {
    exit 1
} else {
    exit 0
}
