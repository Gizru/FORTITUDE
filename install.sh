#!/bin/bash

# Fortitude Installation Script for Linux/macOS
# This script installs Fortitude to ~/.local/bin and adds it to PATH

set -e

FORTITUDE_DIR="$HOME/.local/share/fortitude"
BIN_DIR="$HOME/.local/bin"
REPO_URL="https://github.com/Gizru/FORTITUDE.git"

echo "╔══════════════════════════════════════════════════════════╗"
echo "║                                                          ║"
echo "║              FORTITUDE Installation                     ║"
echo "║                                                          ║"
echo "╚══════════════════════════════════════════════════════════╝"
echo ""

# Check for dependencies
echo "Checking dependencies..."
MISSING_DEPS=""

if ! command -v make &> /dev/null; then
	MISSING_DEPS="$MISSING_DEPS make"
fi

if ! command -v cc &> /dev/null && ! command -v gcc &> /dev/null && ! command -v clang &> /dev/null; then
	MISSING_DEPS="$MISSING_DEPS cc/gcc/clang"
fi

if ! command -v git &> /dev/null; then
	MISSING_DEPS="$MISSING_DEPS git"
fi

if [ -n "$MISSING_DEPS" ]; then
	echo "Error: Missing dependencies:$MISSING_DEPS"
	echo "Please install them and run this script again."
	exit 1
fi

echo "✓ All dependencies found"
echo ""

# Create directories
echo "Creating directories..."
mkdir -p "$FORTITUDE_DIR"
mkdir -p "$BIN_DIR"
echo "✓ Directories created"
echo ""

# Clone or update repository
if [ -d "$FORTITUDE_DIR/.git" ]; then
	echo "Updating existing Fortitude installation..."
	cd "$FORTITUDE_DIR"
	git pull
else
	echo "Cloning Fortitude repository..."
	git clone "$REPO_URL" "$FORTITUDE_DIR"
	cd "$FORTITUDE_DIR"
fi
echo "✓ Repository ready"
echo ""

# Build Fortitude
echo "Building Fortitude..."
make clean 2>/dev/null || true
make all
echo "✓ Build complete"
echo ""

# Install binary
echo "Installing fortitude_runner..."
cp fortitude_runner "$BIN_DIR/fortitude_runner"
chmod +x "$BIN_DIR/fortitude_runner"

# Create symlink for 'fortitude' command
if [ ! -f "$BIN_DIR/fortitude" ]; then
	ln -s "$BIN_DIR/fortitude_runner" "$BIN_DIR/fortitude"
fi
echo "✓ Binary installed"
echo ""

# Add to PATH if not already present
SHELL_RC=""
if [ -n "$ZSH_VERSION" ]; then
	SHELL_RC="$HOME/.zshrc"
elif [ -n "$BASH_VERSION" ]; then
	SHELL_RC="$HOME/.bashrc"
fi

if [ -n "$SHELL_RC" ] && [ -f "$SHELL_RC" ]; then
	if ! grep -q "$BIN_DIR" "$SHELL_RC"; then
		echo "Adding $BIN_DIR to PATH in $SHELL_RC..."
		echo "" >> "$SHELL_RC"
		echo "# Fortitude" >> "$SHELL_RC"
		echo "export PATH=\"\$PATH:$BIN_DIR\"" >> "$SHELL_RC"
		echo "✓ PATH updated"
	else
		echo "✓ PATH already configured"
	fi
else
	echo "⚠ Warning: Could not detect shell. Please add $BIN_DIR to your PATH manually."
fi
echo ""

# Verify installation
if command -v fortitude_runner &> /dev/null || [ -f "$BIN_DIR/fortitude_runner" ]; then
	echo "╔══════════════════════════════════════════════════════════╗"
	echo "║                                                          ║"
	echo "║          Fortitude installed successfully!               ║"
	echo "║                                                          ║"
	echo "╚══════════════════════════════════════════════════════════╝"
	echo ""
	echo "Usage:"
	echo "  fortitude_runner    # Run from any project directory"
	echo "  fortitude           # Alias for fortitude_runner"
	echo ""
	echo "If you just installed, you may need to:"
	echo "  source $SHELL_RC"
	echo "  # or open a new terminal"
else
	echo "⚠ Installation completed, but verification failed."
	echo "  Please ensure $BIN_DIR is in your PATH"
fi

