#ifndef SED_H
#define SED_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the SED (Set Decimal Mode) instruction for MOS
   Technology 6502. SED sets the Decimal Mode in the Status register. For more
   information about the instructions, refer to Instructions.MD
*/

/*
   SED - Set Decimal Mode:
   This function sets the Decimal Mode (D) to 1.
   It adjusts the cycle count accordingly.
*/

static inline void
SED (CPU6502 *cpu)
{
  cpu->Flag.D = 1;
  
  spend_cycles (2);
}

#endif // SED_H
