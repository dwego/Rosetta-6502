#ifndef ORA_H
#define ORA_H

#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the ORA (Logical Inclusive OR with Accumulator)
   instruction for the MOS Technology 6502 processor.

   ORA performs a bitwise OR between the Accumulator (A) and a fetched value,
   storing the result back into the Accumulator. It affects the Zero and
   Negative flags.

   For more information about the instructions, refer to Instructions.MD
*/

/*
   The ORA instruction supports various addressing modes in the 6502
   architecture. These modes determine how the operand is fetched from memory
   before being OR-ed with A.
*/

/*
   This function sets the Zero and Negative flags
   based on the result in the Accumulator after the ORA operation.
*/
static inline void
ORASetStatus (CPU6502 *cpu)
{
  cpu->Flag.Z = (cpu->A == 0);
  cpu->Flag.N = (cpu->A & 0x80) > 0;
}

/*
   ORA_IM - OR Accumulator with Immediate value.
   Fetches an immediate byte, ORs it with A, updates A and sets status flags.
*/
static inline void
ORA_IM (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte Value = FetchByte (Cycles, memory, cpu);
  cpu->A |= Value;
  ORASetStatus (cpu);
  spend_cycles (2);
}

/*
   ORA_ZP - OR Accumulator with Zero Page address value.
   Fetches a zero-page address, reads its value, ORs with A, updates A and
   flags.
*/
static inline void
ORA_ZP (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);
  cpu_read (bus, memory, ZeroPageAddr, Cycles);
  cpu->A |= bus->data;
  ORASetStatus (cpu);
  spend_cycles (3);
}

/*
   ORA_ZPX - OR Accumulator with Zero Page,X address value.
   Adds X to a zero-page address, reads the value, ORs with A, updates A and
   flags.
*/
static inline void
ORA_ZPX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);
  ZeroPageAddr += cpu->X;
  (*Cycles)--; // penalty cycle for zero-page wraparound handling
  cpu_read (bus, memory, ZeroPageAddr, Cycles);
  cpu->A |= bus->data;
  ORASetStatus (cpu);
  spend_cycles (4);
}

/*
   ORA_ABS - OR Accumulator with Absolute address value.
   Fetches a full 16-bit address, reads the value, ORs with A, updates A and
   flags.
*/
static inline void
ORA_ABS (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);
  cpu_read (bus, memory, Absolute, Cycles);
  cpu->A |= bus->data;
  ORASetStatus (cpu);
  spend_cycles (4);
}

/*
   ORA_ABSX - OR Accumulator with Absolute,X address value.
   Adds X to a full 16-bit address. If page crosses, adds a cycle.
   Reads value at new address, ORs with A, updates A and flags.
*/
static inline void
ORA_ABSX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);
  Word AddressWithX = Absolute + cpu->X;

  if ((Absolute & 0xFF00) != (AddressWithX & 0xFF00))
    {
      (*Cycles)++;
      spend_cycle (); // page boundary crossed
    }

  cpu_read (bus, memory, AddressWithX, Cycles);
  cpu->A |= bus->data;
  ORASetStatus (cpu);
  spend_cycles (4);
}

/*
   ORA_ABSY - OR Accumulator with Absolute,Y address value.
   Adds Y to a full 16-bit address. If page crosses, adds a cycle.
   Reads value at new address, ORs with A, updates A and flags.
*/
static inline void
ORA_ABSY (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);
  Word AddressWithY = Absolute + cpu->Y;

  if ((Absolute & 0xFF00) != (AddressWithY & 0xFF00))
    {
      (*Cycles)++;
      spend_cycle (); // page boundary crossed
    }

  cpu_read (bus, memory, AddressWithY, Cycles);
  cpu->A |= bus->data;
  ORASetStatus (cpu);
  spend_cycles (4);
}

#endif // ORA_H
