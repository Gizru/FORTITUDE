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
echo "Installing fortitude..."
cp fortitude_runner "$BIN_DIR/fortitude"
chmod +x "$BIN_DIR/fortitude"
echo "✓ Binary installed"
echo ""

# Add to PATH if not already present
SHELL_RC=""
if [ -n "$ZSH_VERSION" ]; then
	SHELL_RC="$HOME/.zshrc"
elif [ -n "$BASH_VERSION" ]; then
	SHELL_RC="$HOME/.bashrc"
elif [ -f "$HOME/.bash_profile" ]; then
	SHELL_RC="$HOME/.bash_profile"
elif [ -f "$HOME/.profile" ]; then
	SHELL_RC="$HOME/.profile"
fi

if [ -n "$SHELL_RC" ]; then
	if [ ! -f "$SHELL_RC" ]; then
		touch "$SHELL_RC"
	fi
	if ! grep -q "$BIN_DIR" "$SHELL_RC"; then
		echo "Adding $BIN_DIR to PATH in $SHELL_RC..."
		echo "" >> "$SHELL_RC"
		echo "# Fortitude" >> "$SHELL_RC"
		echo "export PATH=\"\$PATH:$BIN_DIR\"" >> "$SHELL_RC"
		echo "✓ PATH updated in $SHELL_RC"
	else
		echo "✓ PATH already configured in $SHELL_RC"
	fi
else
	echo "⚠ Warning: Could not detect shell configuration file."
	echo "   Please add the following to your shell configuration:"
	echo "   export PATH=\"\$PATH:$BIN_DIR\""
fi
echo ""

# Verify installation
if command -v fortitude &> /dev/null || [ -f "$BIN_DIR/fortitude" ]; then
	echo "╔══════════════════════════════════════════════════════════╗"
	echo "║                                                          ║"
	echo "║          Fortitude installed successfully!               ║"
	echo "║                                                          ║"
	echo "╚══════════════════════════════════════════════════════════╝"
	echo ""
	echo "Usage:"
	echo "  fortitude           # Run from any project directory"
	echo ""
	echo "If you just installed, you may need to:"
	echo "  source $SHELL_RC"
	echo "  # or open a new terminal"
else
	echo "⚠ Installation completed, but verification failed."
	echo "  Please ensure $BIN_DIR is in your PATH"
fi

