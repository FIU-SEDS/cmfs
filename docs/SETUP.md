# Development setup

Install Rust with rustup and install `just`. The root `rust-toolchain.toml`
selects stable Rust, rustfmt, Clippy, LLVM tools, and `thumbv7em-none-eabihf`.
For HEX generation, install `cargo-binutils` with `cargo install cargo-binutils`.
Flashing additionally requires `teensy_loader_cli` and a connected Teensy 4.1
in a known-safe bench setup.

Run these commands from the repository root:

```sh
just --list
just build
just hex
just fmt
just fmt-check
just lint
just clean
```

`just flash` builds, generates `fw-flight-computer/cmfs-bringup.hex`, then runs
`teensy_loader_cli --mcu=TEENSY41 -w -v cmfs-bringup.hex` from that directory.
Only run it when hardware flashing is intended and the bench setup is safe.
`just clean` removes Cargo build artifacts; the generated HEX remains until
replaced by `just hex` or removed manually.

To verify the workspace directly:

```sh
cd fw-flight-computer
cargo metadata --no-deps --format-version 1
cargo fmt --all -- --check
cargo build --release
```

To inspect recipe dependencies without flashing, run `just --dry-run flash`
from the repository root. Host tests are not configured yet because `crates/`
is empty. See [ARCHITECTURE.md](ARCHITECTURE.md) for directory responsibilities.
