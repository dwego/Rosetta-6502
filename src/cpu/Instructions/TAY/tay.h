#ifndef TAY_H
#define TAY_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the TAY (Transfer Accumulator to Index Y)
   instruction for MOS Technology 6502. TAY copies the value from the
   Accumulator register (A) to the Index Register Y (Y). For more information
   about the instructions, refer to Instructions.MD
*/

/*
   TAY affects the processor status flags:
   - Zero flag (Z) is set if the new Y value is zero.
   - Negative flag (N) is set if bit 7 of the new Y value is set.
*/

/*
   This function sets the Flags for the Status register
   based on the current value of the Y register.
*/
static inline void
TAYSetStatus (CPU6502 *cpu)
{
  cpu->Flag.Z = (cpu->Y == 0);
  cpu->Flag.N = (cpu->Y & 0x80) != 0;
}

/*
   TAY - Transfer Accumulator to Index Y.
   Copies the value of the Accumulator into the Y register,
   then updates the Zero and Negative flags accordingly.
   Consumes 2 CPU cycles.
*/
static inline void
TAY (Word *Cycles, CPU6502 *cpu)
{
  cpu->Y = cpu->A;
  TAYSetStatus (cpu);
  (*Cycles)--;
  spend_cycles (2);
}

#endif // TAY_H
