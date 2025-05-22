#ifndef SEI_H
#define SEI_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the SEI (Set Interrupt Disable) instruction for
   MOS Technology 6502. SEI sets the Interrupt Disable flag in the Status
   register, preventing interrupts. For more information about the
   instructions, refer to Instructions.MD
*/

/*
   SEI - Set Interrupt Disable Flag:
   This function sets the Interrupt Disable flag (I) to 1.
   It adjusts the cycle count accordingly.
*/

static inline void
SEI (Word *Cycles, CPU6502 *cpu)
{
  cpu->Flag.I = 1;
  (*Cycles)--;
  spend_cycles (2);
}

#endif // SEI_H
