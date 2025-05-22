#ifndef CLD_H
#define CLD_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the CLD (Clear Decimal Mode) instruction for MOS
   Technology 6502. CLD clears the Decimal Mode flag in the processor status
   register. For more information about the instructions, refer to
   Instructions.MD
*/

/*
   CLD - Clear Decimal Mode:
   This function clears the Decimal Mode flag (D) in the CPU status register.
   It adjusts the cycle count accordingly.
*/

static inline void
CLDSetStatus (CPU6502 *cpu)
{
  cpu->Flag.D = 0;
}

static inline void
CLD (Word *Cycles, CPU6502 *cpu)
{
  CLDSetStatus (cpu);
  (*Cycles)--;
  spend_cycles (2);
}

#endif // CLD_H
