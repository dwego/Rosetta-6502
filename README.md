# Rosetta-6502

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

Cycle-accurate virtual machine for the MOS 6502 CPU, written in portable C with a focus on faithful timing, extensible memory-mapped peripherals, and approachable tooling for learning and debugging classic 8-bit software.

---

## Why Rosetta-6502?

- End-to-end cycle accuracy: instruction timing, IRQ/NMI handling, and clock synchronization mirror original hardware.
- Modular memory bus: configurable RAM/ROM layout plus hooks for future devices and I/O.
- Exhaustive instruction coverage: every opcode documented and scaffolded for testing/implementation under `src/cpu/Instructions`.
- Built-in diagnostics: configurable logging to `cpu_log.txt` and RAM visualization helpers under `src/utils`.
- Modern tooling: standard `make`/`clang` workflow, Unity-based unit tests, and ncurses-linked executable for rich TUI plans.

---

## Architecture at a Glance

| Layer | Key Files | Notes |
| --- | --- | --- |
| CPU core | `src/cpu/cpu6502.c`, `include/cpu6502.h` | Implements registers, stack, opcode dispatch, and timing helpers. |
| Instruction set | `src/cpu/Instructions/**`, `Instructions.md` | One directory per opcode with documentation + test stubs for incremental completion. |
| Memory & bus | `src/bus/mem6502.c`, `include/mem6502.h`, `include/bus.h` | Abstraction over RAM/ROM ranges, memory-mapped devices, and access control (`access_type.h`). |
| Configuration & logging | `include/config.{h,c}` | Shared typedefs, logging utilities (`open_log`, `close_log`), and platform portability helpers. |
| Utilities | `src/utils/render_ram.*` | Debug visualizers and helpers for future ncurses dashboards. |
| Tests | `tests/` + `libs/unity` | Unity harness compiling emulator sources (excluding `src/main.c`) for fast regression runs. |

---

## Repository Layout

```
.
├── include/           # Public headers shared across build targets
├── libs/unity/        # Vendored Unity test framework
├── src/
│   ├── cpu/           # CPU core + per-opcode documentation/logic
│   ├── bus/           # Memory mapper & bus abstractions
│   ├── utils/         # Visualization/debug helpers
│   └── main.c         # Entrypoint wiring CPU, bus, and CLI
├── tests/             # Unit/integration tests + dedicated Makefile
├── main               # Built executable (created by `make`)
├── cpu_log.txt        # Sample execution log (created at runtime)
└── Makefile           # Default build pipeline (clang + ncurses)
```

---

## Building & Running

### Prerequisites

- `clang` or another C11-compatible compiler
- `make`
- `ncurses` development headers (`libncurses-dev`, `ncurses`, or the platform equivalent)

### Build the emulator

```bash
make
```

Artifacts:

- Executable: `./main`
- Object cache: `./build/**`

### Run

```bash
./main
```

The current binary boots into the configured memory map and will log execution traces to `cpu_log.txt`. As new ROM-loading features land, this section will be expanded with CLI flags and configuration samples.

---

## Configuration, Memory Maps & Logging

- **Config helpers** (`include/config.*`): shared typedefs, platform-safe error handling, and log helpers.
- **Memory map** (`include/memory_map.h`): declares the logical layout (zero page, stack, I/O, ROM). Extend this file to plug in new peripherals or dev cartridges.
- **Logging**: `open_log()` defaults to `cpu_log.txt`; tweak the filename or verbosity before calling `run()` to keep separate traces per scenario.
- **Render tools** (`src/utils/render_ram.*`): helpers for dumping RAM ranges—perfect anchors for future ncurses/GUI panes.


## Additional Resources

- **6502 Instruction Reference**: [Instructions](/src/cpu/Instructions/Instructions.md)
- **Unity Framework Docs**: [Unity Test API](https://github.com/ThrowTheSwitch/Unity)
- **General 6502 References**: [6502.org](http://6502.org/tutorials/)