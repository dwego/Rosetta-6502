#ifndef NOP_H
#define NOP_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the NOP (No Operation) instruction for the MOS
   Technology 6502. NOP performs no operation and simply advances the program
   counter by one byte. It is often used for timing adjustments or as padding.
   For more information about the instructions, refer to Instructions.MD
*/

/*
   NOP - No Operation:
   This function simulates the NOP instruction which does nothing except
   consume time. It decreases the cycle count and optionally triggers a dummy
   cycle (for accuracy in emulation).
*/

static inline void
NOP (Word *Cycles)
{
  (*Cycles)--;      // Decrease the cycle count by one
  spend_cycles (2); // Simulate 2 CPU cycles typically used by NOP
}

#endif // NOP_H
