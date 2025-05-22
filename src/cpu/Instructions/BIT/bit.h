#ifndef BIT_H
#define BIT_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the BIT (Bit Test) instruction for MOS Technology
   6502. BIT tests bits in memory against the Accumulator without changing the
   Accumulator. It affects the Negative, Overflow, and Zero flags based on the
   result.

   For more information about the instructions, refer to Instructions.MD
*/

/*
   BIT (Bit Test) instruction supports various addressing modes in the 6502
   architecture. The different modes provide flexibility in specifying the
   source of the data for the test.
*/

/*
   This function sets the Flags for the Status register
   to reflect the result of the BIT instruction.
*/

static inline void
BITSetStatus (Byte Value, CPU6502 *cpu)
{
  cpu->Flag.N = get_bit (Value, 7);
  cpu->Flag.V = get_bit (Value, 6);
  cpu->Flag.Z = (cpu->A & Value) == 0;
}

/*
   BIT_ZP - Bit Test with Zero Page addressing.
   This function fetches a byte representing a zero-page address from memory,
   reads the value at that address, and performs the BIT test.
   It then sets the status flags accordingly.
*/

static inline void
BIT_ZP (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);
  Byte Value = ReadByte (Cycles, ZeroPageAddr, memory);
  BITSetStatus (Value, cpu);
  spend_cycles (3);
}

/*
   BIT_ABS - Bit Test with Absolute addressing.
   This function fetches a two-byte absolute address from memory,
   reads the value at that address, and performs the BIT test.
   It then sets the status flags accordingly.
*/

static inline void
BIT_ABS (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);
  Byte Value = ReadByte (Cycles, Absolute, memory);
  BITSetStatus (Value, cpu);
  spend_cycles (4);
}

#endif // BIT_H
