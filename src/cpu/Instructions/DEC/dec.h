#ifndef DEC_H
#define DEC_H

#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the DEC (Decrement Memory) instruction for MOS
   Technology 6502. DEC works by subtracting 1 from the value at a memory
   address. For more information about the instructions, refer to
   Instructions.MD
*/

/*
   DEC (Decrement Memory) instruction supports various addressing modes in the
   6502 architecture. The different modes provide flexibility in specifying the
   memory location to decrement.
*/

/*
   This function sets the Flags for the Status register
   to identify what happened during the DEC instruction.
   It updates Zero and Negative flags based on the decremented value.
*/
static inline void
DECSetStatus (Byte Value, CPU6502 *cpu)
{
  cpu->Flag.Z = (Value == 0);
  cpu->Flag.N = (Value & 0x80) > 0;
}

/*
   DEC_ZP - Decrement the value at a Zero Page memory address.
   This function fetches a byte representing a zero-page address from memory,
   reads the value at that address, decrements it by 1,
   writes the result back, and sets the status flags.
*/
static inline void
DEC_ZP (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);

  cpu_read (bus, memory, ZeroPageAddr, Cycles);
  Byte DecrementValue = bus->data - 1;

  cpu_write (bus, memory, ZeroPageAddr, DecrementValue, Cycles);
  DECSetStatus (DecrementValue, cpu);
  spend_cycles (5);
}

/*
   DEC_ZPX - Decrement the value at a Zero Page memory address offset by X.
   This function fetches a byte representing a zero-page address from memory,
   adds the CPU's X register to it, reads the value at the resulting address,
   decrements it by 1, writes the result back, and sets the status flags.
*/
static inline void
DEC_ZPX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte ZeroPageAddr = FetchByte (Cycles, memory, cpu);
  ZeroPageAddr += cpu->X;
  (*Cycles)--;

  cpu_read (bus, memory, ZeroPageAddr, Cycles);
  Byte DecrementValue = bus->data - 1;

  cpu_write (bus, memory, ZeroPageAddr, DecrementValue, Cycles);
  DECSetStatus (DecrementValue, cpu);
  spend_cycles (6);
}

/*
   DEC_ABS - Decrement the value at an Absolute memory address.
   This function fetches a two-byte absolute address from memory,
   reads the value at that address, decrements it by 1,
   writes the result back, and sets the status flags.
*/
static inline void
DEC_ABS (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);

  cpu_read (bus, memory, Absolute, Cycles);
  Byte DecrementValue = bus->data - 1;

  cpu_write (bus, memory, Absolute, DecrementValue, Cycles);
  DECSetStatus (DecrementValue, cpu);
  spend_cycles (6);
}

/*
   DEC_ABSX - Decrement the value at an Absolute memory address plus X offset.
   This function fetches a two-byte absolute address from memory,
   adds the CPU's X register to it, reads the value at the resulting address,
   decrements it by 1, writes the result back, and sets the status flags.
*/
static inline void
DEC_ABSX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word Absolute = FetchWord (Cycles, memory, cpu);
  Absolute += cpu->X;
  (*Cycles)--;

  cpu_read (bus, memory, Absolute, Cycles);
  Byte DecrementValue = bus->data - 1;

  cpu_write (bus, memory, Absolute, DecrementValue, Cycles);
  DECSetStatus (DecrementValue, cpu);
  spend_cycles (6);
}

#endif // DEC_H
