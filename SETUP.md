# Fortitude GitHub Repository Setup Guide

## Files Ready for GitHub

All necessary files have been created and are ready to be pushed to your FORTITUDE repository.

## Before Pushing

### 1. Update Repository URL in Installation Scripts

You need to replace `yourusername` with your actual GitHub username in:

- `install.sh` (line 9): `REPO_URL="https://github.com/yourusername/FORTITUDE.git"`
- `install.ps1` (line 8): `$REPO_URL = "https://github.com/yourusername/FORTITUDE.git"`
- `README.md`: Update all references to `yourusername/FORTITUDE`

### 2. Clean Build Artifacts

Before committing, make sure to clean build artifacts:

```bash
cd Fortitude
make fclean
rm -f *.o *.exe fortitude_runner test_libft
rm -rf tests/*.o
```

### 3. Verify .gitignore

The `.gitignore` file should exclude:
- `*.o` (object files)
- `*.exe` (executables)
- `fortitude_runner` (binary, installed as `fortitude`)
- `test_libft` (test binary)
- IDE files
- OS files

## Repository Structure

```
FORTITUDE/
├── .gitignore           # Git ignore rules
├── LICENSE              # MIT License
├── README.md            # Main documentation
├── SETUP.md             # This file
├── Makefile             # Build system
├── install.sh           # Linux/macOS installer
├── install.ps1          # Windows installer
├── uninstall.sh         # Uninstaller
├── fortitude.h          # Framework header
├── fortitude.c          # Framework implementation
├── fortitude_runner.c   # Main runner executable
└── tests/
    └── test_libft.c     # Libft test suite
```

## Initial Git Setup

Once you've cloned the empty FORTITUDE repository:

```bash
cd FORTITUDE
# Copy all files from Fortitude/ to FORTITUDE/
# (or rename Fortitude/ to FORTITUDE/)

# Update repository URLs in install scripts
# Then:

git add .
git commit -m "Initial commit: Fortitude testing framework"
git push origin main
```

## After Pushing

### Create a Release

1. Go to GitHub → Releases → Create a new release
2. Tag version: `v1.0.0`
3. Release title: `Fortitude v1.0.0`
4. Description: Initial release of Fortitude testing framework
5. Publish release

### Test Installation

Users can now install with:

**Linux/macOS:**
```bash
curl -fsSL https://raw.githubusercontent.com/yourusername/FORTITUDE/main/install.sh | bash
```

**Windows:**
```powershell
irm https://raw.githubusercontent.com/yourusername/FORTITUDE/main/install.ps1 | iex
```

## Notes

- The `fortitude` command automatically detects Libft projects and runs tests
- Installation scripts add `fortitude` to PATH
- Users can run `fortitude` from any directory
- Only failures and errors are displayed - successful operations are suppressed
- The framework is extensible for other 42 projects

