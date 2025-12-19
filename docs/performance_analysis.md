# Libigl Python Bindings Performance Analysis

## 1. Build System Overview

The project uses a modern Python build system orchestrated by `scikit-build-core` and `CMake`.

*   **`pyproject.toml`**: This is the entry point. It declares `scikit-build-core` as the build backend.
    *   Defines build requirements (`cmake`, `nanobind`, `scikit-build-core`).
    *   Configures `cibuildwheel` to build for `auto64` architectures.

*   **`CMakeLists.txt`**: This controls the actual compilation.
    *   It uses `FetchContent` to download `nanobind` (v2.7.0) and `libigl` (v2.6.0) directly during the build.
    *   It compiles the C++ code into a Python module using `nanobind_add_module`.

*   **CI/CD (`.github/workflows/wheels.yml`)**: This workflow automates the wheel creation for different platforms using `cibuildwheel`.
    *   Defines the matrix for OS (`ubuntu`, `macos`, `windows`) and Architecture (`x86_64`, `arm64`).

## 2. Platform Differences (macOS vs. Linux / x86_64 vs. arm64)

The build process is largely uniform across platforms, but the **compilers** and **default flags** differ significantly, which is the likely cause of the performance discrepancy.

### A. Compiler Differences
*   **Linux (Ubuntu)**: Uses **GCC** by default.
*   **macOS**: Uses **Apple Clang**.
*   **Impact**: Clang and GCC have different default optimization levels and vectorization strategies. The regression being absent on macOS suggests Clang might be generating better code for the new `libigl` version or handling the `Eigen` dependency better by default.

### B. Architecture & Vectorization (The "Generic" Build Problem)
The wheels are built for distribution (e.g., `manylinux`), which forces them to be compatible with a wide range of CPUs.

*   **x86_64 (Linux/Intel Mac)**:
    *   By default, compilers often target a "lowest common denominator" instruction set (e.g., SSE2) to ensure the wheel runs on old CPUs.
    *   **The Problem**: `libigl` and `Eigen` rely heavily on **AVX/AVX2** instructions for performance. If these flags are not explicitly enabled, the code runs in a scalar or poorly vectorized mode, causing significant slowdowns.
    *   The `CMakeLists.txt` sets `CMAKE_BUILD_TYPE` to `Release` but **does not** appear to enable architecture-specific flags like `-march=native` (which you can't use for distributed wheels) or specific AVX flags.

*   **arm64 (Apple Silicon / Linux ARM)**:
    *   The baseline for `arm64` includes **NEON** vectorization.
    *   **Why it's faster**: Since NEON is guaranteed to be present on all standard `arm64` chips, compilers can safely optimize for it without breaking compatibility. This likely explains why the regression is smaller or non-existent on ARM platforms.

## 3. Investigation Hypothesis

The issue report mentions a switch from **Scipy** (which links to optimized BLAS/LAPACK libraries like OpenBLAS or MKL) to **Eigen** (header-only) in `libigl` 2.6.0.

1.  **Missing Vectorization**: On Linux x86_64, the wheel is likely being compiled without AVX2 support. The old version (2.5.1) might have relied on Scipy's pre-compiled, highly optimized BLAS, whereas the new version relies on Eigen compiling correctly on the fly. If Eigen compiles without AVX, it is much slower.
2.  **Compiler Flags**: Explicitly enabling AVX2 for x86_64 builds (at the cost of dropping support for very old CPUs) or using runtime dispatching is required to restore performance.
