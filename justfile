# CMFS Development Commands

# Show available commands
default:
    @just --list

# ==========================================
# Firmware
# ==========================================

# Compile release firmware
build:
    cd fw-flight-computer && cargo build --release

# Generate Teensy 4.1 HEX firmware
hex: build
    cd fw-flight-computer && cargo objcopy --release -p cmfs-flight-computer --bin cmfs-flight-computer -- -O ihex cmfs-bringup.hex

# Flash firmware onto Teensy 4.1
flash: hex
    cd fw-flight-computer && teensy_loader_cli --mcu=TEENSY41 -w -v cmfs-bringup.hex

# ==========================================
# Code Quality
# ==========================================

# Format Rust source code
fmt:
    cd fw-flight-computer && cargo fmt --all

# Verify formatting without modifying files
fmt-check:
    cd fw-flight-computer && cargo fmt --all -- --check

# Run Clippy
lint:
    cd fw-flight-computer && cargo clippy --workspace --bins

# ==========================================
# Testing
# ==========================================

# Run quality checks
ci-checks: fmt-check lint

# ==========================================
# Maintenance
# ==========================================

# Remove compiled artifacts
clean:
    cd fw-flight-computer && cargo clean
