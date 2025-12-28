#ifndef STY_H
#define STY_H

#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the STY (Store Index Register Y) instruction for
   MOS Technology 6502. STY stores the value of the Index Register Y (Y) into a
   specific memory address. For more information about the instructions, refer
   to Instructions.MD
*/

/*
   STY stores the value of the Y register into memory addresses specified by
   various addressing modes. STY does NOT affect any processor flags.
*/

/*
   STY_ZP - Store Y Register into Zero Page address.
   This function fetches a zero-page address from memory and writes the value
   of Y into that address. It consumes 3 CPU cycles.
*/
static inline void
STY_ZP (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (bus, memory, cpu);
  cpu_write (bus, memory, ZeroPageAddr, cpu->Y);
  spend_cycles (3);
}

/*
   STY_ZPX - Store Y Register into Zero Page address offset by X.
   This function fetches a zero-page address, adds the X register to it, and
   writes Y to the resulting address. It consumes 4 CPU cycles.
*/
static inline void
STY_ZPX (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (bus, memory, cpu);
  ZeroPageAddr += cpu->X;
  cpu_write (bus, memory, ZeroPageAddr, cpu->Y);
  spend_cycles (4);
}

/*
   STY_ABS - Store Y Register into Absolute address.
   This function fetches a 16-bit absolute address from memory, then writes Y
   to that address. It consumes 4 CPU cycles.
*/
static inline void
STY_ABS (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (bus, memory, cpu);
  cpu_write (bus, memory, Absolute, cpu->Y);
  spend_cycles (4);
}

#endif // STY_H
