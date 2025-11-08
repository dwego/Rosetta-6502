#ifndef DEX_H
#define DEX_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the DEX (Decrement X Register) instruction for MOS
   Technology 6502. DEX works by decrementing the CPU's X register by 1. For
   more information about the instructions, refer to Instructions.MD
*/

/*
   DEX instruction does not use addressing modes because it operates directly
   on the CPU's X register.
*/

/*
   This function sets the Flags for the Status register
   to identify what happened during the DEX instruction.
   It updates the Zero and Negative flags based on the new value of X.
*/
static inline void
DEXSetStatus (CPU6502 *cpu)
{
  cpu->Flag.Z = (cpu->X == 0);
  cpu->Flag.N = (cpu->X & 0x80) > 0;
}

/*
   DEX - Decrement the X register by 1.
   This function decrements the X register, updates the cycle count,
   sets the status flags, and spends the required CPU cycles.
*/
static inline void
DEX (CPU6502 *cpu)
{
  cpu->X--;
  DEXSetStatus (cpu);
  
  spend_cycles (2);
}

#endif // DEX_H
