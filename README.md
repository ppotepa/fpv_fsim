# FPV Flight Simulator (fpv_fsim)

A C++ drone simulation project using ECS architecture, designed for Windows development and ARM64 production deployment.

## Architecture

- **Mini-domain architecture** with IoC (Inversion of Control)
- **Entity-Component-System (ECS)** pattern
- **Event-driven communication** via EventBus
- **Fixed timestep physics** for determinism

## Toolchain

### Development Environment (Windows)

- **Compiler:** MinGW-w64 (GCC) or Clang
- **Build System:** CMake
- **Libraries:** SDL2, OpenGL
- **Editor:** Visual Studio Code with C/C++ extensions

### Production Environment (ARM64 Cortex-A53)

- **Cross-Compiler:** aarch64-linux-gnu-g++
- **Libraries:** SDL2 compiled for ARM64, OpenGL ES

## Building

### Prerequisites

1. Install MinGW-w64: Download from https://www.mingw-w64.org/ and add to PATH.
2. Install CMake: Download from https://cmake.org/download/ and add to PATH.
3. Install SDL2: Download development libraries for MinGW from https://www.libsdl.org/download-2.0.php and place in appropriate directories.
4. Install OpenGL: Usually included with MinGW.

### Build Steps

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
make
```

### Cross-Compilation for ARM64

Create a toolchain file `toolchain-arm64.cmake`:

```cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
```

Then:

```bash
mkdir build-arm64
cd build-arm64
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-arm64.cmake
make
```

## Project Structure

See `codemap.xml` for detailed code structure.

## Contributing

Follow SOLID principles, IoC, and Clean Code practices.
