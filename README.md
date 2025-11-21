# Fortitude - 42 Project Testing Framework

**A comprehensive automated testing framework for 42 school projects that validates builds, code style, and functionality with detailed reporting.**

Fortitude streamlines the development and validation process for 42 projects by automating build verification, norminette style checking, comprehensive test execution, and automatic cleanup. Simply run `fortitude_runner` from any project directory to get instant feedback on your code quality and correctness.

## Features

- **Automatic Project Detection** - Detects 42 projects and their structure
- **Build Verification** - Tests if projects compile correctly
- **Norminette Integration** - Automatically checks code style compliance
- **Comprehensive Testing** - Tests all functions organized by parts (Part 1, Part 2, Bonus)
- **Automatic Cleanup** - Removes all build artifacts after testing
- **Detailed Reporting** - Color-coded output with success/error messages
- **Cross-Platform** - Works on Linux, macOS, and Windows

## Installation

### Linux/macOS

```bash
curl -fsSL https://raw.githubusercontent.com/Gizru/FORTITUDE/main/install.sh | bash
```

Or manually:
```bash
git clone https://github.com/Gizru/FORTITUDE.git
cd FORTITUDE
chmod +x install.sh
./install.sh
```

### Windows (PowerShell)

```powershell
irm https://raw.githubusercontent.com/Gizru/FORTITUDE/main/install.ps1 | iex
```

Or manually:
```powershell
git clone https://github.com/Gizru/FORTITUDE.git
cd FORTITUDE
.\install.ps1
```

### Requirements

- `make` - Build automation tool
- `cc`/`gcc`/`clang` - C compiler
- `git` - Version control (for installation)
- `norminette` - 42 code style checker (optional, will skip if not found)

## Usage

### From Any Project Directory

Simply navigate to your 42 project directory and run:

```bash
fortitude_runner
# or
fortitude
```

Fortitude will:
1. List all project files
2. Build the project (with bonus for Libft)
3. Run norminette checks
4. Execute test suite (if available)
5. Clean all build artifacts
6. Display a comprehensive summary

### Example Output

```
╔══════════════════════════════════════════════════════════╗
║                    FORTITUDE RUNNER                      ║
║              Analyzing current directory                 ║
╚══════════════════════════════════════════════════════════╝

[Source]   ft_atoi.c
[Source]   ft_strlen.c
...

Building project...
[SUCCESS] Build completed!

Running norminette...
[SUCCESS] Norminette check passed!

Running Libft test suite from Fortitude...
─────────────────────────────────────────────────────────────
  Part 1 - Libc functions
─────────────────────────────────────────────────────────────
[PASS] ft_isalpha
[PASS] ft_isdigit
...

Summary:
[SUCCESS] Build: OK
[SUCCESS] Norminette: OK
[SUCCESS] Tests: OK
[SUCCESS] Cleanup: OK
```

## Project Structure

```
Fortitude/
├── README.md              # This file
├── LICENSE                # MIT License
├── install.sh             # Linux/macOS installer
├── install.ps1            # Windows installer
├── uninstall.sh           # Uninstaller
├── Makefile               # Build system
├── fortitude.h            # Framework header
├── fortitude.c            # Framework implementation
├── fortitude_runner.c     # Main runner executable
└── tests/
    └── test_libft.c       # Libft test suite
```

## Adding Tests for New Projects

1. Create a test file in `tests/` directory: `test_<project_name>.c`
2. Implement test functions using the assertion macros from `fortitude.h`
3. Organize tests by parts (Part 1, Part 2, Bonus)
4. Update the Makefile to add a test target
5. Update `fortitude_runner.c` to detect and run your project's tests

## Test Organization

Tests are organized by subject parts:

- **Part 1 - Libc functions** - Standard library function implementations
- **Part 2 - Additional functions** - Custom utility functions
- **Bonus** - Optional bonus functions (gracefully handles missing bonus)

## Uninstallation

### Linux/macOS

```bash
curl -fsSL https://raw.githubusercontent.com/yourusername/FORTITUDE/main/uninstall.sh | bash
```

### Windows

Remove the installation directory and remove `%USERPROFILE%\bin` from your PATH.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Designed for 42 school projects
- Inspired by the need for automated testing and validation
