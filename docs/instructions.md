# MOS 6502 CPU Instruction Set Reference

This document describes all the instructions supported by the MOS Technology 6502 CPU, including their behavior, flags affected, cycles consumed, and addressing modes. It serves as a complete technical reference for emulation or development.

---

## Table of Contents

- [Load and Store Instructions](#load-and-store-instructions)
- [Register Transfers](#register-transfers)
- [Arithmetic and Logic Instructions](#arithmetic-and-logic-instructions)
- [Increment and Decrement Instructions](#increment-and-decrement-instructions)
- [Shift and Rotate Instructions](#shift-and-rotate-instructions)
- [Branch Instructions](#branch-instructions)
- [Jump and Subroutine Instructions](#jump-and-subroutine-instructions)
- [Flag Set and Clear Instructions](#flag-set-and-clear-instructions)
- [Stack Operations](#stack-operations)
- [No Operation](#no-operation)
- [Break Instruction](#break-instruction)

---

## Load and Store Instructions

### LDA - Load Accumulator

- **Operation:** `A ← M`
- **Flags Affected:** Z, N
- **Description:** Loads a byte from memory into the accumulator.
- **Cycles:** 2-4 depending on addressing mode.
- **Addressing Modes:** Immediate, Zero Page, Zero Page,X, Absolute, Absolute,X, Absolute,Y, (Indirect,X), (Indirect),Y

---

### LDX - Load X Register

- **Operation:** `X ← M`
- **Flags Affected:** Z, N
- **Description:** Loads a byte from memory into the X register.
- **Cycles:** 2-4
- **Addressing Modes:** Immediate, Zero Page, Zero Page,Y, Absolute

---

### LDY - Load Y Register

- **Operation:** `Y ← M`
- **Flags Affected:** Z, N
- **Description:** Loads a byte from memory into the Y register.
- **Cycles:** 2-4
- **Addressing Modes:** Immediate, Zero Page, Zero Page,X, Absolute

---

### STA - Store Accumulator

- **Operation:** `M ← A`
- **Flags Affected:** None
- **Description:** Stores the accumulator value into memory.
- **Cycles:** 3-5
- **Addressing Modes:** Zero Page, Zero Page,X, Absolute, Absolute,X, Absolute,Y, (Indirect,X), (Indirect),Y

---

### STX - Store X Register

- **Operation:** `M ← X`
- **Flags Affected:** None
- **Description:** Stores the X register value into memory.
- **Cycles:** 3
- **Addressing Modes:** Zero Page, Zero Page,Y, Absolute

---

### STY - Store Y Register

- **Operation:** `M ← Y`
- **Flags Affected:** None
- **Description:** Stores the Y register value into memory.
- **Cycles:** 3
- **Addressing Modes:** Zero Page, Zero Page,X, Absolute

---

## Register Transfers

### TAX - Transfer Accumulator to X

- **Operation:** `X ← A`
- **Flags Affected:** Z, N
- **Cycles:** 2

---

### TAY - Transfer Accumulator to Y

- **Operation:** `Y ← A`
- **Flags Affected:** Z, N
- **Cycles:** 2

---

### TXA - Transfer X to Accumulator

- **Operation:** `A ← X`
- **Flags Affected:** Z, N
- **Cycles:** 2

---

### TYA - Transfer Y to Accumulator

- **Operation:** `A ← Y`
- **Flags Affected:** Z, N
- **Cycles:** 2

---

### TSX - Transfer Stack Pointer to X

- **Operation:** `X ← SP`
- **Flags Affected:** Z, N
- **Cycles:** 2

---

### TXS - Transfer X to Stack Pointer

- **Operation:** `SP ← X`
- **Flags Affected:** None
- **Cycles:** 2

---

## Arithmetic and Logic Instructions

### ADC - Add with Carry

- **Operation:** `A ← A + M + C`
- **Flags Affected:** C, Z, N, V
- **Description:** Adds memory and carry flag to accumulator.
- **Cycles:** 2-4
- **Addressing Modes:** Immediate, Zero Page, Zero Page,X, Absolute, Absolute,X, Absolute,Y, (Indirect,X), (Indirect),Y

---

### SBC - Subtract with Carry

- **Operation:** `A ← A - M - (1 - C)`
- **Flags Affected:** C, Z, N, V
- **Cycles:** 2-4
- **Addressing Modes:** Same as ADC

---

### AND - Logical AND

- **Operation:** `A ← A & M`
- **Flags Affected:** Z, N
- **Cycles:** 2-4
- **Addressing Modes:** Same as ADC

---

### ORA - Logical OR

- **Operation:** `A ← A | M`
- **Flags Affected:** Z, N
- **Cycles:** 2-4
- **Addressing Modes:** Same as ADC

---

### EOR - Exclusive OR

- **Operation:** `A ← A ^ M`
- **Flags Affected:** Z, N
- **Cycles:** 2-4
- **Addressing Modes:** Same as ADC

---

### CMP - Compare Accumulator

- **Operation:** `A - M`
- **Flags Affected:** C, Z, N
- **Description:** Compares A and memory by subtracting without storing result.
- **Cycles:** 2-4
- **Addressing Modes:** Same as ADC

---

### CPX - Compare X Register

- **Operation:** `X - M`
- **Flags Affected:** C, Z, N
- **Cycles:** 2-3
- **Addressing Modes:** Immediate, Zero Page, Absolute

---

### CPY - Compare Y Register

- **Operation:** `Y - M`
- **Flags Affected:** C, Z, N
- **Cycles:** 2-3
- **Addressing Modes:** Immediate, Zero Page, Absolute

---

## Increment and Decrement Instructions

### INC - Increment Memory

- **Operation:** `M ← M + 1`
- **Flags Affected:** Z, N
- **Cycles:** 5-6
- **Addressing Modes:** Zero Page, Zero Page,X, Absolute, Absolute,X

---

### INX - Increment X Register

- **Operation:** `X ← X + 1`
- **Flags Affected:** Z, N
- **Cycles:** 2

---

### INY - Increment Y Register

- **Operation:** `Y ← Y + 1`
- **Flags Affected:** Z, N
- **Cycles:** 2

---

### DEC - Decrement Memory

- **Operation:** `M ← M - 1`
- **Flags Affected:** Z, N
- **Cycles:** 5-6
- **Addressing Modes:** Zero Page, Zero Page,X, Absolute, Absolute,X

---

### DEX - Decrement X Register

- **Operation:** `X ← X - 1`
- **Flags Affected:** Z, N
- **Cycles:** 2

---

### DEY - Decrement Y Register

- **Operation:** `Y ← Y - 1`
- **Flags Affected:** Z, N
- **Cycles:** 2

---

## Shift and Rotate Instructions

### ASL - Arithmetic Shift Left

- **Operation:** `M ← M << 1` or `A ← A << 1`
- **Flags Affected:** C, Z, N
- **Cycles:** 2-6
- **Addressing Modes:** Accumulator, Zero Page, Zero Page,X, Absolute, Absolute,X

---

### LSR - Logical Shift Right

- **Operation:** `M ← M >> 1` or `A ← A >> 1`
- **Flags Affected:** C, Z, N
- **Cycles:** 2-6
- **Addressing Modes:** Same as ASL

---

### ROL - Rotate Left

- **Operation:** `M ← (M << 1) + C` or `A ← (A << 1) + C`
- **Flags Affected:** C, Z, N
- **Cycles:** 2-6
- **Addressing Modes:** Same as ASL

---

### ROR - Rotate Right

- **Operation:** `M ← (C << 7) + (M >> 1)` or `A ← (C << 7) + (A >> 1)`
- **Flags Affected:** C, Z, N
- **Cycles:** 2-6
- **Addressing Modes:** Same as ASL

---

## Branch Instructions

All branch instructions use relative addressing and conditionally change the program counter.

| Instruction | Condition                            | Cycles            |
|-------------|------------------------------------|-------------------|
| BPL         | Branch if Positive (N=0)            | 2 (+1 if branch taken, +2 if page crossed) |
| BMI         | Branch if Negative (N=1)            | Same as BPL       |
| BVC         | Branch if Overflow Clear (V=0)      | Same as BPL       |
| BVS         | Branch if Overflow Set (V=1)        | Same as BPL       |
| BCC         | Branch if Carry Clear (C=0)         | Same as BPL       |
| BCS         | Branch if Carry Set (C=1)           | Same as BPL       |
| BEQ         | Branch if Equal (Z=1)                | Same as BPL       |
| BNE         | Branch if Not Equal (Z=0)            | Same as BPL       |

---

## Jump and Subroutine Instructions

### JMP - Jump

- **Operation:** `PC ← address`
- **Cycles:** 3
- **Addressing Modes:** Absolute, Indirect

---

### JSR - Jump to Subroutine

- **Operation:** Push (PC - 1) to stack, then `PC ← address`
- **Cycles:** 6
- **Addressing Modes:** Absolute

---

### RTS - Return from Subroutine

- **Operation:** Pull PC from stack, increment PC by 1
- **Cycles:** 6

---

## Flag Set and Clear Instructions

| Instruction | Description        | Flags Affected | Cycles |
|-------------|--------------------|----------------|--------|
| CLC         | Clear Carry Flag    | C cleared      | 2      |
| SEC         | Set Carry Flag      | C set          | 2      |
| CLI         | Clear Interrupt    | I cleared      | 2      |
| SEI         | Set Interrupt      | I set          | 2      |
| CLV         | Clear Overflow     | V cleared      | 2      |
| CLD         | Clear Decimal Mode | D cleared      | 2      |
| SED         | Set Decimal Mode   | D set          | 2      |

---

## Stack Operations

### PHA - Push Accumulator

- **Operation:** Push A onto stack
- **Cycles:** 3

---

### PHP - Push Processor Status

- **Operation:** Push flags onto stack
- **Cycles:** 3

---

### PLA - Pull Accumulator

- **Operation:** Pull A from stack, set flags Z and N
- **Cycles:** 4

---

### PLP - Pull Processor Status

- **Operation:** Pull flags from stack
- **Cycles:** 4

---

## No Operation

### NOP

- **Operation:** No operation
- **Cycles:** 2

---

## Break Instruction

### BRK - Force Interrupt

- **Operation:** Push PC+2 and flags, set interrupt disable flag, jump to IRQ vector
- **Cycles:** 7

---

# Addressing Modes Summary

| Mode           | Description                              | Bytes | Notes                       |
|----------------|------------------------------------------|-------|-----------------------------|
| Immediate (IMM) | Operand is a constant                    | 2     | Example: LDA #$10           |
| Zero Page (ZP) | Address in zero page (first 256 bytes)  | 2     | Wraps around 0x00-0xFF      |
| Zero Page,X (ZPX) | Zero page address plus X               | 2     | Wraps in zero page          |
| Zero Page,Y (ZPY) | Zero page address plus Y               | 2     | Wraps in zero page          |
| Absolute (ABS) | Full 16-bit address                      | 3     |                             |
| Absolute,X (ABSX) | Absolute address plus X                 | 3     | May add cycle if page crossed|
| Absolute,Y (ABSY) | Absolute address plus Y                 | 3     | May add cycle if page crossed|
| Indirect (IND) | Used only by JMP, address read from addr| 3     | Reads pointer address       |
| Indexed Indirect (INDX) | (Zero Page,X) Indirect addressing  | 2     | Reads pointer + X           |
| Indirect Indexed (INDY) | (Zero Page), Indirect + Y         | 2     | Reads pointer + Y, may add cycle |

---

# Notes:

- Flags affected:
  - **C** = Carry
  - **Z** = Zero
  - **I** = Interrupt Disable
  - **D** = Decimal Mode
  - **B** = Break Command
  - **V** = Overflow
  - **N** = Negative (Sign)

- Cycle counts vary slightly depending on addressing mode and page boundary crossing.

---

### Sources and Inspiration

- Official MOS Technology 6502 documentation and datasheets  
- [6502.org](https://www.6502.org) — Community and detailed technical resources  
- [*Emulating a CPU in C++ (6502)*](https://www.youtube.com/watch?v=qJgsuQoy9bc&list=PLLwK93hM93Z13TRzPx9JqTIn33feefl37) by Dave Poo (YouTube) —  

