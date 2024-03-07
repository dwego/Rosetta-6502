
# Rosetta 6502 Emulator and Compiler

# Overview
This project combines a 6502 processor emulator with a compiler that translates 6502 assembly code into x64 or x86 assembly. The challenge is heightened by a 65KB RAM constraint.

# Features
1- 6502 Processor Emulation:

Precise 6502 processor emulator supporting original binary code.
Full support for 6502 instructions, addressing modes, and accurate simulation of processor features.

2- 6502 to x64/x86 Compiler:

Compiler translating 6502 assembly into x64 or x86 assembly.
Smart adaptation to differences in instruction sets and features between 6502 and x64/x86 architectures.

3- 65KB RAM Restriction:

All operations comply with the 65KB RAM limit.
Efficient memory management for optimal space utilization.
How to Use
# Compilation
1- Compile 6502 Emulator:

```bash
gcc -o 6502_emulator 6502_emulator.c
```
2- Compile 6502 to x64/x86 Compiler:

```bash
gcc -o 6502_compiler 6502_compiler.c
```
# Execution

1- Run 6502 Emulator:

```bash
./6502_emulator binary_program.bin
```

2- Compile and Run 6502 to x64/x86:

```bash
./6502_compiler input_code_6502.asm -o output_code_x64.asm -a x64
```
```bash
./6502_compiler input_code_6502.asm -o output_code_x86.asm -a x86
```
# Requirements
- GCC Compiler (or any C compiler)
- Development environment supporting target architectures (x64/x86)

## :warning: Note
  
**This software is currently in development and undergoing testing.**
Please be aware that some features may not be fully implemented, and the software might contain bugs.
Use it cautiously and avoid deploying it in production environments until thorough testing has been completed.

