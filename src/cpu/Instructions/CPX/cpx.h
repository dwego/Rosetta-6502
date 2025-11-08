#ifndef CPX_H
#define CPX_H

#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the CPX (Compare X Register) instruction for MOS
   Technology 6502. CPX compares the X register with a value fetched from
   memory and updates the CPU status flags accordingly. For more information
   about the instructions, refer to Instructions.MD
*/

/*
   CPX compares the X register with a value by subtracting it from X (without
   storing the result). It updates the flags as follows:
   - Carry (C) is set if X >= value,
   - Zero (Z) is set if X == value,
   - Negative (N) is set based on the high bit of the subtraction result.
*/

static inline void
CPXSetStatus (Byte Result, CPU6502 *cpu)
{
  cpu->Flag.Z = (Result == 0);
  cpu->Flag.C = (cpu->X >= Result);
  cpu->Flag.N = (Result & 0x80) != 0;
}

/*
   CPX_IM - Compare X register with Immediate value.
   Fetches a byte from memory, compares it with X, and updates status flags.
*/
static inline void
CPX_IM (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte Value = FetchByte (Cycles, bus, memory, cpu);
  Byte Result = cpu->X - Value;
  CPXSetStatus (Result, cpu);
  spend_cycles (2);
}

/*
   CPX_ZP - Compare X register with value from Zero Page address.
   Fetches a zero-page address from memory, reads the value at that address,
   compares it with X, and updates status flags.
*/
static inline void
CPX_ZP (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, bus, memory, cpu);
  cpu_read (bus, memory, ZeroPageAddr, Cycles, cpu);
  Byte Result = cpu->X - bus->data;
  CPXSetStatus (Result, cpu);
  spend_cycles (3);
}

/*
   CPX_ABS - Compare X register with value from Absolute address.
   Fetches a two-byte absolute address, reads the value,
   compares it with X, and updates status flags.
*/
static inline void
CPX_ABS (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);
  cpu_read (bus, memory, Absolute, Cycles, cpu);
  Byte Result = cpu->X - bus->data;
  CPXSetStatus (Result, cpu);
  spend_cycles (4);
}

#endif // CPX_H
