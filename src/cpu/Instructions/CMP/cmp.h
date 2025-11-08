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
CMP_IM (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte Value = FetchByte (Cycles, bus, memory, cpu);
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
  Byte ZeroPageAddr = FetchByte (Cycles, bus, memory, cpu);
  cpu_read (bus, memory, ZeroPageAddr, Cycles, cpu);
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
  Byte ZeroPageAddr = FetchByte (Cycles, bus, memory, cpu);
  ZeroPageAddr += cpu->X;
  (*Cycles)--;
  cpu_read (bus, memory, ZeroPageAddr, Cycles, cpu);
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
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);
  cpu_read (bus, memory, Absolute, Cycles, cpu);
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
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);
  Word NewAddress = Absolute + cpu->X;

  if ((NewAddress & 0xFF00) != (Absolute & 0xFF00))
    {
      (*Cycles)++;
      spend_cycle ();
    }

  cpu_read (bus, memory, NewAddress, Cycles, cpu);
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
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);
  Word NewAddress = Absolute + cpu->Y;

  if ((NewAddress & 0xFF00) != (Absolute & 0xFF00))
    {
      (*Cycles)++;
      spend_cycle ();
    }

  cpu_read (bus, memory, NewAddress, Cycles, cpu);
  Byte Result = cpu->A - bus->data;
  CMPSetStatus (Result, cpu);
  spend_cycles (4);
}

/*
   CMP_INDX - Compare Accumulator with value using (Indirect, X) addressing mode.
   The operand is a zero-page address. The X register is added to this address
   (wrapping within zero-page) to form a new pointer location. The two bytes
   read from this pointer form the 16-bit effective address. The byte at that
   address is compared with A. Updates Carry, Zero, and Negative flags.
*/

static inline void
CMP_INDX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte zp = FetchByte (Cycles, bus, memory, cpu);
  zp += cpu->X; // zero-page wraparound
  Byte lo = memory->Data[zp];
  Byte hi = memory->Data[(Byte)(zp + 1)];
  Word addr = (hi << 8) | lo;

  cpu_read (bus, memory, addr, Cycles, cpu);
  Byte Result = cpu->A - bus->data;
  CMPSetStatus (Result, cpu);
  spend_cycles (6);
}

/*
   CMP_INDY - Compare Accumulator with value using (Indirect), Y addressing mode.
   The operand is a zero-page address pointing to a 16-bit base address.
   The Y register is added to that base to form the effective address.
   If the addition crosses a page boundary, one extra cycle is consumed.
   The value read from that address is compared with A.
   Updates Carry, Zero, and Negative flags.
*/

static inline void
CMP_INDY (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
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
  Byte Result = cpu->A - bus->data;
  CMPSetStatus (Result, cpu);
  spend_cycles (5);
}

#endif // CMP_H
