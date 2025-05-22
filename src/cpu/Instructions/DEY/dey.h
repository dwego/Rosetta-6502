#ifndef DEY_H
#define DEY_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the DEY (Decrement Y Register) instruction for MOS
   Technology 6502. DEY works by decrementing the CPU's Y register by 1. For
   more information about the instructions, refer to Instructions.MD
*/

/*
   DEY instruction does not use addressing modes because it operates directly
   on the CPU's Y register.
*/

/*
   This function sets the Flags for the Status register
   to identify what happened during the DEY instruction.
   It updates the Zero and Negative flags based on the new value of Y.
*/
static inline void
DEYSetStatus (CPU6502 *cpu)
{
  cpu->Flag.Z = (cpu->Y == 0);
  cpu->Flag.N = (cpu->Y & 0x80) > 0;
}

/*
   DEY - Decrement the Y register by 1.
   This function decrements the Y register, updates the cycle count,
   sets the status flags, and spends the required CPU cycles.
*/
static inline void
DEY (Word *Cycles, CPU6502 *cpu)
{
  cpu->Y--;
  DEYSetStatus (cpu);
  (*Cycles)--;
  spend_cycles (2);
}

#endif // DEY_H
