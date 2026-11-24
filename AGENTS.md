# Agent development guide

Cosmic Messenger Flight Software (CMFS) is the FIU SEDS embedded C++ project for the Teensy 4.1. Read [CONTRIBUTING.MD](CONTRIBUTING.MD) and [docs/SETUP.md](docs/SETUP.md) before editing. Use [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for module ownership and open design decisions. When the documentation and source disagree, inspect the implementation and record any uncertainty.

## Commands

Check the root `justfile` and run `just --list` before using recipes. Use `just build` for the PlatformIO Teensy 4.1 prototype and `just fmt` to apply the root `.clang-format` to project-owned firmware. Host tests are pending configuration. Report only commands actually run.

## Code and architecture

- Follow the [C++ naming conventions](docs/CODING_STYLE.md) when adding or renaming firmware files and identifiers.
- Use C++ for application logic and drivers. Keep board support and C interfaces such as FreeRTOS localized. Document ownership, callback lifetimes, and linkage assumptions at those boundaries.
- Use clear types and explicit ownership. Prefer scoped resource management where appropriate and make failure paths visible. Check target support before relying on standard library facilities, exceptions, RTTI, or dynamic allocation.
- Keep driver code responsible for measurements, board code responsible for peripheral setup, and state evaluation independent of drivers and FreeRTOS. Put board startup and task coordination under `fw-flight-computer/`. Keep host utilities under `tools/`.
- Document units, reference frames, sample periods, and timing assumptions. Handle failed, missing, or stale readings deliberately.
- Prefer bounded work and predictable memory use in critical paths. Document task priorities, stack requirements, synchronization, and peripheral ownership. Keep ISRs short and use ISR-safe APIs.
- Prefer existing board support and dependencies. Verify target compatibility, maintenance, and licenses before adding dependencies. Create libraries or firmware targets when there is a concrete need.

## Verification and hardware

- Add or update host tests for state transitions, sensor conversions, and error handling when behavior changes. Use simulated or recorded input where practical.
- Report host test results, Teensy target compilation, and observations on physical hardware as separate evidence.
- Do not flash a board, change hardware pin mappings, or activate recovery or pyrotechnic outputs without explicit authorization and a known-safe test setup.
- Treat December 18 as a bench demonstration. Report timing and fault behavior only to the extent verified.

## Contributions and documentation

- Follow the branch and review rules in [CONTRIBUTING.MD](CONTRIBUTING.MD). Preserve unrelated work, repository licensing, and attribution. Avoid force-pushing and unrequested history rewrites.
- Keep changes focused. Explain what changed, why, and how it was verified. Update `docs/` when tooling, wiring, APIs, task architecture, or contributor workflows change. Document open engineering decisions as such.
- Do not create issues or pull requests. Do not create remote releases or change remote settings without explicit authorization.
