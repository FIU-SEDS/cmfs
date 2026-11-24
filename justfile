# CMFS developer commands

default:
    @just --list

# Build the FreeRTOS Blink example for Teensy 4.1
build:
    cd fw-flight-computer && pio run -e teensy41

# Configure, build, and run the GoogleTest host tests
test:
    cmake -S fw-flight-computer/tests -B fw-flight-computer/.pio/host-tests
    cmake --build fw-flight-computer/.pio/host-tests
    cd fw-flight-computer/.pio/host-tests && ctest --output-on-failure

# Check application and core C++ sources and headers with Clang
check-app:
    #!/bin/sh
    set -eu
    if ! command -v clangd >/dev/null; then
        echo 'Install clangd and add it to PATH to run just check-app.' >&2
        exit 1
    fi
    cd fw-flight-computer
    pio run -e teensy41 -t compiledb
    driver_glob="${PLATFORMIO_CORE_DIR:-$HOME/.platformio}/packages/toolchain-*/bin/arm*-g++"
    find src/app src/core -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.cc' -o -name '*.h' \) \
        -exec sh -c '
            driver_glob=$1
            shift
            status=0
            for source do
                printf "Checking %s\n" "$source"
                clangd --check="$source" --query-driver="$driver_glob" --tweaks=none --log=error || status=1
            done
            exit "$status"
        ' sh "$driver_glob" {} +

# Build and flash with Teensy Loader CLI
flash: build
    teensy_loader_cli --mcu=TEENSY41 -w -v fw-flight-computer/.pio/build/teensy41/firmware.hex

# Clean the Teensy 4.1 build artifacts
clean:
    cd fw-flight-computer && pio run -e teensy41 -t clean

# Rebuild the Blink example from scratch
rebuild: clean build

# Build and display firmware memory usage
size: build

# Format project-owned firmware with the repository's .clang-format
fmt:
    #!/bin/sh
    set -eu
    formatter=clang-format
    if ! command -v "$formatter" >/dev/null && command -v xcrun >/dev/null; then
        formatter=$(xcrun --find clang-format)
    fi
    find fw-flight-computer/src fw-flight-computer/tests -type f \
        \( -name '*.c' -o -name '*.h' -o -name '*.cpp' -o -name '*.hpp' \) \
        -exec "$formatter" --style=file -i {} +
