#ifndef EOR_H
#define EOR_H

#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the EOR (Exclusive OR Accumulator) instruction for
   MOS Technology 6502. EOR performs a bitwise exclusive OR operation between
   the Accumulator register (A) and a value fetched from memory, then stores
   the result back into the Accumulator. For more information about the
   instructions, refer to Instructions.MD
*/

/*
   EOR instruction supports various addressing modes in the 6502 architecture.
   These modes provide flexibility in specifying the source of the data
   to be exclusive ORed with the Accumulator (A).
*/

/*
   This function sets the Flags for the Status register
   to identify what happened during the EOR instruction.
   It updates the Zero and Negative flags based on the new value of the
   Accumulator.
*/
static inline void
EORSetStatus (CPU6502 *cpu)
{
  cpu->Flag.Z = (cpu->A == 0);
  cpu->Flag.N = (cpu->A & 0x80) > 0;
}

/*
   EOR_IM - Exclusive OR with Immediate value.
   This function fetches a byte from memory, performs EOR with the Accumulator
   (A), then sets the status flags accordingly.
*/
static inline void
EOR_IM (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte Value = FetchByte (Cycles, bus, memory, cpu);
  cpu->A ^= Value;
  EORSetStatus (cpu);
  spend_cycles (2);
}

/*
   EOR_ZP - Exclusive OR with Zero Page address.
   This function fetches a zero-page address from memory, reads the byte at
   that address, performs EOR with the Accumulator (A), then sets the status
   flags accordingly.
*/
static inline void
EOR_ZP (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, bus, memory, cpu);
  cpu_read (bus, memory, ZeroPageAddr, Cycles, cpu);
  cpu->A = bus->data;
  EORSetStatus (cpu);
  spend_cycles (3);
}

/*
   EOR_ZPX - Exclusive OR with Zero Page address offset by X register.
   Similar to EOR_ZP, but adds the X register to the zero-page address before
   reading. It adjusts the cycle count accordingly and sets the status flags.
*/
static inline void
EOR_ZPX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, bus, memory, cpu);
  ZeroPageAddr += cpu->X;
  (*Cycles)--;
  cpu_read (bus, memory, ZeroPageAddr, Cycles, cpu);
  cpu->A = bus->data;
  EORSetStatus (cpu);
  spend_cycles (4);
}

/*
   EOR_ABS - Exclusive OR with Absolute address.
   This function fetches a two-byte absolute address from memory, reads the
   byte at that address, performs EOR with the Accumulator (A), then sets the
   status flags.
*/
static inline void
EOR_ABS (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);
  cpu_read (bus, memory, Absolute, Cycles, cpu);
  cpu->A = bus->data;
  EORSetStatus (cpu);
  spend_cycles (4);
}

/*
   EOR_ABSX - Exclusive OR with Absolute address offset by X register.
   Similar to EOR_ABS, but adds the X register value to the absolute address
   before reading. If the addition crosses a page boundary, it adjusts the
   cycle count. It then sets the status flags.
*/
static inline void
EOR_ABSX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);

  Word OldPage = Absolute & 0xFF00;
  Absolute += cpu->X;
  Word NewPage = Absolute & 0xFF00;

  if (OldPage != NewPage)
    {
      (*Cycles)++;
      spend_cycle ();
    }

  cpu_read (bus, memory, Absolute, Cycles, cpu);
  cpu->A = bus->data;
  EORSetStatus (cpu);
  spend_cycles (4);
}

/*
   EOR_ABSY - Exclusive OR with Absolute address offset by Y register.
   Similar to EOR_ABS, but adds the Y register value to the absolute address
   before reading. If the addition crosses a page boundary, it adjusts the
   cycle count. It then sets the status flags.
*/

static inline void
EOR_ABSY (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);

  Word OldPage = Absolute & 0xFF00;
  Absolute += cpu->Y;
  Word NewPage = Absolute & 0xFF00;

  if (OldPage != NewPage)
    {
      (*Cycles)++;
      spend_cycle ();
    }

  cpu_read (bus, memory, Absolute, Cycles, cpu);
  cpu->A = bus->data;
  EORSetStatus (cpu);
  spend_cycles (4);
}

/*
   EOR_INDX - Exclusive OR using (Indirect, X) addressing mode.
   In this mode, the operand is a zero-page base address. The X register is
   added to this base address (wrapping within zero-page) to locate a 16-bit
   pointer. The value read from that pointer's target address is XORed with
   the Accumulator (A). 
*/

static inline void
EOR_INDX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte zp = FetchByte (Cycles, bus, memory, cpu);
  zp += cpu->X; // apply X offset (wrap-around zero page)
  Byte lo = memory->Data[zp];
  Byte hi = memory->Data[(Byte)(zp + 1)];
  Word addr = (hi << 8) | lo;

  cpu_read (bus, memory, addr, Cycles, cpu);
  cpu->A ^= bus->data;
  EORSetStatus (cpu);
  spend_cycles (6);
}

/*
   EOR_INDY - Exclusive OR using (Indirect), Y addressing mode.
   In this mode, the operand is a zero-page address pointing to a 16-bit base
   address. The Y register is added to this base address to get the effective
   address. The value read from that effective address is XORed with the
   Accumulator (A).
*/

static inline void
EOR_INDY (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte zp = FetchByte (Cycles, bus, memory, cpu);
  Byte lo = memory->Data[zp];
  Byte hi = memory->Data[(Byte)(zp + 1)];
  Word base = (hi << 8) | lo;
  Word addr = base + cpu->Y;

  if ((base & 0xFF00) != (addr & 0xFF00)) // page boundary crossed
    {
      (*Cycles)++;
      spend_cycle ();
    }

  cpu_read (bus, memory, addr, Cycles, cpu);
  cpu->A ^= bus->data;
  EORSetStatus (cpu);
  spend_cycles (5);
}

#endif // EOR_H

