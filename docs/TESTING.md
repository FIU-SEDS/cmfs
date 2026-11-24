# Host testing

The host tests use GoogleTest and CTest to verify the portable flight-state code. They run on your computer and require CMake 3.16 or newer, a C++17 compiler, and an installed GoogleTest development package.

## macOS

If you need a C++ compiler, install Apple's Command Line Tools with `xcode-select --install`. [Apple Command Line Tools](https://developer.apple.com/documentation/xcode/installing-the-command-line-tools)

Install CMake and GoogleTest with Homebrew. [CMake formula](https://formulae.brew.sh/formula/cmake) · [GoogleTest formula](https://formulae.brew.sh/formula/googletest)

```sh
brew install cmake googletest
```

## Linux

### Debian and Ubuntu

```sh
sudo apt update
sudo apt install build-essential cmake libgtest-dev
```

### Fedora

```sh
sudo dnf install gcc-c++ make cmake gtest-devel
```

## Configure, build, and run

Run from the repository root on macOS or Linux:

```sh
just test
```

To run the same steps directly with CMake and CTest:

```sh
cmake -S fw-flight-computer/tests -B fw-flight-computer/.pio/host-tests
cmake --build fw-flight-computer/.pio/host-tests
(cd fw-flight-computer/.pio/host-tests && ctest --output-on-failure)
```

If CMake cannot find `GTestConfig.cmake` and GoogleTest is installed in a custom location, add `-DCMAKE_PREFIX_PATH=/path/to/install-prefix` to the configure command. [CMake package search](https://cmake.org/cmake/help/latest/command/find_package.html#config-mode-search-procedure)
