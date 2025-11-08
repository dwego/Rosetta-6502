#ifndef SEC_H
#define SEC_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the SEC (Set Carry Flag) instruction for MOS
   Technology 6502. SEC sets the Carry Flag in the Status register. For more
   information about the instructions, refer to Instructions.MD
*/

/*
   SEC - Set Carry Flag:
   This function sets the Carry Flag (C) to 1.
   It adjusts the cycle count accordingly.
*/

static inline void
SEC (CPU6502 *cpu)
{
  cpu->Flag.C = 1;
  
  spend_cycles (2);
}

#endif // SEC_H
