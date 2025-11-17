
# Rosetta-6502

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

**Rosetta-6502** is a cycle-accurate, from-scratch implementation of the MOS 6502 CPU —  
the legendary 8-bit processor found in the Apple II, Commodore 64, NES, Atari 2600,  
and countless embedded systems.

This project aims to be both a **faithful emulator** and a **learning tool**, offering:

- A clean, modern C11 codebase
- A modular bus and memory system
- Extensible MMIO interfaces (software-defined hardware) - **COMING SOON**
- A complete opcode table with per-instruction folders
- Cycle-accurate execution and timing helpers
- A RAM visualizer (ncurses) and execution traces for debugging
- Support for assembling and running real 6502 firmware via `ca65`/`ld65`

Rosetta-6502 is designed to act as a *bridge* (“Rosetta”) between:

### **Classic 8-bit CPUs**
Deeply accurate replication of 6502 hardware behavior.

### **Modern development workflows**
Clean architecture, test suites, modular components, and readable code.

Whether you are building a retro-inspired computer, writing 6502 assembly,  
creating BIOS routines, or studying how classic machines worked internally

---

## Platform Compatibility

Rosetta-6502 currently supports:

- **macOS**
- **Linux**

Other platforms are not officially supported.

---

# Building Rosetta-6502

### Prerequisites

- `clang` or any C11-compatible compiler  
- `make`  
- `ncurses` development headers  
- optional: `cc65` (to build custom 6502 firmware)

### Build

```bash
make
```

Artifacts:

* Executable: `./main`
* Object files: `./build/**`

---

# Running Custom 6502 Firmware

Rosetta-6502 can load and execute **raw 6502 binaries** (produced by `ca65` + `ld65`) using:

```bash
./main --bin firmware.bin
```

Firmware is placed at ROM address `$E000`, then executed from the 6502 reset vector at `$FFFC`.

# Documentation

* [docs/firmware.md](./docs/firmware.md) — building firmware, addressing modes, linker config
* [docs/instructions.md](./docs/instructions.md) — detailed notes on all opcodes 
* [docs/debug.md](./docs/debug.md) — detailed to how debug your firmware

---

# External Resources

* 6502 Tutorials: [http://6502.org/tutorials/](http://6502.org/tutorials/)
* cc65 Documentation: [https://cc65.github.io/doc/](https://cc65.github.io/doc/)
* Unity Test Framework: [https://github.com/ThrowTheSwitch/Unity](https://github.com/ThrowTheSwitch/Unity)

---
