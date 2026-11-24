# Cosmic Messenger Flight Software (CMFS)

CMFS is the embedded C++ flight software project for FIU SEDS's Cosmic Messenger avionics platform, developed toward the International Rocket Engineering Competition (IREC) 2027. The initial development board is the Teensy 4.1, based on the NXP i.MX RT1062 (Arm Cortex-M7). A custom flight-computer PCB is a longer-term goal. [FIU SEDS](https://github.com/FIU-SEDS)

## Development status

CMFS is establishing its C++ firmware baseline with a PlatformIO build for a FreeRTOS LED blink prototype on Teensy 4.1. The December 18, 2026 milestone is a bench demonstration of sensor acquisition and software state evaluation.

## Project goals

- Acquire and validate measurements from IMU, barometer, and other selected sensor breakout boards.
- Keep the finite-state machine independent of board APIs so contributors can exercise it with simulated or recorded data on a host computer.
- Evaluate FreeRTOS for coordinating periodic sampling, state evaluation, logging, telemetry, and health monitoring.
- Record host test results, target builds, and bench observations as separate verification evidence.

## Repository layout

| Location | Purpose |
| --- | --- |
| `fw-flight-computer/` | Teensy startup, platform support, application code, and PlatformIO configuration |
| `docs/` | Setup, architecture, and contributor workflow |
| `tools/` | Reserved for host utilities such as log decoders |
| `justfile` | Firmware build and formatting commands |

## Getting started

Follow the setup guide to build with `just build` and format firmware source with `just fmt`.

- [Setup](docs/SETUP.md)
- [Repository architecture](docs/ARCHITECTURE.md)
- [Development workflow](docs/DEVELOPMENT.md)
- [Contributing](CONTRIBUTING.MD)
- [Agent development guide](AGENTS.md)

## Project lineage and acknowledgements

CMFS builds on avionics experience from the FIU SEDS [Vinson](https://github.com/FIU-SEDS/Vinson) and [Orizaba](https://github.com/FIU-SEDS/Orizaba) flight computers. Orizaba was developed for IREC 2025.

The ARIS ASTERIA team's organization of board-specific firmware, reusable libraries, tooling, and documentation inspired the CMFS repository layout. [ARIS ASTERIA Firmware](https://github.com/aris-space/asteria-firmware)

See [LICENSE](LICENSE) and [NOTICE](NOTICE) for licensing and attribution.
