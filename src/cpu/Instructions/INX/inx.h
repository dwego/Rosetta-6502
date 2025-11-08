#ifndef INX_H
#define INX_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the INX (Increment X Register) instruction for MOS
   Technology 6502. INX increments the X register by 1. It updates the Zero and
   Negative flags according to the new value of X. This instruction uses
   implied addressing mode (no memory access). For more information about the
   instructions, refer to Instructions.MD
*/

/*
   This function sets the Flags for the Status register
   based on the current value of the X register.
*/
static inline void
INXSetStatus (CPU6502 *cpu)
{
  cpu->Flag.Z = (cpu->X == 0);
  cpu->Flag.N = (cpu->X & 0x80) != 0;
}

/*
   INX - Increment X Register.
   Increments the X register, updates the status flags,
   and spends the required CPU cycles.
*/
static inline void
INX (CPU6502 *cpu)
{
  cpu->X++;
  INXSetStatus (cpu);
  spend_cycles (2);
  ; // or decrement accordingly, depending on your cycle tracking
                  // system
}

#endif // INX_H
