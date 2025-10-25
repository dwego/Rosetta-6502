#ifndef ROL_H
#define ROL_H

#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the ROL (Rotate Left) instruction for MOS
   Technology 6502. ROL shifts all bits of a byte left by one position. The
   carry flag (C) is shifted into bit 0, and the original bit 7 is shifted into
   the carry flag. For more information about the instructions, refer to
   Instructions.MD
*/

/*
   ROL supports various addressing modes in the 6502 architecture.
   These modes provide flexibility in specifying the operand for the rotation.
*/

/*
   This function sets the Flags for the Status register
   to identify what happened during the ROL instruction.
   - Carry flag is set from the original bit 7.
   - Zero flag is set if the result is zero.
   - Negative flag is set from the bit 7 of the result.
*/
static inline void
ROLSetStatus (Byte originalValue, Byte result, CPU6502 *cpu)
{
  cpu->Flag.C = (originalValue & 0x80) ? 1 : 0;
  cpu->Flag.Z = (result == 0);
  cpu->Flag.N = (result & 0x80) != 0;
}

/*
   ROL_ACC - Rotate Left the Accumulator.
   This function rotates the bits of the accumulator left by one,
   incorporating the carry flag, updates the accumulator,
   sets the status flags, and spends cycles.
*/
static inline void
ROL_ACC (Word *Cycles, CPU6502 *cpu)
{
  Byte oldCarry = cpu->Flag.C;
  Byte original = cpu->A;

  Byte result = (original << 1) | oldCarry;
  cpu->A = result;
  (*Cycles)--;

  ROLSetStatus (original, result, cpu);
  spend_cycles (2);
}

/*
   ROL_ZP - Rotate Left the byte at Zero Page address.
   This function fetches a zero page address from memory,
   reads the byte at that address, rotates it left with carry,
   writes the result back, updates status flags, and spends cycles.
*/
static inline void
ROL_ZP (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte addr = FetchByte (Cycles, bus, memory, cpu);

  cpu_read (bus, memory, addr, Cycles);
  Byte original = bus->data;
  Byte oldCarry = cpu->Flag.C;

  Byte result = (original << 1) | oldCarry;
  cpu_write (bus, memory, addr, result, Cycles);

  ROLSetStatus (original, result, cpu);
  spend_cycles (5);
}

/*
   ROL_ZPX - Rotate Left the byte at Zero Page address plus X offset.
   Similar to ROL_ZP, but adds the X register to the zero page address before
   rotation.
*/
static inline void
ROL_ZPX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte addr = FetchByte (Cycles, bus, memory, cpu);
  addr += cpu->X;
  (*Cycles)--;

  cpu_read (bus, memory, addr, Cycles);
  Byte original = bus->data;
  Byte oldCarry = cpu->Flag.C;

  Byte result = (original << 1) | oldCarry;
  cpu_write (bus, memory, addr, result, Cycles);

  ROLSetStatus (original, result, cpu);
  spend_cycles (6);
}

/*
   ROL_ABS - Rotate Left the byte at Absolute address.
   This function fetches a two-byte absolute address,
   rotates the byte at that address left with carry,
   writes the result back, sets flags, and spends cycles.
*/
static inline void
ROL_ABS (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word addr = FetchWord (Cycles, bus, memory, cpu);

  cpu_read (bus, memory, addr, Cycles);
  Byte original = bus->data;
  Byte oldCarry = cpu->Flag.C;

  Byte result = (original << 1) | oldCarry;
  cpu_write (bus, memory, addr, result, Cycles);

  ROLSetStatus (original, result, cpu);
  spend_cycles (6);
}

/*
   ROL_ABSX - Rotate Left the byte at Absolute address plus X offset.
   Similar to ROL_ABS, but adds the X register to the absolute address before
   rotation.
*/
static inline void
ROL_ABSX (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word addr = FetchWord (Cycles, bus, memory, cpu);
  addr += cpu->X;

  cpu_read (bus, memory, addr, Cycles);
  Byte original = bus->data;
  Byte oldCarry = cpu->Flag.C;

  Byte result = (original << 1) | oldCarry;
  cpu_write (bus, memory, addr, result, Cycles);

  ROLSetStatus (original, result, cpu);
  spend_cycles (7);
}

#endif // ROL_H
