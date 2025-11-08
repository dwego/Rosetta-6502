#ifndef PHA_H
#define PHA_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   Header file for the PHA (Push Accumulator) instruction for the MOS
   Technology 6502.

   The PHA instruction pushes the current value of the Accumulator (A)
   onto the stack. It does not affect any status flags.
   It always uses the implied addressing mode.

   For more information about the instructions, refer to Instructions.MD
*/

/*
   PHA - Push Accumulator onto the stack.
   This function pushes the value of the Accumulator (A) onto the stack.
   It does not modify the status flags.
*/
static inline void
PHA (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  PushByteToStack (bus, memory, cpu->A, cpu);
  spend_cycles (3); // PHA takes 3 cycles
}

#endif // PHA_H
