#ifndef CLV_H
#define CLV_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the CLV (Clear Overflow Flag) instruction for the
   MOS Technology 6502. CLV clears the Overflow flag (V) in the processor
   status register. For more information about the instructions, refer to
   Instructions.MD
*/

/*
   CLV - Clear Overflow Flag:
   This function clears the Overflow flag (V) in the CPU status register.
   It adjusts the cycle count accordingly.
*/

static inline void
CLVSetStatus (CPU6502 *cpu)
{
  cpu->Flag.V = 0;
}

static inline void
CLV (CPU6502 *cpu)
{
  CLVSetStatus (cpu);
  
  spend_cycles (2);
}

#endif // CLV_H
