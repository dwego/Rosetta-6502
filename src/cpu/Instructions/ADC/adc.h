#ifndef ADC_H
#define ADC_H

#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the ADC (Add with Carry) instruction for MOS
   Technology 6502. ADC adds a value and the carry flag to the Accumulator
   register (A). For more information about the instructions, refer to
   Instructions.MD
*/

/*
   This function sets the Flags for the Status register
   to represent the result of the ADC instruction.
*/

static inline void
ADCSetStatus (CPU6502 *cpu, Byte before, Byte value)
{
  cpu->Flag.Z = (cpu->A == 0);
  cpu->Flag.N = (cpu->A & 0x80) > 0;
  cpu->Flag.V = (~(before ^ value) & (before ^ cpu->A) & 0x80) != 0;
  cpu->Flag.C = (cpu->A < before);
}

/*
   ADC_IM - Add Immediate value and the carry flag (if set) to the Accumulator.
   This function fetches a byte from memory and adds it and the carry flag (if
   set) to the Accumulator (A). It then sets the status flags.
*/

static inline void
ADC_IM (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte Value = FetchByte (Cycles, bus, memory, cpu);

  Byte Before = cpu->A;
  cpu->A += Value + cpu->Flag.C;
  ADCSetStatus (cpu, Before, Value);
  spend_cycles (2);
}

/*
   ADC_ZP - Add value from Zero Page and the carry flag (if set) to the
   Accumulator. This function fetches a byte representing a zero-page address
   from memory, reads the value at that address, and adds it and the carry flag
   (if set) to the Accumulator (A). It then sets the status flags.
*/

static inline void
ADC_ZP (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, bus, memory, cpu);
  cpu_read (bus, memory, ZeroPageAddr, Cycles, cpu);

  Byte Before = cpu->A;
  cpu->A += bus->data + cpu->Flag.C;
  ADCSetStatus (cpu, Before, bus->data);
  spend_cycles (3);
}

/*
   ADC_ZPX - Add value from Zero Page with X Offset and the carry flag (if set)
   to the Accumulator. This function fetches a byte representing a zero-page
   address from memory, adds the X register to this address, reads the value at
   the resultant address, and adds it and the carry flag (if set) to the
   Accumulator (A). It then sets the status flags.
*/

static inline void
ADC_ZPX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, bus, memory, cpu);
  ZeroPageAddr += cpu->X;

  cpu_read (bus, memory, ZeroPageAddr, Cycles, cpu);

  Byte Before = cpu->A;
  cpu->A += bus->data + cpu->Flag.C;
  ADCSetStatus (cpu, Before, bus->data);
  spend_cycles (4);
}

/*
   ADC_ABS - Add value from Absolute address and the carry flag (if set) to the
   Accumulator. This function fetches an absolute address from memory, reads
   the value at that address, and adds it and the carry flag (if set) to the
   Accumulator (A). It then sets the status flags.
*/

static inline void
ADC_ABS (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);

  cpu_read (bus, memory, Absolute, Cycles, cpu);
  Byte Before = cpu->A;
  cpu->A += bus->data + cpu->Flag.C;
  ADCSetStatus (cpu, Before, bus->data);
  spend_cycles (4);
}

/*
   ADC_ABSX - Add value from Absolute address with X Offset and the carry flag
   (if set) to the Accumulator. This function fetches an absolute address from
   memory, adds the X register to this address, reads the value at the
   resultant address, and adds it and the carry flag (if set) to the
   Accumulator (A). It then sets the status flags.
*/

static inline void
ADC_ABSX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);
  Word NewAddress = Absolute + cpu->X;

  if ((NewAddress & 0xFF00) != (Absolute & 0xFF00))
    {
      (*Cycles)++;
      spend_cycle ();
    }

  cpu_read (bus, memory, NewAddress, Cycles, cpu);
  Byte Before = cpu->A;
  cpu->A += bus->data + cpu->Flag.C;
  ADCSetStatus (cpu, Before, bus->data);
  spend_cycles (4);
}

/*
   ADC_ABSY - Add value from Absolute address with Y Offset and the carry flag
   (if set) to the Accumulator. This function fetches an absolute address from
   memory, adds the Y register to this address, reads the value at the
   resultant address, and adds it and the carry flag (if set) to the
   Accumulator (A). It then sets the status flags.
*/

static inline void
ADC_ABSY (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);
  Word NewAddress = Absolute + cpu->Y;

  if ((NewAddress & 0xFF00) != (Absolute & 0xFF00))
    {
      (*Cycles)++;
      spend_cycle ();
    }

  cpu_read (bus, memory, NewAddress, Cycles, cpu);
  Byte Before = cpu->A;
  cpu->A += bus->data + cpu->Flag.C;
  ADCSetStatus (cpu, Before, bus->data);
  spend_cycles (4);
}

/*
   ADC_INDX - Add with Carry using (Indirect, X) addressing mode.
   In this mode, the operand is a zero-page base address. The X register is
   added to this address (with wrap-around) to get a new zero-page pointer.
   The two bytes read from that pointer form the effective 16-bit address.
   The value at that address is added to A along with the Carry flag.
*/

static inline void
ADC_INDX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte zp = FetchByte (Cycles, bus, memory, cpu);
  zp += cpu->X; // zero-page wrap
  Byte lo = memory->Data[zp];
  Byte hi = memory->Data[(Byte)(zp + 1)];
  Word addr = (hi << 8) | lo;

  cpu_read (bus, memory, addr, Cycles, cpu);
  Byte Value = bus->data;
  Byte Before = cpu->A;

  cpu->A += Value + cpu->Flag.C;
  ADCSetStatus (cpu, Before, Value);
  spend_cycles (6);
}

/*
   ADC_INDY - Add with Carry using (Indirect), Y addressing mode.
   The operand is a zero-page pointer to a 16-bit base address.
   The Y register is added to this base to form the effective address.
   The byte read from that address is added to A along with the Carry flag.
   If a page boundary is crossed, one extra cycle is consumed.
*/

static inline void
ADC_INDY (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
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
  Byte Value = bus->data;
  Byte Before = cpu->A;

  cpu->A += Value + cpu->Flag.C;
  ADCSetStatus (cpu, Before, Value);
  spend_cycles (5);
}

#endif // ADC_H
