# Repository architecture

CMFS targets the Teensy 4.1 (NXP i.MX RT1062, ARM Cortex-M7).
Each board's firmware lives in its own Cargo workspace. The current workspace
contains one application, `cmfs-bringup`.

```text
cmfs/
├── crates/                     # Reserved for reusable Rust libraries
├── docs/                       # Setup and engineering documentation
├── fw-flight-computer/
│   ├── .cargo/config.toml      # Embedded target and linker flags
│   ├── Cargo.toml              # Workspace members and resolver
│   ├── Cargo.lock              # Resolved firmware dependencies
│   └── app/
│       ├── Cargo.toml          # cmfs-bringup package and dependencies
│       └── src/main.rs         # Firmware entry point and board initialization
├── just/                       # Reserved for shared just recipes
├── tools/                      # Reserved for host-side utilities
├── justfile                    # Development commands run from the repository root
└── rust-toolchain.toml         # Rust toolchain, components, and embedded target
```

`fw-flight-computer/Cargo.toml` defines the workspace; application dependencies
belong in `app/Cargo.toml`. Any future workspace build profiles belong in the
workspace manifest. The workspace owns a single `Cargo.lock` and `target/`
directory. Run Cargo from `fw-flight-computer/` so it discovers `.cargo/config.toml`,
which selects `thumbv7em-none-eabihf` and the BSP-provided `t4link.x` linker script.

`app/src/main.rs` owns the `no_std`/`no_main` entry point, Teensy BSP initialization,
and panic-handler selection. It currently runs a buzzer bench demonstration on
pin 6. FreeRTOS integration is not implemented by this restructuring.

As functionality grows, reusable drivers and hardware-independent flight logic
belong in `crates/`. Drivers acquire measurements; flight logic evaluates state
transitions; application tasks coordinate timing and communication. `crates/` is
currently empty and has no host-test workspace. Likewise, `just/` and `tools/` are
reserved directories rather than implemented tooling.

Example:
Hardware-independent flight-state logic belongs in crates/, for example a future crates/flight-core/ library.
That library would define flight states and transition rules using measurements passed to it. It shouldn’t directly read sensors or call FreeRTOS.
fw-flight-computer/app/ would initialize hardware, coordinate sensor readings, pass measurements into the state machine, and act on its results.
This separation lets you test transitions on your computer with simulated measurements, without needing the Teensy.


`just build` produces the ELF at
`fw-flight-computer/target/thumbv7em-none-eabihf/release/cmfs-bringup`.
`just hex` builds first and writes `fw-flight-computer/cmfs-bringup.hex`.
`just flash` generates that HEX file before invoking the Teensy loader from the
firmware workspace. Generated artifacts must not be committed.

See [SETUP.md](SETUP.md) for prerequisites and verification commands. Compilation
and HEX generation do not establish hardware validation or flight qualification.
