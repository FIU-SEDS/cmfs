# C++ coding style

Use these naming conventions when adding or renaming files and identifiers in CMFS firmware. Identifier casing follows the [LLVM Coding Standards](https://llvm.org/docs/CodingStandards.html#name-types-functions-variables-and-enumerators-properly). File names follow the CMFS layout and use the project's existing `.hpp` extension for C++ headers.

| Item | Convention | Examples |
| --- | --- | --- |
| C++ module files | Use PascalCase for the base name. Match the primary type or choose a descriptive module name. Use the same base name for the header and implementation when both exist. | `FlightStateMachine.hpp`, `FlightStateMachine.cpp` |
| Classes, structs, enum types, and type aliases | Use PascalCase and descriptive nouns or noun phrases. | `FlightStateMachine`, `MeasurementSnapshot`, `FlightState` |
| Variables, parameters, data members, and named constants | Use PascalCase and choose names that describe the stored value. | `Snapshot`, `CurrentState`, `SamplePeriodMs` |
| Functions and methods | Use lowerCamelCase and choose names that describe the action or query. | `updateState()`, `getCurrentState()`, `hasValidSample()` |
| Scoped enum values | Use PascalCase. The enum type provides context. | `FlightState::Idle`, `FlightState::Boost` |

Keep conventional entry-point file names such as `src/main.cpp` and spell externally defined names as required by their APIs, such as Arduino's `setup()` and `loop()`.

The [formatting recipe](SETUP.md#format-firmware-source) applies the LLVM-based `clang-format` configuration. Check identifier and file naming during code review.
