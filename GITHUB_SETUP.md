# GitHub Repository Setup - Quick Start

## Step-by-Step Instructions

### 1. Clone Your Empty FORTITUDE Repository

```bash
cd ~/Desktop/42  # or wherever you want
git clone https://github.com/yourusername/FORTITUDE.git
cd FORTITUDE
```

### 2. Copy Files from Fortitude/ to FORTITUDE/

**On Windows (PowerShell):**
```powershell
Copy-Item -Path ..\Fortitude\* -Destination . -Recurse -Exclude *.o,*.exe,fortitude_runner,test_libft
```

**On Linux/macOS:**
```bash
cp -r ../Fortitude/* .
rm -f *.o *.exe fortitude_runner test_libft tests/*.o
```

### 3. Update GitHub Username

Replace `yourusername` with your actual GitHub username in:

- `install.sh` (line 9)
- `install.ps1` (line 8)  
- `README.md` (all installation URLs)

### 4. Initial Commit

```bash
git add .
git commit -m "Initial commit: Fortitude testing framework for 42 projects"
git push origin main
```

### 5. Create First Release

1. Go to: https://github.com/yourusername/FORTITUDE/releases/new
2. Tag: `v1.0.0`
3. Title: `Fortitude v1.0.0 - Initial Release`
4. Description: Initial release of Fortitude testing framework
5. Publish release

## Files Included

✅ All source files (`.c`, `.h`)
✅ Makefile
✅ Installation scripts (`install.sh`, `install.ps1`)
✅ Uninstaller (`uninstall.sh`)
✅ Documentation (`README.md`, `SETUP.md`)
✅ License (`LICENSE`)
✅ Git ignore (`.gitignore`)
✅ Test suite (`tests/test_libft.c`)

## Excluded (via .gitignore)

❌ Build artifacts (`.o`, `.exe`)
❌ Compiled binaries (`fortitude_runner`)
❌ IDE files
❌ OS files

## After Setup

Users can install with:

```bash
# Linux/macOS
curl -fsSL https://raw.githubusercontent.com/yourusername/FORTITUDE/main/install.sh | bash

# Windows
irm https://raw.githubusercontent.com/yourusername/FORTITUDE/main/install.ps1 | iex
```

Then use from any directory:
```bash
fortitude_runner
# or
fortitude
```

