#ifndef CMP_H
#define CMP_H

#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the CMP (Compare Accumulator) instruction for MOS
   Technology 6502. CMP compares the Accumulator register (A) with a value
   fetched from memory and updates the CPU status flags accordingly. For more
   information about the instructions, refer to Instructions.MD
*/

/*
   CMP instruction compares the Accumulator (A) with a value by subtracting it
   from A (without storing the result). It updates the flags as follows:
   - Carry (C) is set if A >= value,
   - Zero (Z) is set if A == value,
   - Negative (N) is set based on the high bit of the subtraction result.
*/

static inline void
CMPSetStatus (Byte Result, CPU6502 *cpu)
{
  cpu->Flag.Z = (Result == 0);
  cpu->Flag.C = (cpu->A >= Result);
  cpu->Flag.N = (Result & 0x80) != 0;
}

/*
   CMP_IM - Compare Accumulator with Immediate value.
   Fetches a byte from memory, compares it with A, and updates status flags.
*/
static inline void
CMP_IM (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte Value = FetchByte (Cycles, memory, cpu);
  Byte Result = cpu->A - Value;
  CMPSetStatus (Result, cpu);
  spend_cycles (2);
}

/*
   CMP_ZP - Compare Accumulator with value from Zero Page address.
   Fetches a zero-page address from memory, reads the value at that address,
   compares it with A, and updates status flags.
*/
static inline void
CMP_ZP (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);
  cpu_read (bus, memory, ZeroPageAddr, Cycles);
  Byte Result = cpu->A - bus->data;
  CMPSetStatus (Result, cpu);
  spend_cycles (3);
}

/*
   CMP_ZPX - Compare Accumulator with value from Zero Page address with X
   offset. Adds X to the zero-page address before reading the value. Compares
   it with A and updates status flags.
*/
static inline void
CMP_ZPX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);
  ZeroPageAddr += cpu->X;
  (*Cycles)--;
  cpu_read (bus, memory, ZeroPageAddr, Cycles);
  Byte Result = cpu->A - bus->data;
  CMPSetStatus (Result, cpu);
  spend_cycles (4);
}

/*
   CMP_ABS - Compare Accumulator with value from Absolute address.
   Fetches a two-byte absolute address, reads the value,
   compares it with A, and updates status flags.
*/
static inline void
CMP_ABS (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);
  cpu_read (bus, memory, Absolute, Cycles);
  Byte Result = cpu->A - bus->data;
  CMPSetStatus (Result, cpu);
  spend_cycles (4);
}

/*
   CMP_ABSX - Compare Accumulator with value from Absolute address with X
   offset. Adds X to the absolute address before reading the value. If page
   boundary is crossed, consumes extra cycle. Compares with A and updates
   status flags.
*/
static inline void
CMP_ABSX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);
  Word NewAddress = Absolute + cpu->X;

  if ((NewAddress & 0xFF00) != (Absolute & 0xFF00))
    {
      (*Cycles)++;
      spend_cycle ();
    }

  cpu_read (bus, memory, NewAddress, Cycles);
  Byte Result = cpu->A - bus->data;
  CMPSetStatus (Result, cpu);
  spend_cycles (4);
}

/*
   CMP_ABSY - Compare Accumulator with value from Absolute address with Y
   offset. Adds Y to the absolute address before reading the value. If page
   boundary is crossed, consumes extra cycle. Compares with A and updates
   status flags.
*/
static inline void
CMP_ABSY (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);
  Word NewAddress = Absolute + cpu->Y;

  if ((NewAddress & 0xFF00) != (Absolute & 0xFF00))
    {
      (*Cycles)++;
      spend_cycle ();
    }

  cpu_read (bus, memory, NewAddress, Cycles);
  Byte Result = cpu->A - bus->data;
  CMPSetStatus (Result, cpu);
  spend_cycles (4);
}

#endif // CMP_H
