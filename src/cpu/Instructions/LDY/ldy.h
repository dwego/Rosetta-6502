#ifndef LDY_H
#define LDY_H

#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the LDY (Load Index Register Y) instruction for
   MOS Technology 6502. LDY works by moving a value into the Index Register Y
   (Y). For more information about the instructions, refer to Instructions.MD
*/

/*
   This function sets the Flags for the Status register
   to identify what happened during the LDY instruction.
*/

static inline void
LDYSetStatus (CPU6502 *cpu)
{
  cpu->Flag.Z = (cpu->Y == 0);
  cpu->Flag.N = (cpu->Y & 0x80) > 0;
}

/*
   LDY (Load Index Register Y) instruction supports various addressing modes in
   the 6502 architecture. The different modes provide fleYibility in specifying
   the source of the data to be loaded into the Index Register Y, (Y).
*/

/*
   LDY_IM - Load Index Register Y with Immediate value.
   This function fetches a byte from memory and loads it into the Index
   Register Y (Y). It then sets the status flags using LDYSetStatus.
*/

static inline void
LDY_IM (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte Value = FetchByte (Cycles, memory, cpu);
  cpu->Y = Value;
  LDYSetStatus (cpu);
  spend_cycles (2);
}

/*
   LDY_ZP - Load Index Register Y from Zero Page.
   This function fetches a byte representing a zero-page address from memory,
   reads the value at that address, and loads it into the Index Register Y (Y).
   It then sets the status flags.
*/

static inline void
LDY_ZP (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);
  cpu_read (bus, memory, ZeroPageAddr, Cycles);
  cpu->Y = bus->data;
  LDYSetStatus (cpu);
  spend_cycles (3);
}

/*
   LDY_ZPX - Load Index Register Y from Zero Page with X Offset.
   Similar to LDY_ZP, but adds the X register value to the zero-page address
   before reading the value from memory. It adjusts the cycle count accordingly
   and sets the status flags.
*/

static inline void
LDY_ZPX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);
  ZeroPageAddr += cpu->X;
  (*Cycles)--;
  cpu_read (bus, memory, ZeroPageAddr, Cycles);
  cpu->Y = bus->data;
  LDYSetStatus (cpu);
  spend_cycles (4);
}

/*
   LDY_ABS - Load Index Register Y from Absolute address.
   This function fetches a two-byte absolute address from memory, reads the
   value at that address, and loads it into the Index Register Y (Y). It then
   sets the status flags.
*/

static inline void
LDY_ABS (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);
  cpu_read (bus, memory, Absolute, Cycles);
  cpu->Y = bus->data;
  LDYSetStatus (cpu);
  spend_cycles (4);
}

/*
   LDY_ABSX - Load Index Register Y from Absolute address with X Offset.
   Similar to LDY_ABS, but adds the X register value to the absolute address
   before reading the value from memory. It adjusts the cycle count accordingly
   and sets the status flags.
*/

static inline void
LDY_ABSX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);

  Word OldPage = Absolute & 0xFF00;
  Absolute += cpu->X;
  Word NewPage = Absolute & 0xFF00;

  // Add an extra cycle if page is crossed
  if (OldPage != NewPage)
    {
      (*Cycles)++;
      spend_cycle ();
    }

  cpu_read (bus, memory, Absolute, Cycles);
  cpu->Y = bus->data;
  LDYSetStatus (cpu);
  spend_cycles (4);
}

#endif // LDY_H
