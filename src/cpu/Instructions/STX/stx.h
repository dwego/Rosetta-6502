#ifndef STX_H
#define STX_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the STX (Store Index Register X) instruction for
   MOS Technology 6502. STX stores the value of the Index Register X (X) into
   memory. For more information about the instructions, refer to
   Instructions.MD
*/

/*
   STX stores the value of the X register into memory addresses specified by
   various addressing modes. STX does NOT affect any processor flags.
*/

/*
   STX_ZP - Store X Register into Zero Page address.
   This function fetches a zero-page address from memory and writes the value
   of X into that address. It consumes 3 CPU cycles.
*/

static inline void
STX_ZP (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);
  WriteByte (Cycles, cpu->X, memory, ZeroPageAddr);
  spend_cycles (3);
}

/*
   STX_ZPY - Store X Register into Zero Page address offset by Y.
   This function fetches a zero-page address, adds the Y register to it, and
   writes X to the resulting address. It consumes 4 CPU cycles.
*/

static inline void
STX_ZPY (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);
  ZeroPageAddr += cpu->Y;
  WriteByte (Cycles, cpu->X, memory, ZeroPageAddr);
  spend_cycles (4);
}

/*
   STX_ABS - Store X Register into Absolute address.
   This function fetches a 16-bit absolute address from memory, then writes X
   to that address. It consumes 4 CPU cycles.
*/

static inline void
STX_ABS (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);
  WriteByte (Cycles, cpu->X, memory, Absolute);
  spend_cycles (4);
}

#endif // STX_H
