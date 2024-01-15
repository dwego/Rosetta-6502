
# Rosetta 6502 Emulator and Compiler

# Overview
This project combines a 6502 processor emulator with a compiler that translates 6502 assembly code into x64 or x86 assembly. The challenge is heightened by a 65KB RAM constraint.

# Features
6502 Processor Emulation:

Precise 6502 processor emulator supporting original binary code.
Full support for 6502 instructions, addressing modes, and accurate simulation of processor features.
6502 to x64/x86 Compiler:

Compiler translating 6502 assembly into x64 or x86 assembly.
Smart adaptation to differences in instruction sets and features between 6502 and x64/x86 architectures.
65KB RAM Restriction:

All operations comply with the 65KB RAM limit.
Efficient memory management for optimal space utilization.
How to Use
Compilation:
Compile 6502 Emulator:

bash
Copy code
gcc -o 6502_emulator 6502_emulator.c
Compile 6502 to x64/x86 Compiler:

bash
Copy code
gcc -o 6502_compiler 6502_compiler.c
Execution:
Run 6502 Emulator:

bash
Copy code
./6502_emulator binary_program.bin
Compile and Run 6502 to x64/x86:

bash
Copy code
./6502_compiler input_code_6502.asm -o output_code_x64.asm -a x64
bash
Copy code
./6502_compiler input_code_6502.asm -o output_code_x86.asm -a x86
Requirements
GCC Compiler (or any C compiler)
Development environment supporting target architectures (x64/x86)
Contributions
Contributions are welcome! Open issues, propose improvements, or submit pull requests.

