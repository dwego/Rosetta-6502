#ifndef CLC_H
#define CLC_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the CLC (Clear Carry Flag) instruction for MOS
   Technology 6502. CLC clears the Carry flag in the processor status register.
   For more information about the instructions, refer to Instructions.MD
*/

/*
   CLC - Clear Carry Flag:
   This function clears the Carry flag in the CPU status register.
   It adjusts the cycle count accordingly.
*/

static inline void
CLCSetStatus (CPU6502 *cpu)
{
  cpu->Flag.C = 0;
}

static inline void
CLC (CPU6502 *cpu)
{
  CLCSetStatus (cpu);
  
  spend_cycles (2);
}

#endif // CLC_H
