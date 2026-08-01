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

// Helper

static inline void
ADC(CPU6502 *cpu, Byte value)
{
    Byte accumulator = cpu->A;
    Byte carry_in = cpu->Flag.C;

    Word sum = (Word)accumulator + (Word)value + (Word)carry_in;
    Byte result = (Byte)(sum & 0xFF);

    cpu->Flag.C = sum > 0xFF;

    cpu->Flag.V =
        ((~(accumulator ^ value) & (accumulator ^ result)) & 0x80) != 0;

    cpu->Flag.Z = result == 0;
    cpu->Flag.N = (result & 0x80) != 0;

    cpu->A = result;
}

/*
   ADC_IM - Add Immediate value and the carry flag (if set) to the Accumulator.
   This function fetches a byte from memory and adds it and the carry flag (if
   set) to the Accumulator (A). It then sets the status flags.
*/

static inline void
ADC_IM(Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
    Byte value = FetchByte(bus, memory, cpu);

    ADC(cpu, value);

    spend_cycles(2);
}
/*
   ADC_ZP - Add value from Zero Page and the carry flag (if set) to the
   Accumulator. This function fetches a byte representing a zero-page address
   from memory, reads the value at that address, and adds it and the carry flag
   (if set) to the Accumulator (A). It then sets the status flags.
*/

static inline void
ADC_ZP(Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
    Byte address = FetchByte(bus, memory, cpu);

    cpu_read(bus, memory, address);
    ADC(cpu, bus->data);

    spend_cycles(3);
}
/*
   ADC_ZPX - Add value from Zero Page with X Offset and the carry flag (if set)
   to the Accumulator. This function fetches a byte representing a zero-page
   address from memory, adds the X register to this address, reads the value at
   the resultant address, and adds it and the carry flag (if set) to the
   Accumulator (A). It then sets the status flags.
*/

static inline void
ADC_ZPX (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (bus, memory, cpu);
  ZeroPageAddr += cpu->X;

  cpu_read (bus, memory, ZeroPageAddr);

  ADC(cpu, bus->data);
  spend_cycles (4);
}

/*
   ADC_ABS - Add value from Absolute address and the carry flag (if set) to the
   Accumulator. This function fetches an absolute address from memory, reads
   the value at that address, and adds it and the carry flag (if set) to the
   Accumulator (A). It then sets the status flags.
*/

static inline void
ADC_ABS (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (bus, memory, cpu);

  cpu_read (bus, memory, Absolute);
  ADC(cpu, bus->data);
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
ADC_ABSX (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (bus, memory, cpu);
  Word NewAddress = Absolute + cpu->X;

  cpu_read (bus, memory, NewAddress);
  ADC(cpu, bus->data);
  spend_cycles (4);

  if ((NewAddress & 0xFF00) != (Absolute & 0xFF00))
        spend_cycle();
}

/*
   ADC_ABSY - Add value from Absolute address with Y Offset and the carry flag
   (if set) to the Accumulator. This function fetches an absolute address from
   memory, adds the Y register to this address, reads the value at the
   resultant address, and adds it and the carry flag (if set) to the
   Accumulator (A). It then sets the status flags.
*/

static inline void
ADC_ABSY (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (bus, memory, cpu);
  Word NewAddress = Absolute + cpu->Y;

  cpu_read (bus, memory, NewAddress);
  ADC(cpu, bus->data);
  spend_cycles (4);

  if ((NewAddress & 0xFF00) != (Absolute & 0xFF00))
        spend_cycle();
}

/*
   ADC_INDX - Add with Carry using (Indirect, X) addressing mode.
   In this mode, the operand is a zero-page base address. The X register is
   added to this address (with wrap-around) to get a new zero-page pointer.
   The two bytes read from that pointer form the effective 16-bit address.
   The value at that address is added to A along with the Carry flag.
*/

static inline void
ADC_INDX (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte operand = FetchByte(bus, memory, cpu);
  Byte pointer = (Byte)(operand + cpu->X);

  cpu_read(bus, memory, pointer);
  Byte low = bus->data;

  cpu_read(bus, memory, (Byte)(pointer + 1));
  Byte high = bus->data;

  Word address = ((Word)high << 8) | low;

  cpu_read(bus, memory, address);
  ADC(cpu, bus->data);

  spend_cycles(6);
}

/*
   ADC_INDY - Add with Carry using (Indirect), Y addressing mode.
   The operand is a zero-page pointer to a 16-bit base address.
   The Y register is added to this base to form the effective address.
   The byte read from that address is added to A along with the Carry flag.
   If a page boundary is crossed, one extra cycle is consumed.
*/

static inline void
ADC_INDY(Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
    Byte pointer = FetchByte(bus, memory, cpu);

    cpu_read(bus, memory, pointer);
    Byte low = bus->data;

    cpu_read(bus, memory, (Byte)(pointer + 1));
    Byte high = bus->data;

    Word base_address = ((Word)high << 8) | low;
    Word address = (Word)(base_address + cpu->Y);

    cpu_read(bus, memory, address);
    ADC(cpu, bus->data);

    spend_cycles(5);

    if ((base_address & 0xFF00) != (address & 0xFF00))
        spend_cycle();
}

#endif // ADC_H
