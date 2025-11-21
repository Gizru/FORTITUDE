# Fortitude Installation Script for Windows PowerShell
# This script installs Fortitude and adds it to PATH

$ErrorActionPreference = "Stop"

$FORTITUDE_DIR = "$env:USERPROFILE\.fortitude"
$BIN_DIR = "$env:USERPROFILE\bin"
$REPO_URL = "https://github.com/Gizru/FORTITUDE.git"

Write-Host "╔══════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║                                                          ║" -ForegroundColor Cyan
Write-Host "║              FORTITUDE Installation                     ║" -ForegroundColor Cyan
Write-Host "║                                                          ║" -ForegroundColor Cyan
Write-Host "╚══════════════════════════════════════════════════════════╝" -ForegroundColor Cyan
Write-Host ""

# Check for dependencies
Write-Host "Checking dependencies..." -ForegroundColor Yellow
$MISSING_DEPS = @()

if (-not (Get-Command make -ErrorAction SilentlyContinue)) {
	$MISSING_DEPS += "make"
}

if (-not (Get-Command cc -ErrorAction SilentlyContinue) -and 
    -not (Get-Command gcc -ErrorAction SilentlyContinue) -and 
    -not (Get-Command clang -ErrorAction SilentlyContinue)) {
	$MISSING_DEPS += "cc/gcc/clang"
}

if (-not (Get-Command git -ErrorAction SilentlyContinue)) {
	$MISSING_DEPS += "git"
}

if ($MISSING_DEPS.Count -gt 0) {
	Write-Host "Error: Missing dependencies: $($MISSING_DEPS -join ', ')" -ForegroundColor Red
	Write-Host "Please install them and run this script again."
	exit 1
}

Write-Host "✓ All dependencies found" -ForegroundColor Green
Write-Host ""

# Create directories
Write-Host "Creating directories..." -ForegroundColor Yellow
New-Item -ItemType Directory -Force -Path $FORTITUDE_DIR | Out-Null
New-Item -ItemType Directory -Force -Path $BIN_DIR | Out-Null
Write-Host "✓ Directories created" -ForegroundColor Green
Write-Host ""

# Clone or update repository
if (Test-Path "$FORTITUDE_DIR\.git") {
	Write-Host "Updating existing Fortitude installation..." -ForegroundColor Yellow
	Set-Location $FORTITUDE_DIR
	git pull
} else {
	Write-Host "Cloning Fortitude repository..." -ForegroundColor Yellow
	git clone $REPO_URL $FORTITUDE_DIR
	Set-Location $FORTITUDE_DIR
}
Write-Host "✓ Repository ready" -ForegroundColor Green
Write-Host ""

# Build Fortitude
Write-Host "Building Fortitude..." -ForegroundColor Yellow
& make clean 2>$null
& make all
Write-Host "✓ Build complete" -ForegroundColor Green
Write-Host ""

# Install binary
Write-Host "Installing fortitude..." -ForegroundColor Yellow
Copy-Item "fortitude_runner.exe" "$BIN_DIR\fortitude.exe" -Force

Write-Host "✓ Binary installed" -ForegroundColor Green
Write-Host ""

# Add to PATH
Write-Host "Adding to PATH..." -ForegroundColor Yellow
$currentPath = [Environment]::GetEnvironmentVariable("Path", "User")
if ($currentPath -notlike "*$BIN_DIR*") {
	$newPath = "$currentPath;$BIN_DIR"
	[Environment]::SetEnvironmentVariable("Path", $newPath, "User")
	$env:Path += ";$BIN_DIR"
	Write-Host "✓ PATH updated" -ForegroundColor Green
} else {
	Write-Host "✓ PATH already configured" -ForegroundColor Green
}
Write-Host ""

# Verify installation
Write-Host "╔══════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║                                                          ║" -ForegroundColor Cyan
Write-Host "║          Fortitude installed successfully!               ║" -ForegroundColor Cyan
Write-Host "║                                                          ║" -ForegroundColor Cyan
Write-Host "╚══════════════════════════════════════════════════════════╝" -ForegroundColor Cyan
Write-Host ""
Write-Host "Usage:" -ForegroundColor Yellow
Write-Host "  fortitude           # Run from any project directory"
Write-Host ""
Write-Host "Note: You may need to restart your terminal for PATH changes to take effect."

