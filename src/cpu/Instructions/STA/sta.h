#ifndef STA_H
#define STA_H

#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the STA (Store Accumulator) instruction for MOS
   Technology 6502. STA stores the value of the Accumulator register (A) into
   memory. For more information about the instructions, refer to
   Instructions.MD
*/

/*
   STA stores the value of the Accumulator (A) into the memory location
   specified by various addressing modes. STA does NOT modify any processor
   flags.
*/

/*
   STA_ZP - Store Accumulator into Zero Page address.
   This function fetches a zero-page address from memory, then writes the value
   of A into that address. It consumes 3 CPU cycles.
*/

static inline void
STA_ZP (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, bus, memory, cpu);
  cpu_write (bus, memory, ZeroPageAddr, cpu->A, Cycles, cpu);
  spend_cycles (3);
}

/*
   STA_ZPX - Store Accumulator into Zero Page address offset by X.
   This function fetches a zero-page address, adds the X register to it, and
   writes A to the resulting address. It consumes 4 CPU cycles.
*/

static inline void
STA_ZPX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, bus, memory, cpu);
  ZeroPageAddr += cpu->X;
  cpu_write (bus, memory, ZeroPageAddr, cpu->A, Cycles, cpu);
  spend_cycles (4);
}

/*
   STA_ABS - Store Accumulator into Absolute address.
   This function fetches a 16-bit absolute address from memory, then writes A
   to that address. It consumes 4 CPU cycles.
*/

static inline void
STA_ABS (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);
  cpu_write (bus, memory, Absolute, cpu->A, Cycles, cpu);
  spend_cycles (4);
}

/*
   STA_ABSX - Store Accumulator into Absolute address offset by X.
   This function fetches an absolute address, adds X to it, and writes A to the
   resulting address. It consumes 5 CPU cycles.
*/

static inline void
STA_ABSX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);
  Absolute += cpu->X;
  cpu_write (bus, memory, Absolute, cpu->A, Cycles, cpu);
  spend_cycles (5);
}

/*
   STA_ABSY - Store Accumulator into Absolute address offset by Y.
   This function fetches an absolute address, adds Y to it, and writes A to the
   resulting address. It consumes 5 CPU cycles.
*/

static inline void
STA_ABSY (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);
  Absolute += cpu->Y;
  cpu_write (bus, memory, Absolute, cpu->A, Cycles, cpu);
  spend_cycles (5);
}

/*
   STA_INDX - Store Accumulator using (Indirect, X) addressing mode.
   In this mode, the operand is a zero-page base address. The X register
   is added to this base address (wrapping in zero-page), forming a new
   zero-page pointer location. The two bytes at that location are used
   as the low/high bytes of the effective 16-bit address where the value
   of A will be stored.
*/

static inline void
STA_INDX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte zp = FetchByte (Cycles, bus, memory, cpu);
  zp += cpu->X;  // zero-page wraparound
  Byte lo = memory->Data[zp];
  Byte hi = memory->Data[(Byte)(zp + 1)];
  Word addr = (hi << 8) | lo;

  cpu_write (bus, memory, addr, cpu->A, Cycles, cpu);
  spend_cycles (6);
}

/*
   STA_INDY - Store Accumulator using (Indirect), Y addressing mode.
   In this mode, the operand is a zero-page address pointing to a 16-bit base
   address. The Y register is then added to that base to form the final target
   address.
*/

static inline void
STA_INDY (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte zp = FetchByte (Cycles, bus, memory, cpu);
  Byte lo = memory->Data[zp];
  Byte hi = memory->Data[(Byte)(zp + 1)];
  Word base = (hi << 8) | lo;
  Word addr = base + cpu->Y;

  cpu_write (bus, memory, addr, cpu->A, Cycles, cpu);
  spend_cycles (6);
}

#endif // STA_H
