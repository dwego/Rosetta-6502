#ifndef ROR_H
#define ROR_H

#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the ROR (Rotate Right) instruction for MOS
   Technology 6502. ROR rotates the bits of a byte right by one position. The
   carry flag (C) is shifted into bit 7, and the original bit 0 is shifted into
   the carry flag. For more information about the instructions, refer to
   Instructions.MD
*/

/*
   ROR supports various addressing modes in the 6502 architecture.
   These modes provide flexibility in specifying the operand for the rotation.
*/

/*
   This function sets the Flags for the Status register
   to identify what happened during the ROR instruction.
   - Carry flag is set from the original bit 0.
   - Zero flag is set if the result is zero.
   - Negative flag is set from bit 7 of the result.
*/
static inline void
RORSetStatus (Byte originalValue, Byte result, CPU6502 *cpu)
{
  cpu->Flag.C = (originalValue & 0x01) ? 1 : 0;
  cpu->Flag.Z = (result == 0);
  cpu->Flag.N = (result & 0x80) != 0;
}

/*
   ROR_ACC - Rotate Right the Accumulator.
   This function rotates the bits of the accumulator right by one,
   incorporating the carry flag into bit 7,
   updates the accumulator, sets status flags, and spends cycles.
*/
static inline void
ROR_ACC (Word *Cycles, CPU6502 *cpu)
{
  Byte original = cpu->A;
  Byte oldCarry = cpu->Flag.C;

  Byte result = (original >> 1) | (oldCarry << 7);
  cpu->A = result;
  (*Cycles)--;

  RORSetStatus (original, result, cpu);
}

/*
   ROR_ZP - Rotate Right the byte at Zero Page address.
   This function fetches a zero page address from memory,
   reads the byte at that address, rotates it right with carry,
   writes the result back, updates status flags, and spends cycles.
*/
static inline void
ROR_ZP (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte addr = FetchByte (Cycles, bus, memory, cpu);

  cpu_read (bus, memory, addr, Cycles);
  Byte original = bus->data;
  Byte oldCarry = cpu->Flag.C;

  Byte result = (original >> 1) | (oldCarry << 7);
  cpu_write (bus, memory, addr, result, Cycles);

  RORSetStatus (original, result, cpu);
}

/*
   ROR_ZPX - Rotate Right the byte at Zero Page address plus X offset.
   Similar to ROR_ZP, but adds the X register to the zero page address before
   rotation.
*/
static inline void
ROR_ZPX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte addr = FetchByte (Cycles, bus, memory, cpu);
  addr += cpu->X;
  (*Cycles)--;

  cpu_read (bus, memory, addr, Cycles);
  Byte original = bus->data;
  Byte oldCarry = cpu->Flag.C;

  Byte result = (original >> 1) | (oldCarry << 7);
  cpu_write (bus, memory, addr, result, Cycles);

  RORSetStatus (original, result, cpu);
}

/*
   ROR_ABS - Rotate Right the byte at Absolute address.
   This function fetches a two-byte absolute address,
   rotates the byte at that address right with carry,
   writes the result back, sets flags, and spends cycles.
*/
static inline void
ROR_ABS (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word addr = FetchWord (Cycles, bus, memory, cpu);

  cpu_read (bus, memory, addr, Cycles);
  Byte original = bus->data;
  Byte oldCarry = cpu->Flag.C;

  Byte result = (original >> 1) | (oldCarry << 7);
  cpu_write (bus, memory, addr, result, Cycles);

  RORSetStatus (original, result, cpu);
}

/*
   ROR_ABSX - Rotate Right the byte at Absolute address plus X offset.
   Similar to ROR_ABS, but adds the X register to the absolute address before
   rotation.
*/
static inline void
ROR_ABSX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word addr = FetchWord (Cycles, bus, memory, cpu);
  addr += cpu->X;

  cpu_read (bus, memory, addr, Cycles);
  Byte original = bus->data;
  Byte oldCarry = cpu->Flag.C;

  Byte result = (original >> 1) | (oldCarry << 7);
  cpu_write (bus, memory, addr, result, Cycles);

  RORSetStatus (original, result, cpu);
}

#endif // ROR_H
