#ifndef LDA_H
#define LDA_H

#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the LDA (Load Accumulator) instruction for MOS
   Technology 6502. LDA works by moving a value into the Accumulator register
   (A). For more information about the instructions, refer to Instructions.MD
*/

/*
   LDA (Load Accumulator) instruction supports various addressing modes in the
   6502 architecture. The different modes provide flexibility in specifying the
   source of the data to be loaded into the Accumulator (A).
*/

/*
   This function sets the Flags for the Status register
   to identify what happened during the LDA instruction.
*/

static inline void
LDASetStatus (CPU6502 *cpu)
{
  cpu->Flag.Z = (cpu->A == 0);
  cpu->Flag.N = (cpu->A & 0x80) > 0;
}

/*
   LDA_IM - Load Accumulator with Immediate value.
   This function fetches a byte from memory and loads it into the Accumulator
   (A). It then sets the status flags using LDASetStatus.
*/

static inline void
LDA_IM (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte Value = FetchByte (bus, memory, cpu);
  ;
  cpu->A = Value;
  LDASetStatus (cpu);
  spend_cycles (2);
}

/*
   LDA_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory,
   reads the value at that address, and loads it into the Accumulator (A). It
   then sets the status flags.
*/

static inline void
LDA_ZP (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (bus, memory, cpu);
  cpu_read (bus, memory, ZeroPageAddr, cpu);
  cpu->A = bus->data;
  LDASetStatus (cpu);
  spend_cycles (3);
}

/*
   LDA_ZPX - Load Accumulator from Zero Page with X Offset.
   Similar to LDA_ZP, but adds the X register value to the zero-page address
   before reading the value from memory. It adjusts the cycle count accordingly
   and sets the status flags.
*/

static inline void
LDA_ZPX (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (bus, memory, cpu);
  ZeroPageAddr += cpu->X;
  
  cpu_read (bus, memory, ZeroPageAddr, cpu);
  cpu->A = bus->data;
  LDASetStatus (cpu);
  spend_cycles (4);
}

/*
   LDA_ABS - Load Accumulator from Absolute address.
   This function fetches a two-byte absolute address from memory, reads the
   value at that address, and loads it into the Accumulator (A). It then sets
   the status flags.
*/

static inline void
LDA_ABS (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (bus, memory, cpu);
  cpu_read (bus, memory, Absolute, cpu);
  cpu->A = bus->data;
  LDASetStatus (cpu);
  spend_cycles (4);
}

/*
   LDA_ABSX - Load Accumulator from Absolute address with X Offset.
   Similar to LDA_ABS, but adds the X register value to the absolute address
   before reading the value from memory. It adjusts the cycle count accordingly
   and sets the status flags.
*/

static inline void
LDA_ABSX (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (bus, memory, cpu);
  Word OldPage = Absolute & 0xFF00;
  Absolute += cpu->X;
  Word NewPage = Absolute & 0xFF00;
  if (OldPage != NewPage)
    {
      
      spend_cycle ();
    }

  cpu_read (bus, memory, Absolute, cpu);
  cpu->A = bus->data;
  LDASetStatus (cpu);
  spend_cycles (4);
}

/*
   LDA_ABSY - Load Accumulator from Absolute address with Y Offset.
   Similar to LDA_ABS, but adds the Y register value to the absolute address
   before reading the value from memory. It adjusts the cycle count accordingly
   and sets the status flags.
*/

static inline void
LDA_ABSY (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (bus, memory, cpu);

  Word OldPage = Absolute & 0xFF00;
  Absolute += cpu->Y;
  Word NewPage = Absolute & 0xFF00;

  // Add an extra cycle if page is crossed
  if (OldPage != NewPage)
    {
      
      spend_cycle ();
    }

  cpu_read (bus, memory, Absolute, cpu);
  cpu->A = bus->data;
  LDASetStatus (cpu);
  spend_cycles (4);
}


/*
   LDA_INDX - Load Accumulator from (Indirect, X) addressing mode.
   In this mode, the operand is a zero-page address. The X register is added
   to this base zero-page address to get a new zero-page location. The low and
   high bytes of the final target address are read from this zero-page pair,
   forming a 16-bit effective address.
*/

static inline void
LDA_INDX (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte zp = FetchByte (bus, memory, cpu);
  zp += cpu->X;  // add X offset (wraps within zero page)
  Byte lo = memory->Data[zp];
  Byte hi = memory->Data[(Byte)(zp + 1)];
  Word addr = (hi << 8) | lo;

  cpu_read (bus, memory, addr, cpu);
  cpu->A = bus->data;
  LDASetStatus (cpu);
  spend_cycles (6);
}

/*
   LDA_INDY - Load Accumulator from (Indirect), Y addressing mode.
   In this mode, the operand is a zero-page address that points to a 16-bit
   base address. The Y register is then added to this base address to form
   the final effective address. If this addition crosses a page boundary,
   one extra cycle is added. 
*/

static inline void
LDA_INDY (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte zp = FetchByte (bus, memory, cpu);
  Byte lo = memory->Data[zp];
  Byte hi = memory->Data[(Byte)(zp + 1)];
  Word base = (hi << 8) | lo;
  Word addr = base + cpu->Y;

  if ((base & 0xFF00) != (addr & 0xFF00))  // page boundary crossed
    {
      
      spend_cycle ();
    }

  cpu_read (bus, memory, addr, cpu);
  cpu->A = bus->data;
  LDASetStatus (cpu);
  spend_cycles (5);
}

#endif // LDA_H
