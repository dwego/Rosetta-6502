#ifndef SBC_H
#define SBC_H

#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"
#include <stdatomic.h>

/*
   This is a header file for the SBC (Subtract with Carry) instruction for MOS
   Technology 6502. SBC subtracts a value and the inverse of the carry flag
   from the Accumulator register (A). The instruction performs A = A + (~value)
   + Carry. For more information about the instructions, refer to
   Instructions.MD
*/

/*
   This function sets the Flags for the Status register
   to represent the result of the SBC instruction.
*/

static inline void
SBCSetStatus (CPU6502 *cpu, Byte before, Byte value, Byte result)
{
  cpu->Flag.C
      = (result
         <= before); // Carry is set if no borrow occurred (result <= before)
  cpu->Flag.Z = (result == 0);
  cpu->Flag.N = (result & 0x80) != 0;
  // Overflow is set if the sign bit of result is incorrect for subtraction
  cpu->Flag.V = ((before ^ result) & (before ^ value) & 0x80) != 0;
}

/*
   SBC_IM - Subtract Immediate value and the inverse of carry flag from the
   Accumulator. This function fetches a byte from memory, performs A = A +
   (~value) + Carry, then sets the status flags.
*/

static inline void
SBC_IM (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte Value = FetchByte (Cycles, bus, memory, cpu);
  Byte Before = cpu->A;

  // Perform subtraction via ADC with complemented value
  Byte Result = cpu->A + (~Value) + cpu->Flag.C;
  cpu->A = Result;

  SBCSetStatus (cpu, Before, Value, Result);
  spend_cycles (2);
}

/*
   SBC_ZP - Subtract value from Zero Page and the inverse of carry flag from
   the Accumulator. This function fetches a zero-page address from memory,
   reads the value at that address, performs A = A + (~value) + Carry, then
   sets the status flags.
*/

static inline void
SBC_ZP (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, bus, memory, cpu);
  cpu_read (bus, memory, ZeroPageAddr, Cycles, cpu);
  Byte Value = bus->data;
  Byte Before = cpu->A;

  Byte Result = cpu->A + (~Value) + cpu->Flag.C;
  cpu->A = Result;

  SBCSetStatus (cpu, Before, Value, Result);
  spend_cycles (3);
}

/*
   SBC_ZPX - Subtract value from Zero Page with X Offset and the inverse of
   carry flag from the Accumulator. This function fetches a zero-page address
   from memory, adds the X register, reads the value at the resulting address,
   performs A = A + (~value) + Carry, then sets the status flags.
*/

static inline void
SBC_ZPX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, bus, memory, cpu);
  ZeroPageAddr += cpu->X;

  cpu_read (bus, memory, ZeroPageAddr, Cycles, cpu);
  Byte Value = bus->data;
  Byte Before = cpu->A;

  Byte Result = cpu->A + (~Value) + cpu->Flag.C;
  cpu->A = Result;

  SBCSetStatus (cpu, Before, Value, Result);
  spend_cycles (4);
}

/*
   SBC_ABS - Subtract value from Absolute address and the inverse of carry flag
   from the Accumulator. This function fetches an absolute address from memory,
   reads the value at that address, performs A = A + (~value) + Carry, then
   sets the status flags.
*/

static inline void
SBC_ABS (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);

  cpu_read (bus, memory, Absolute, Cycles, cpu);
  Byte Value = bus->data;
  Byte Before = cpu->A;

  Byte Result = cpu->A + (~Value) + cpu->Flag.C;
  cpu->A = Result;

  SBCSetStatus (cpu, Before, Value, Result);
  spend_cycles (4);
}

/*
   SBC_ABSX - Subtract value from Absolute address with X Offset and the
   inverse of carry flag from the Accumulator. This function fetches an
   absolute address from memory, adds the X register, reads the value at the
   resulting address, performs A = A + (~value) + Carry, then sets the status
   flags.
*/

static inline void
SBC_ABSX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);
  Word NewAddress = Absolute + cpu->X;

  if ((NewAddress & 0xFF00) != (Absolute & 0xFF00))
    {
      (*Cycles)++;
      spend_cycle ();
    }

  cpu_read (bus, memory, Absolute, Cycles, cpu);
  Byte Value = bus->data;
  Byte Before = cpu->A;

  Byte Result = cpu->A + (~Value) + cpu->Flag.C;
  cpu->A = Result;

  SBCSetStatus (cpu, Before, Value, Result);
  spend_cycles (4);
}

/*
   SBC_ABSY - Subtract value from Absolute address with Y Offset and the
   inverse of carry flag from the Accumulator. This function fetches an
   absolute address from memory, adds the Y register, reads the value at the
   resulting address, performs A = A + (~value) + Carry, then sets the status
   flags.
*/

static inline void
SBC_ABSY (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, bus, memory, cpu);
  Word NewAddress = Absolute + cpu->Y;

  if ((NewAddress & 0xFF00) != (Absolute & 0xFF00))
    {
      (*Cycles)++;
      spend_cycle ();
    }

  cpu_read (bus, memory, NewAddress, Cycles, cpu);
  Byte Value = bus->data;
  Byte Before = cpu->A;

  Byte Result = cpu->A + (~Value) + cpu->Flag.C;
  cpu->A = Result;

  SBCSetStatus (cpu, Before, Value, Result);
  spend_cycles (4);
}

/*
   SBC_INDX - Subtract using (Indirect, X) addressing mode.
   In this mode, the operand is a zero-page base address. The X register is
   added to this base address (wrapping in zero page) to get a new zero-page
   location. The two bytes read from that location form the effective 16-bit
   address.
*/

static inline void
SBC_INDX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte zp = FetchByte (Cycles, bus, memory, cpu);
  zp += cpu->X; // zero-page wrap
  Byte lo = memory->Data[zp];
  Byte hi = memory->Data[(Byte)(zp + 1)];
  Word addr = (hi << 8) | lo;

  cpu_read (bus, memory, addr, Cycles, cpu);
  Byte Value = bus->data;
  Byte Before = cpu->A;

  Byte Result = cpu->A + (~Value) + cpu->Flag.C;
  cpu->A = Result;

  SBCSetStatus (cpu, Before, Value, Result);
  spend_cycles (6);
}

/*
   SBC_INDY - Subtract using (Indirect), Y addressing mode.
   The operand is a zero-page pointer to a 16-bit base address.
   The Y register is added to this base address to form the effective
   target address. The byte from that address is subtracted from A with Carry.
*/

static inline void
SBC_INDY (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte zp = FetchByte (Cycles, bus, memory, cpu);
  Byte lo = memory->Data[zp];
  Byte hi = memory->Data[(Byte)(zp + 1)];
  Word base = (hi << 8) | lo;
  Word addr = base + cpu->Y;

  if ((base & 0xFF00) != (addr & 0xFF00)) // page crossed
    {
      (*Cycles)++;
      spend_cycle ();
    }

  cpu_read (bus, memory, addr, Cycles, cpu);
  Byte Value = bus->data;
  Byte Before = cpu->A;

  Byte Result = cpu->A + (~Value) + cpu->Flag.C;
  cpu->A = Result;

  SBCSetStatus (cpu, Before, Value, Result);
  spend_cycles (5);
}

#endif // SBC_H
