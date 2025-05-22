#ifndef ASL_H
#define ASL_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the ASL (Arithmetic Shift Left) instruction for
   MOS Technology 6502. ASL shifts a value one bit to the left, storing the
   result in the Accumulator or memory, affecting the Carry, Zero, and Negative
   flags. For more information about the instruction, refer to Instructions.MD.
*/

/*
   ASL (Arithmetic Shift Left) instruction for the MOS Technology 6502 CPU.

   The ASL instruction shifts all bits of the operand one bit to the left.
   Bit 7 is moved into the Carry flag, bit 0 is set to zero.
   This operation effectively multiplies the operand by two.

   The result is stored back in either the Accumulator or memory, depending on
   the addressing mode.

   Flags affected:
   - Carry (C): Set to the value of the bit shifted out (bit 7).
   - Zero (Z): Set if the result is zero.
   - Negative (N): Set according to the new bit 7 of the result.
*/

/*
   This function sets the Flags in the Status register to reflect
   the outcome of the ASL operation on the Accumulator.
*/

static inline void
ASLSetStatus (Byte value, CPU6502 *cpu)
{
  cpu->Flag.C = (value & 0x80) ? 1 : 0;
  cpu->Flag.Z = (cpu->A == 0);
  cpu->Flag.N = (cpu->A & 0x80) != 0;
}

/*
   ASL_ACC - Arithmetic Shift Left on the Accumulator.
   This function fetches a byte from memory, shifts it left by one bit,
   stores the result in the Accumulator, and sets the status flags.
*/

static inline void
ASL_ACC (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte value = FetchByte (Cycles, memory, cpu);
  cpu->A = value << 1;
  ASLSetStatus (value, cpu);
}

/*
   ASL_ZP - Arithmetic Shift Left on a Zero Page address.
   This function fetches a zero page address from memory, reads the value at
   that address, shifts it left by one bit, stores the result back if needed
   (not shown here), and sets the status flags. It adjusts the cycle count
   accordingly.
*/

static inline void
ASL_ZP (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte zero_page_addr = FetchByte (Cycles, memory, cpu);
  Byte value = ReadByte (Cycles, zero_page_addr, memory);

  cpu->A = value << 1;
  (*Cycles) -= 2;
  ASLSetStatus (value, cpu);
  spend_cycles (5);
}

/*
   ASL_ZPX - Arithmetic Shift Left on a Zero Page address with X offset.
   This function adds the X register to the zero page address, reads the value,
   shifts it left by one bit, stores the result, adjusts cycles, and sets
   flags.
*/

static inline void
ASL_ZPX (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte zero_page_addr = FetchByte (Cycles, memory, cpu);
  zero_page_addr += cpu->X;
  (*Cycles)--;

  Byte value = ReadByte (Cycles, zero_page_addr, memory);
  cpu->A = value << 1;
  (*Cycles) -= 2;
  ASLSetStatus (value, cpu);
  spend_cycles (6);
}

/*
   ASL_ABS - Arithmetic Shift Left on an Absolute address.
   This function fetches a two-byte absolute address, reads the value,
   shifts it left by one bit, stores the result, adjusts cycles, and sets
   flags.
*/

static inline void
ASL_ABS (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Word absolute = FetchWord (Cycles, memory, cpu);
  Byte value = ReadByte (Cycles, absolute, memory);

  cpu->A = value << 1;
  (*Cycles) -= 2;
  ASLSetStatus (value, cpu);
  spend_cycles (6);
}

/*
   ASL_ABSX - Arithmetic Shift Left on an Absolute address with X offset.
   This function adds the X register to the absolute address, reads the value,
   shifts it left by one bit, stores the result, adjusts cycles, and sets
   flags.
*/

static inline void
ASL_ABSX (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Word absolute = FetchWord (Cycles, memory, cpu);
  absolute += cpu->X;

  Byte value = ReadByte (Cycles, absolute, memory);
  cpu->A = value << 1;
  (*Cycles) -= 3;
  ASLSetStatus (value, cpu);
  spend_cycles (6);
}

#endif /* ASL_H */
