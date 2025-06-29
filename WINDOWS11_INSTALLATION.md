# Windows 11 Installation Guide for Binance Connector C++

This guide provides step-by-step instructions to set up the Binance Connector C++ project on Windows 11.

## Prerequisites
- Windows 11
- Administrator privileges (for some installations)
- Internet connection

## Step 1: Download and Install Miniconda

1. Go to: https://docs.conda.io/projects/conda/en/stable/user-guide/install/windows.html
2. Download the Windows installer (64-bit)
3. Run the installer and follow the installation wizard
4. **IMPORTANT**: Check "Add Miniconda3 to my PATH environment variable" during installation
5. Complete the installation

## Step 2: Install MSYS2 (for GCC and build tools)

1. Go to: https://www.msys2.org/
2. Download the MSYS2 installer
3. Run the installer and follow the installation wizard
4. After installation, open "MSYS2 MinGW x64" terminal (not PowerShell)
5. Run these commands in sequence:

```bash
# Update the package database and core system packages
pacman -Syu

# Install GCC compiler
pacman -S mingw-w64-x86_64-gcc

# Install CMake
pacman -S mingw-w64-x86_64-cmake

# Install Make
pacman -S mingw-w64-x86_64-make
```

6. **Add to Windows PATH**: Add `C:\msys64\mingw64\bin` to your system PATH
   - Open System Properties → Advanced → Environment Variables
   - Edit the "Path" variable
   - Add new entry: `C:\msys64\mingw64\bin`
   - Click OK to save

## Step 3: Install CMake (Alternative Method)

If you prefer to install CMake separately:
1. Go to: https://cmake.org/download/
2. Download "Windows x64 Installer"
3. Run the installer
4. **IMPORTANT**: Check "Add CMake to the system PATH for all users" during installation

## Step 4: Setup Conda Environment

Open a new Command Prompt or PowerShell and run:

```powershell
# Create conda environment
conda create -n binanceconnectorcpp python pip

# Activate the environment
conda activate binanceconnectorcpp

# Install Conan
pip install conan
```

## Step 5: CONAN SETUP

```powershell
# Detect and create profile
conan profile detect --name binanceconnectorcpp
```

## Step 6: Update Compiler Settings

1. Navigate to: `%USERPROFILE%\.conan2\profiles\binanceconnectorcpp`
2. Open the profile file in a text editor (Notepad, VS Code, etc.)
3. Make these changes:
   - Change `compiler.cppstd=gnuXX` to `compiler.cppstd=gnu23`
   - Ensure `compiler=gcc` (not msvc)
   - Ensure `compiler.libcxx=libstdc++11`

Example profile content:
```ini
[settings]
arch=x86_64
build_type=Release
compiler=gcc
compiler.cppstd=gnu23
compiler.libcxx=libstdc++11
compiler.version=13
os=Windows

[buildenv]
CC=gcc
CXX=g++
```

## Step 7: Verify Installation

Open a new PowerShell window and verify all tools are available:

```powershell
# Check GCC
gcc --version

# Check CMake
cmake --version

# Check Make
mingw32-make --version

# Check Conan
conan --version
```

All commands should return version information without errors.

## Step 8: Build the Project

Navigate to your project directory and run:

```powershell
# Install dependencies (run only the first time)
conan install . --output-folder=build -s build_type=Debug --build=missing --profile:host binanceconnectorcpp --profile:build=binanceconnectorcpp

# Build the project
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

## Troubleshooting

### Common Issues:

1. **"cmake not found"**
   - Ensure CMake is installed and added to PATH
   - Restart PowerShell after installation

2. **"gcc not found"**
   - Ensure MSYS2 is installed and `C:\msys64\mingw64\bin` is in PATH
   - Restart PowerShell after adding to PATH

3. **"mingw32-make not found"**
   - Install with: `pacman -S mingw-w64-x86_64-make`
   - Ensure `C:\msys64\mingw64\bin` is in PATH

4. **"conan not found"**
   - Ensure conda environment is activated: `conda activate binanceconnectorcpp`
   - Reinstall conan: `pip install conan`

5. **Build errors**
   - Ensure all dependencies are installed
   - Check that the conan profile is correctly configured
   - Try cleaning and rebuilding: `rm -rf build && mkdir build`

### PowerShell Execution Policy Issues:
If you get execution policy errors:
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

## Alternative: Using Ninja Build System (Optional)

If you prefer faster builds, you can optionally install and use Ninja instead of Make:

```bash
# Install Ninja (optional - only if you want faster builds)
pacman -S mingw-w64-x86_64-ninja
```

Then build with Ninja:
```powershell
# Build with Ninja
cmake .. -G "Ninja"
cmake --build .
```

## Environment Variables Summary

Make sure these are in your system PATH:
- `C:\msys64\mingw64\bin` (for GCC, Make, CMake)
- `C:\Users\<username>\miniconda3\Scripts` (for conda)
- `C:\Users\<username>\miniconda3\Library\bin` (for conda)

## Next Steps

After successful installation and build:
1. Run tests: `ctest` (if available)
2. Check the generated executables in the `build` directory
3. Refer to the main README.md for usage instructions

## Support

If you encounter issues:
1. Check that all tools are properly installed and in PATH
2. Verify the conan profile settings
3. Ensure you're using the correct conda environment
4. Check the troubleshooting section above 