#ifndef CPY_H
#define CPY_H

#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the CPY (Compare Y Register) instruction for MOS
   Technology 6502. CPY compares the Y register with a value fetched from
   memory and updates the CPU status flags accordingly. For more information
   about the instructions, refer to Instructions.MD
*/

/*
   CPY compares the Y register with a value by subtracting it from Y (without
   storing the result). It updates the flags as follows:
   - Carry (C) is set if Y >= value,
   - Zero (Z) is set if Y == value,
   - Negative (N) is set based on the high bit of the subtraction result.
*/

static inline void
CPYSetStatus (Byte Result, CPU6502 *cpu)
{
  cpu->Flag.Z = (Result == 0);
  cpu->Flag.C = (cpu->Y >= Result);
  cpu->Flag.N = (Result & 0x80) != 0;
}

/*
   CPY_IM - Compare Y register with Immediate value.
   Fetches a byte from memory, compares it with Y, and updates status flags.
*/
static inline void
CPY_IM (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte Value = FetchByte (Cycles, bus, memory, cpu);
  Byte Result = cpu->Y - Value;
  CPYSetStatus (Result, cpu);
  spend_cycles (2);
}

/*
   CPY_ZP - Compare Y register with value from Zero Page address.
   Fetches a zero-page address from memory, reads the value at that address,
   compares it with Y, and updates status flags.
*/
static inline void
CPY_ZP (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, bus, memory, cpu);
  cpu_read (bus, memory, ZeroPageAddr, Cycles, cpu);
  Byte Result = cpu->Y - bus->data;
  CPYSetStatus (Result, cpu);
  spend_cycles (3);
}

/*
   CPY_ABS - Compare Y register with value from Absolute address.
   Fetches a two-byte absolute address, reads the value,
   compares it with Y, and updates status flags.
*/
static inline void
CPY_ABS (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);
  cpu_read (bus, memory, Absolute, Cycles, cpu);
  Byte Result = cpu->Y - bus->data;
  CPYSetStatus (Result, cpu);
  spend_cycles (4);
}

#endif // CPY_H
