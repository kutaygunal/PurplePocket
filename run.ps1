param(
    [string]$Configuration = "Debug",  # Default to Debug, but allow Release as parameter
    [switch]$BuildOnly = $false        # Option to only build without running
)

$ErrorActionPreference = "Stop"  # Stop on first error

# Project paths
$ProjectRoot = $PSScriptRoot
$BuildDir = Join-Path $ProjectRoot "build"

# Colors for output
function Write-ColorOutput($ForegroundColor) {
    $fc = $host.UI.RawUI.ForegroundColor
    $host.UI.RawUI.ForegroundColor = $ForegroundColor
    if ($args) {
        Write-Output $args
    }
    $host.UI.RawUI.ForegroundColor = $fc
}

# Ensure build directory exists
if (!(Test-Path $BuildDir)) {
    Write-ColorOutput Green "Creating build directory..."
    New-Item -ItemType Directory -Path $BuildDir | Out-Null
}

# Generate build files
Write-ColorOutput Green "Generating build files..."
cmake -G "Visual Studio 17 2022" -A x64 -B $BuildDir
if ($LASTEXITCODE -ne 0) {
    Write-ColorOutput Red "Failed to generate build files!"
    exit 1
}

# Build the project
Write-ColorOutput Green "Building project in $Configuration configuration..."
cmake --build $BuildDir --config $Configuration
if ($LASTEXITCODE -ne 0) {
    Write-ColorOutput Red "Build failed!"
    exit 1
}

# Run the application if not build-only
if (!$BuildOnly) {
    $ExePath = Join-Path (Join-Path $BuildDir $Configuration) "QtProject.exe"
    if (Test-Path $ExePath) {
        Write-ColorOutput Green "Running application..."
        & $ExePath
        if ($LASTEXITCODE -ne 0) {
            Write-ColorOutput Red "Application exited with error code: $LASTEXITCODE"
            exit $LASTEXITCODE
        }
    } else {
        Write-ColorOutput Red "Could not find executable at: $ExePath"
        exit 1
    }
}

Write-ColorOutput Green "Done!"
