#ifndef INC_H
#define INC_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the INC (Increment Memory) instruction for MOS
   Technology 6502. INC increments the value stored at a specified memory
   address by one. It affects the Zero and Negative flags based on the result
   of the increment operation. It does NOT modify the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   INC instruction supports various addressing modes in the 6502 architecture.
   These modes specify the memory location whose value will be incremented.
*/

/*
   This function sets the Flags for the Status register
   based on the result of the INC instruction.
   It updates the Zero (Z) and Negative (N) flags according to the incremented
   value.
*/
static inline void
INCSetStatus (CPU6502 *cpu, Byte value)
{
  cpu->Flag.Z = (value == 0);
  cpu->Flag.N = (value & 0x80) != 0;
}

/*
   INC_ZP - Increment Memory at Zero Page address.
   Fetches a zero-page address from memory, reads the value at that address,
   increments it by one, writes it back to memory, then updates the flags.
*/
static inline void
INC_ZP (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);
  Byte Value = ReadByte (Cycles, ZeroPageAddr, memory);
  Byte IncrementedValue = Value + 1;

  WriteByte (Cycles, IncrementedValue, memory, ZeroPageAddr);
  INCSetStatus (cpu, IncrementedValue);
  spend_cycles (5);
}

/*
   INC_ZPX - Increment Memory at Zero Page address offset by X.
   Fetches a zero-page address, adds the X register, reads the value,
   increments it, writes it back, then updates the flags.
*/
static inline void
INC_ZPX (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);
  ZeroPageAddr += cpu->X;

  Byte Value = ReadByte (Cycles, ZeroPageAddr, memory);
  Byte IncrementedValue = Value + 1;

  WriteByte (Cycles, IncrementedValue, memory, ZeroPageAddr);
  INCSetStatus (cpu, IncrementedValue);
  spend_cycles (6);
}

/*
   INC_ABS - Increment Memory at Absolute address.
   Fetches a 16-bit absolute address, reads the value at that address,
   increments it, writes it back, then updates the flags.
*/
static inline void
INC_ABS (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);
  Byte Value = ReadByte (Cycles, Absolute, memory);
  Byte IncrementedValue = Value + 1;

  WriteByte (Cycles, IncrementedValue, memory, Absolute);
  INCSetStatus (cpu, IncrementedValue);
  spend_cycles (6);
}

/*
   INC_ABSX - Increment Memory at Absolute address offset by X.
   Fetches a 16-bit absolute address, adds the X register,
   reads the value, increments it, writes it back, then updates the flags.
*/
static inline void
INC_ABSX (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);
  Absolute += cpu->X;

  Byte Value = ReadByte (Cycles, Absolute, memory);
  Byte IncrementedValue = Value + 1;

  WriteByte (Cycles, IncrementedValue, memory, Absolute);
  INCSetStatus (cpu, IncrementedValue);
  spend_cycles (6);
}

#endif // INC_H
