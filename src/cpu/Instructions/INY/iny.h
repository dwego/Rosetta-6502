#ifndef INY_H
#define INY_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the INY (Increment Y Register) instruction for MOS
   Technology 6502. INY increments the Y register by 1. It updates the Zero and
   Negative flags according to the new value of Y. This instruction uses
   implied addressing mode (no memory access). For more information about the
   instructions, refer to Instructions.MD
*/

/*
   This function sets the Flags for the Status register
   based on the current value of the Y register.
*/
static inline void
INYSetStatus (CPU6502 *cpu)
{
  cpu->Flag.Z = (cpu->Y == 0);
  cpu->Flag.N = (cpu->Y & 0x80) != 0;
}

/*
   INY - Increment Y Register.
   Increments the Y register, updates the status flags,
   and spends the required CPU cycles.
*/
static inline void
INY (CPU6502 *cpu)
{
  cpu->Y++;
  INYSetStatus (cpu);
  spend_cycles (2);
  ;
}

#endif // INY_H
