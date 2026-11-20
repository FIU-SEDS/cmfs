# CMFS developer commands

default:
    @just --list

# Build the FreeRTOS Blink example for Teensy 4.1
build:
    cd fw-flight-computer && pio run -e teensy41

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
    find fw-flight-computer/src fw-flight-computer/app \
        fw-flight-computer/include fw-flight-computer/platform -type f \
        \( -name '*.c' -o -name '*.h' -o -name '*.cpp' -o -name '*.hpp' \) \
        -exec "$formatter" --style=file -i {} +
