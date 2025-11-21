#!/bin/bash

# Fortitude Uninstallation Script for Linux/macOS

set -e

FORTITUDE_DIR="$HOME/.local/share/fortitude"
BIN_DIR="$HOME/.local/bin"

echo "╔══════════════════════════════════════════════════════════╗"
echo "║                                                          ║"
echo "║            FORTITUDE Uninstallation                      ║"
echo "║                                                          ║"
echo "╚══════════════════════════════════════════════════════════╝"
echo ""

read -p "Are you sure you want to uninstall Fortitude? (y/N) " -n 1 -r
echo
if [[ ! $REPLY =~ ^[Yy]$ ]]; then
	echo "Uninstallation cancelled."
	exit 0
fi

# Remove binaries
echo "Removing binaries..."
rm -f "$BIN_DIR/fortitude_runner"
rm -f "$BIN_DIR/fortitude"
echo "✓ Binaries removed"

# Remove installation directory
if [ -d "$FORTITUDE_DIR" ]; then
	echo "Removing installation directory..."
	rm -rf "$FORTITUDE_DIR"
	echo "✓ Installation directory removed"
fi

# Remove from PATH (optional - commented out to be safe)
# echo "Note: PATH entries in shell config files were not removed."
# echo "      You can remove them manually if needed."

echo ""
echo "✓ Fortitude has been uninstalled successfully!"

