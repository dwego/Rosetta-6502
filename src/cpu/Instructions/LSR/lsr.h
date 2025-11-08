#ifndef LSR_H
#define LSR_H

#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   Header file for the LSR (Logical Shift Right) instruction of the MOS 6502
   CPU. LSR shifts all bits of a byte one position to the right. The least
   significant bit (LSB) is copied to the Carry flag. The most significant bit
   (MSB) is always set to 0. For more information, see Instructions.MD.
*/

/*
   LSR supports multiple addressing modes.
   Each mode determines where the shift operation is applied (Accumulator or
   Memory).
*/

/*
   This function sets the processor flags after an LSR operation.
   - Carry (C): set to bit 0 (LSB) of the original value.
   - Zero (Z): set if the result is 0.
   - Negative (N): always cleared (0), since MSB is always 0 after shift.
   This version is for the Accumulator mode.
*/
static inline void
LSRSetStatus (Byte Value, CPU6502 *cpu)
{
  cpu->Flag.C = Value & 0x01;
  cpu->A = Value >> 1;
  cpu->Flag.Z = (cpu->A == 0);
  cpu->Flag.N = 0;
}

/*
   LSR_ACC - Logical Shift Right on the Accumulator (implied mode).
   Performs the shift directly on the A register.
*/
static inline void
LSR_ACC (CPU6502 *cpu)
{
  Byte Value = cpu->A;
  LSRSetStatus (Value, cpu);
  ;
  spend_cycles (2);
}

/*
   LSR_ZP - Logical Shift Right on Zero Page address.
   Reads the value from memory, performs the shift, writes the result back,
   and updates flags accordingly.
*/
static inline void
LSR_ZP (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte addr = FetchByte (bus, memory, cpu);
  cpu_read (bus, memory, addr, cpu);
  Byte Value = bus->data;
  cpu_write (bus, memory, addr, Value >> 1, cpu);

  cpu->Flag.C = Value & 0x01;
  cpu->Flag.Z = ((Value >> 1) == 0);
  cpu->Flag.N = 0;
  spend_cycles (5);
}

/*
   LSR_ZPX - Logical Shift Right on Zero Page address offset by X.
   Applies wrapping within 0x00–0xFF.
*/
static inline void
LSR_ZPX (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte addr = FetchByte (bus, memory, cpu);
  addr += cpu->X;
  

  cpu_read (bus, memory, addr, cpu);
  Byte Value = bus->data;
  cpu_write (bus, memory, addr, Value >> 1, cpu);

  cpu->Flag.C = Value & 0x01;
  cpu->Flag.Z = ((Value >> 1) == 0);
  cpu->Flag.N = 0;
  spend_cycles (6);
}

/*
   LSR_ABS - Logical Shift Right on Absolute address.
   Reads the full 16-bit address from memory, applies shift, writes back the
   result.
*/
static inline void
LSR_ABS (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word addr = FetchWord (bus, memory, cpu);
  cpu_read (bus, memory, addr, cpu);
  Byte Value = bus->data;
  cpu_write (bus, memory, addr, Value >> 1, cpu);

  cpu->Flag.C = Value & 0x01;
  cpu->Flag.Z = ((Value >> 1) == 0);
  cpu->Flag.N = 0;
  spend_cycles (6);
}

/*
   LSR_ABSX - Logical Shift Right on Absolute address offset by X.
   Reads the address, adds X, performs the shift, and writes the result back.
*/
static inline void
LSR_ABSX (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word addr = FetchWord (bus, memory, cpu);
  addr += cpu->X;

  cpu_read (bus, memory, addr, cpu);
  Byte Value = bus->data;
  cpu_write (bus, memory, addr, Value >> 1, cpu);

  cpu->Flag.C = Value & 0x01;
  cpu->Flag.Z = ((Value >> 1) == 0);
  cpu->Flag.N = 0;
  spend_cycles (6);
}

#endif // LSR_H
