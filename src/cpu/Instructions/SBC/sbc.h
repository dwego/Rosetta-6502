#ifndef SBC_H
#define SBC_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

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
SBC_IM (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte Value = FetchByte (Cycles, memory, cpu);
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
SBC_ZP (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);
  Byte Value = ReadByte (Cycles, ZeroPageAddr, memory);
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
SBC_ZPX (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);
  ZeroPageAddr += cpu->X;

  Byte Value = ReadByte (Cycles, ZeroPageAddr, memory);
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
SBC_ABS (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);

  Byte Value = ReadByte (Cycles, Absolute, memory);
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
SBC_ABSX (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);
  Word NewAddress = Absolute + cpu->X;

  if ((NewAddress & 0xFF00) != (Absolute & 0xFF00))
    {
      (*Cycles)++;
      spend_cycle ();
    }

  Byte Value = ReadByte (Cycles, NewAddress, memory);
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
SBC_ABSY (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);
  Word NewAddress = Absolute + cpu->Y;

  if ((NewAddress & 0xFF00) != (Absolute & 0xFF00))
    {
      (*Cycles)++;
      spend_cycle ();
    }

  Byte Value = ReadByte (Cycles, NewAddress, memory);
  Byte Before = cpu->A;

  Byte Result = cpu->A + (~Value) + cpu->Flag.C;
  cpu->A = Result;

  SBCSetStatus (cpu, Before, Value, Result);
  spend_cycles (4);
}

#endif // SBC_H
