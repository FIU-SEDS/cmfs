# Development setup

CMFS targets the Teensy 4.1 with embedded C++. The current branch has a PlatformIO build for the FreeRTOS LED blink prototype. Toolchain and board support choices for the broader firmware baseline remain open.

## Build the Teensy 4.1 blink prototype

With PlatformIO Core and `just` installed, run from the repository root:

```sh
just --list
just build
```

`just build` runs `pio run -e teensy41` in `fw-flight-computer/` and produces `fw-flight-computer/.pio/build/teensy41/firmware.hex`. PlatformIO compiles `src/`, `app/`, and `platform/teensy41/` using the source filter in [`platformio.ini`](../fw-flight-computer/platformio.ini). Includes such as `app/BlinkTask.hpp` resolve from the firmware project root.

## Format firmware source

Install `clang-format` and make it available on `PATH`. On macOS, the recipe can also discover the formatter provided by Apple’s Command Line Tools through `xcrun`.

```sh
just fmt
```

The recipe applies the root [`.clang-format`](../.clang-format) in place to C and C++ source and headers under `fw-flight-computer/src/`, `app/`, `include/`, and `platform/`. The NXP board files under `boards/`, third-party dependencies, and build output are outside its scope. Review the resulting diff before committing.

## Document the C++ baseline when it lands

- Record the selected toolchain, board support versions, and C++ standard for the firmware baseline.
- Document host build and test commands and lint tools as they are configured.
- Record the approved Teensy programming procedure once it has been verified in a known-safe bench setup.

See the [architecture guide](ARCHITECTURE.md) for planned modules and [development workflow](DEVELOPMENT.md) for how to record validation.
