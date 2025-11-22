#!/bin/bash

# Fortitude Installation Script for Linux/macOS
# This script installs Fortitude to ~/.local/bin and adds it to PATH
#
# Designed for environments with restricted permissions (e.g., school machines):
# - All installation paths are within $HOME (user's home directory)
# - No sudo/administrator privileges required
# - Works with network-mounted home directories

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

# Function to detect shell RC file (improved detection)
detect_shell_rc() {
	RC_FILE=""
	
	# Check current shell first
	if [[ "$SHELL" == *"zsh"* ]]; then
		if [ -f "$HOME/.zshrc" ]; then
			RC_FILE="$HOME/.zshrc"
		fi
	elif [[ "$SHELL" == *"bash"* ]]; then
		if [ -f "$HOME/.bashrc" ]; then
			RC_FILE="$HOME/.bashrc"
		elif [ -f "$HOME/.bash_profile" ]; then
			RC_FILE="$HOME/.bash_profile"
		fi
	fi
	
	# Fallback: check file existence regardless of SHELL variable
	if [ -z "$RC_FILE" ]; then
		if [ -f "$HOME/.zshrc" ]; then
			RC_FILE="$HOME/.zshrc"
		elif [ -f "$HOME/.bashrc" ]; then
			RC_FILE="$HOME/.bashrc"
		elif [ -f "$HOME/.bash_profile" ]; then
			RC_FILE="$HOME/.bash_profile"
		elif [ -f "$HOME/.profile" ]; then
			RC_FILE="$HOME/.profile"
		fi
	fi
	
	echo "$RC_FILE"
}

# Check for dependencies
echo "Checking dependencies..."
MISSING_DEPS=""

if ! command -v make &> /dev/null; then
	MISSING_DEPS="$MISSING_DEPS make"
fi

if ! command -v cc &> /dev/null && ! command -v gcc &> /dev/null && ! command -v clang &> /dev/null; then
	MISSING_DEPS="$MISSING_DEPS gcc/clang"
fi

if ! command -v git &> /dev/null; then
	MISSING_DEPS="$MISSING_DEPS git"
fi

if [ -n "$MISSING_DEPS" ]; then
	echo "⚠ Missing dependencies:$MISSING_DEPS"
	echo ""
	echo "Fortitude requires these tools to be installed:"
	echo "  - make (build automation)"
	echo "  - gcc/clang (C compiler)"
	echo "  - git (version control)"
	echo ""
	echo "On school machines, these should already be available."
	echo "If they are missing, please contact your system administrator."
	echo ""
	echo "To check if they're installed but not in PATH, try:"
	echo "  /usr/bin/make --version"
	echo "  /usr/bin/gcc --version"
	echo "  /usr/bin/git --version"
	echo ""
	exit 1
fi

echo "✓ All dependencies found"
echo ""

# Create directories (all within $HOME - no system access needed)
echo "Creating directories..."
mkdir -p "$FORTITUDE_DIR"
mkdir -p "$BIN_DIR"
echo "✓ Directories created within $HOME"
echo ""

# Clone or update repository
if [ -d "$FORTITUDE_DIR/.git" ]; then
	echo "Updating existing Fortitude installation..."
	cd "$FORTITUDE_DIR"
	git pull || {
		echo "⚠ Warning: Failed to update. Continuing with existing version..."
	}
else
	echo "Cloning Fortitude repository..."
	if ! git clone "$REPO_URL" "$FORTITUDE_DIR"; then
		echo "Error: Failed to clone repository"
		exit 1
	fi
	cd "$FORTITUDE_DIR"
fi
echo "✓ Repository ready"
echo ""

# Build Fortitude
echo "Building Fortitude..."
if ! make clean 2>/dev/null; then
	echo "  (No previous build to clean)"
fi
if ! make all; then
	echo "Error: Build failed"
	exit 1
fi
echo "✓ Build complete"
echo ""

# Verify binary exists
if [ ! -f "fortitude_runner" ]; then
	echo "Error: Build artifact 'fortitude_runner' not found"
	exit 1
fi

# Install binary
echo "Installing fortitude..."
cp fortitude_runner "$BIN_DIR/fortitude"
chmod +x "$BIN_DIR/fortitude"
echo "✓ Binary installed"
echo ""

# Detect shell RC file
SHELL_RC=$(detect_shell_rc)

# Add to PATH and create alias if not already present
if [ -n "$SHELL_RC" ]; then
	if [ ! -f "$SHELL_RC" ]; then
		touch "$SHELL_RC"
	fi
	
	# Add PATH if not present
	if ! grep -q "$BIN_DIR" "$SHELL_RC" 2>/dev/null; then
		echo "Adding $BIN_DIR to PATH in $SHELL_RC..."
		echo "" >> "$SHELL_RC"
		echo "# Fortitude" >> "$SHELL_RC"
		echo "export PATH=\"\$PATH:$BIN_DIR\"" >> "$SHELL_RC"
		echo "✓ PATH updated in $SHELL_RC"
	fi
	
	# Add alias for immediate availability (more reliable than PATH alone)
	if ! grep -q "alias fortitude=" "$SHELL_RC" 2>/dev/null; then
		echo "Adding fortitude alias to $SHELL_RC..."
		echo "alias fortitude=\"$BIN_DIR/fortitude\"" >> "$SHELL_RC"
		echo "✓ Alias added"
	fi
else
	echo "⚠ Warning: Could not detect shell configuration file."
	echo "   Please add the following to your shell configuration:"
	echo "   export PATH=\"\$PATH:$BIN_DIR\""
	echo "   alias fortitude=\"$BIN_DIR/fortitude\""
fi
echo ""

# Export PATH in current session for immediate use
export PATH="$PATH:$BIN_DIR"

# Verify installation
echo "Verifying installation..."
if [ -f "$BIN_DIR/fortitude" ]; then
	if "$BIN_DIR/fortitude" --help &>/dev/null || "$BIN_DIR/fortitude" -h &>/dev/null; then
		echo "✓ Installation verified"
		echo ""
		echo "╔══════════════════════════════════════════════════════════╗"
		echo "║                                                          ║"
		echo "║          Fortitude installed successfully!               ║"
		echo "║                                                          ║"
		echo "╚══════════════════════════════════════════════════════════╝"
		echo ""
		echo "Usage:"
		echo "  fortitude           # Run from any project directory"
		echo ""
		
		# Show help if available
		if "$BIN_DIR/fortitude" --help &>/dev/null 2>&1; then
			echo "Quick help:"
			"$BIN_DIR/fortitude" --help | head -10
			echo ""
		fi
		
		# Reload shell to make changes available immediately
		echo "Reloading shell to activate changes..."
		echo ""
		
		# Try to reload shell (works in most interactive shells)
		if [ -n "$SHELL" ] && [ -t 0 ]; then
			exec "$SHELL" -l
		else
			echo "To use fortitude immediately, run:"
			echo "  source $SHELL_RC"
			echo "  # or open a new terminal"
		fi
	else
		echo "✓ Binary installed but help command unavailable"
		echo ""
		echo "Installation complete! Run 'fortitude' from any project directory."
		echo ""
		if [ -n "$SHELL" ] && [ -t 0 ]; then
			exec "$SHELL" -l
		fi
	fi
else
	echo "⚠ Installation completed, but binary not found at $BIN_DIR/fortitude"
	echo "  Please check the installation and ensure $BIN_DIR is in your PATH"
	exit 1
fi
