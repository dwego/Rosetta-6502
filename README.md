# Rosetta-6502

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

**Rosetta-6502** is an in-development, cycle-accurate virtual machine (VM) emulating the classic 6502 CPU architecture.  
This project aims to build a fully faithful software implementation of the 6502 processor, including its instruction set, clock timing, memory bus, interrupts, and peripherals — enabling users to run 6502 assembly code and ROMs with precise timing and behavior.

---

## Features (In Progress)

- Complete emulation of the 6502 CPU instruction set with cycle-accurate timing  
- Memory management with configurable RAM/ROM mapping and bus interface  
- Clock synchronization for realistic CPU timing  
- Interrupt handling (IRQ, NMI) support  
- Infrastructure prepared for peripherals and memory-mapped I/O devices  
- ROM loading and configuration system planned  
- Debugging support in development  
- Future plans for a GUI frontend for easier interaction and visualization  

---

## Project Goals

- Create a robust and accurate 6502 VM purely in C and C++ with some assembly for critical routines  
- Provide a flexible and extensible architecture allowing easy customization of memory and peripherals  
- Build a reliable platform for learning, debugging, and running 6502 software  
- Eventually develop a graphical interface for real-time control and monitoring  

---

## Getting Started

Currently under active development — no stable releases yet. The core CPU and clock systems are functional, and memory management modules are being integrated.  

Contributions, bug reports, and suggestions are welcome!

---

## License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.
