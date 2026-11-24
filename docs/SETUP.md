# Development setup

CMFS targets the Teensy 4.1 with embedded C++. The current branch has a PlatformIO build for the FreeRTOS LED blink prototype. Toolchain and board support choices for the broader firmware baseline remain open.

## Build the Teensy 4.1 blink prototype

With PlatformIO Core and `just` installed, run from the repository root:

```sh
just --list
just build
```

`just build` runs `pio run -e teensy41` in `fw-flight-computer/` and produces `fw-flight-computer/.pio/build/teensy41/firmware.hex`. PlatformIO compiles firmware under `fw-flight-computer/src/` with [`platformio.ini`](../fw-flight-computer/platformio.ini). Includes such as `app/BlinkTask.hpp` resolve from `src/`.

## Check application and core C++ syntax

Install `clangd` and make it available on `PATH`, then run:

```sh
just check-app
```

The recipe regenerates the Teensy 4.1 compilation database with PlatformIO and uses Clang's parser to check C++ sources and headers under `fw-flight-computer/src/app/` and `fw-flight-computer/src/core/`, including headers that are not yet included by a source file. It returns a nonzero status if a check fails. Use `just build` to also compile and link the firmware.

## Run host tests

See the [host testing guide](TESTING.md) for dependencies and commands on macOS and Linux.

## Format firmware source

Install `clang-format` and make it available on `PATH`. On macOS, the recipe can also discover the formatter provided by Apple’s Command Line Tools through `xcrun`.

```sh
just fmt
```

The recipe applies the root [`.clang-format`](../.clang-format) in place to C and C++ source and headers under `fw-flight-computer/src/` and `fw-flight-computer/tests/`. Third-party dependencies and build output are outside its scope. Review the resulting diff before committing.

## Document the C++ baseline when it lands

- Record the selected toolchain, board support versions, and C++ standard for the firmware baseline.
- Record the approved Teensy programming procedure once it has been verified in a known-safe bench setup.

See the [firmware directory layout](ARCHITECTURE.md#firmware-directory-layout) for where to put code and the [development workflow](DEVELOPMENT.md) for how to record validation.
