# Repository architecture

CMFS targets the Teensy 4.1 using embedded C++. The current PlatformIO target builds the FreeRTOS LED blink prototype in `fw-flight-computer/`. The December 18, 2026 milestone is a bench prototype for the IREC 2027 program.

`src/main.cpp` initializes the LED, creates the blink task, and starts the scheduler. `app/BlinkTask.cpp` controls the LED through the `IDigitalOutput` interface in `include/cmfs/hal/`. `platform/teensy41/` implements that interface with the Teensy Arduino APIs. Scheduler startup and task timing still need bench verification.

## Planned module boundaries

| Module | Responsibility |
| --- | --- |
| Board startup | Own pin configuration, peripheral initialization, and application startup in `fw-flight-computer/`. |
| Sensor drivers | Own device protocol, sample conversion, and communication errors. Keep the bus interface explicit so conversions can be tested on a host. |
| Flight-state logic | Evaluate state changes from supplied measurements. Keep the interface independent of Teensy and FreeRTOS headers so recorded or simulated measurements can drive host tests. |
| Application tasks | Coordinate periodic sampling, pass measurement snapshots to state evaluation, and publish results for logging and telemetry. |
| RTOS integration | Own FreeRTOS configuration, scheduler startup, and board-specific interrupt integration once a compatible port is validated. |
| Host tools | Decode logs, inspect telemetry, and generate test data under `tools/` as needed. |

Keep the portable modules with the firmware initially. Introduce separate library targets when shared code or host testing requires them.

## Measurements and task ownership

Sensor drivers supply readings or explicit errors. The sampling layer attaches timestamps and validity information, then publishes a coherent snapshot for state evaluation. Logging and telemetry consume measurements and state-change reports through interfaces defined by the application.

Document measurement units, coordinate frames, timestamp sources, and sample periods in the types or interfaces that carry them. Exercise state evaluation with recorded or simulated data, including missing, stale, or invalid samples. Keep simulated inputs isolated from hardware control during bench tests.

For FreeRTOS tasks, document which task owns each peripheral, the lifetime of queue data, and the expected stack, priority, and timing. Validate startup and interrupt ownership for the selected Teensy support and FreeRTOS port. Keep interrupt handlers bounded and use the kernel's ISR-safe APIs when handing work to a task.

## Engineering milestones

| Stage | Evidence |
| --- | --- |
| C++ firmware baseline | Reproducible build for Teensy 4.1 and observable bench bring-up |
| First sensor | Captured measurements with board, breakout, and interface documented |
| Portable state evaluation | Host tests with representative input and error cases |
| FreeRTOS feasibility | Observed scheduler startup and task execution on the selected port |
| December 18 bench prototype | Real sensor snapshots exercised by software state evaluation with results recorded |

Recovery and pyrotechnic outputs remain disconnected during routine bench work. Flight qualification requires a separate review and validation process.

## Open decisions

- C++ language standard, compiler, board support, and build system for the broader firmware baseline.
- Host test framework and the layout of reusable modules.
- FreeRTOS port and configuration ownership.
- Sensor models, interface assignments, sampling rates, and telemetry formats.

See [setup](SETUP.md) for available commands and [development workflow](DEVELOPMENT.md) for reporting test evidence.
