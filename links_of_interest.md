# Links of Interest

## Compiler Installation

### Windows
- **MSYS2** (provides GCC via MinGW-w64): https://www.msys2.org/
  - After installing, open the MSYS2 terminal and run:
    ```
    pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
    ```
  - Add `C:\msys64\ucrt64\bin` to your system PATH

### Linux
- GCC is typically pre-installed. If not:
  ```
  sudo apt install g++ cmake ninja-build    # Ubuntu/Debian
  sudo dnf install gcc-c++ cmake ninja-build # Fedora
  ```

### macOS
- Clang (default):
  ```
  xcode-select --install
  ```
- CMake and Ninja via Homebrew:
  ```
  brew install cmake ninja
  ```

## Build Tools
- **CMake**: https://cmake.org/
- **Ninja**: https://ninja-build.org/

## Code Editor (optional)

The book uses terminal commands to build and run all projects. Any editor works — just open the chapter folder and use the integrated terminal (or a standalone one) to run:

```
cmake -B build -G Ninja
cmake --build build
```

If you don't have a preferred editor, we recommend **Visual Studio Code** for its cross-platform support (Windows, macOS, Linux):

- **VS Code**: https://code.visualstudio.com/
  - Recommended extensions:
    - **C/C++** (Microsoft) — syntax highlighting, IntelliSense, debugging
    - **CMake Tools** (Microsoft) — auto-detects CMakeLists.txt, configure/build/run from the editor

## Code Search (terminal-first, optional)

As the engine grows, you'll need to navigate the codebase quickly. If you're using an IDE, its built-in search handles this. If you prefer working terminal-first, the tools below are current best-in-class recommendations for searching code from the command line. These specific tools may change over time, but the need to search code efficiently won't — check this document for up-to-date suggestions.

- **ripgrep** (`rg`) — fast code search: https://github.com/BurntSushi/ripgrep
  - Examples:
    ```
    rg "ProcessInput"              # Find every mention across the codebase
    rg "class Engine"              # Find class declarations
    rg "void.*Update" --type cpp   # Regex search, C++ files only
    ```
  - Install:
    - Windows (MSYS2): `pacman -S mingw-w64-ucrt-x86_64-ripgrep`
    - Linux: `sudo apt install ripgrep`
    - macOS: `brew install ripgrep`

- **fzf** — interactive fuzzy finder, pairs well with ripgrep: https://github.com/junegunn/fzf
  - Install:
    - Windows (MSYS2): `pacman -S mingw-w64-ucrt-x86_64-fzf`
    - Linux: `sudo apt install fzf`
    - macOS: `brew install fzf`
