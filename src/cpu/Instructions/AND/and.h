#ifndef AND_H
#define AND_H

#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the AND (And with Accumulator) instruction for MOS
   Technology 6502. AND performs a bitwise AND operation on the Accumulator
   register (A) and a provided value, storing the result back in the
   Accumulator. For more information about the instructions, refer to
   Instructions.MD
*/

/*
   AND instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data
   to be AND'ed with the Accumulator (A).
*/

/*
   This function sets the Flags for the Status register
   to represent the result of the AND operation.
*/
static inline void
ANDSetStatus (CPU6502 *cpu)
{
  cpu->Flag.Z = (cpu->A == 0);
  cpu->Flag.N = (cpu->A & 0x80) > 0;
}

/*
   AND_IM - And with Accumulator using an Immediate value.
   This function fetches a byte from memory and performs an AND operation
   between it and the contents of the Accumulator, storing the result in the
   Accumulator. It then sets the status flags using ANDSetStatus.
*/

static inline void
AND_IM (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  cpu->A &= FetchByte (Cycles, memory, cpu);
  ANDSetStatus (cpu);
  spend_cycles (2);
}

/*
   AND_ZP - And with Accumulator from a Zero-Page address.
   This function fetches a byte representing a zero-page address from memory,
   reads the value at that address, ANDs it with the Accumulator, and stores
   value in the Accumulator. It then sets the status flags using ANDSetStatus.
*/
static inline void
AND_ZP (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);
  cpu_read (bus, memory, ZeroPageAddr, Cycles);
  cpu->A &= bus->data;
  ANDSetStatus (cpu);
  spend_cycles (3);
}

/*
   AND_ZPX - And with Accumulator from a Zero Page address with X register
   offset. This function fetches a byte representing a zero-page address from
   memory, adds the X register to this address, reads the value from this
   address, ANDs it with the Accumulator, and stores the result in the
   Accumulator. It then sets the status flags using ANDSetStatus.
*/
static inline void
AND_ZPX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);
  ZeroPageAddr += cpu->X;
  cpu_read (bus, memory, ZeroPageAddr, Cycles);
  cpu->A &= bus->data;
  (*Cycles)--;
  ANDSetStatus (cpu);
  spend_cycles (4);
}

/*
   AND_ABS - And with Accumulator from an Absolute address.
   This function fetches a two-byte absolute address from memory, reads the
   value at that address, ANDs it with the Accumulator, and stores the result
   in the Accumulator. It then sets the status flags using ANDSetStatus.
*/
static inline void
AND_ABS (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);
  cpu_read (bus, memory, Absolute, Cycles);
  cpu->A &= bus->data;

  ANDSetStatus (cpu);
  spend_cycles (4);
}

/*
   AND_ABSX - And with Accumulator from an Absolute address with X register
   offset. This function fetches a two-byte absolute address from memory, adds
   the X register to this address, reads the value from this address, ANDs it
   with the Accumulator, and stores the result in the Accumulator. It then sets
   the status flags using ANDSetStatus.
*/

static inline void
AND_ABSX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);

  Word OldPage = Absolute & 0xFF00;
  Absolute += cpu->X;
  Word NewPage = Absolute & 0xFF00;

  if (OldPage != NewPage)
    {
      (*Cycles)++;
      spend_cycle ();
    }

  cpu_read (bus, memory, Absolute, Cycles);
  cpu->A &= bus->data;
  ANDSetStatus (cpu);
  spend_cycles (4);
}

/*
   AND_ABSY - And with Accumulator from an Absolute address with Y register
   offset. This function fetches a two-byte absolute address from memory, adds
   the Y register to this address, reads the value from this address, ANDs it
   with the Accumulator, and stores the result in the Accumulator. It then sets
   the status flags using ANDSetStatus.
*/
static inline void
AND_ABSY (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);

  Word OldPage = Absolute & 0xFF00;
  Absolute += cpu->Y;
  Word NewPage = Absolute & 0xFF00;

  if (OldPage != NewPage)
    {
      (*Cycles)++;
      spend_cycle ();
    }

  cpu_read (bus, memory, Absolute, Cycles);
  cpu->A &= bus->data;
  ANDSetStatus (cpu);
  spend_cycles (4);
}

#endif // AND_H
