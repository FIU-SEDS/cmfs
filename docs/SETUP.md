# Development setup

CMFS targets the Teensy 4.1 with embedded C++. The C++ toolchain, language standard, board support, and build configuration are open decisions. Firmware builds, host tests, formatting, and flashing commands are pending the C++ baseline.

## Inspect available recipes

If `just` is installed, run this from the repository root:

```sh
just --list
```

The list includes recipes from the previous Rust firmware. The build, format, lint, and flash recipes still call Cargo directly or through dependencies. They require the former Rust workspace and cannot build or program C++ firmware.

## Document the C++ baseline when it lands

- Record how to install the compiler and board support, including supported versions and the selected C++ standard.
- Describe the firmware target, required dependencies, build invocation, and output artifact paths.
- Document the host build and test commands and any formatting or lint tools configured in the repository.
- Record the approved Teensy programming procedure once it has been verified in a known-safe bench setup.

See the [architecture guide](ARCHITECTURE.md) for planned modules and [development workflow](DEVELOPMENT.md) for how to record validation.
