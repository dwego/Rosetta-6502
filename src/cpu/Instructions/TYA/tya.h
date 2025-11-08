#ifndef TYA_H
#define TYA_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the TYA (Transfer Y to Accumulator) instruction
   for MOS Technology 6502. TYA works by transferring the value from the Index
   Register Y (Y) into the Accumulator register (A). This instruction updates
   the Zero and Negative flags based on the new value of the Accumulator. For
   more information about the instructions, refer to Instructions.MD
*/

/*
   This function sets the flags in the Status register
   to reflect the result of the TYA instruction.
*/
static inline void
TYASetStatus (CPU6502 *cpu)
{
  cpu->Flag.Z = (cpu->A == 0);
  cpu->Flag.N = (cpu->A & 0x80) != 0;
}

/*
   TYA - Transfer Y to Accumulator.
   Copies the value from the Y register into the Accumulator (A).
   Updates Zero and Negative flags accordingly.
   Consumes 2 CPU cycles.
*/
static inline void
TYA (CPU6502 *cpu)
{
  cpu->A = cpu->Y;
  TYASetStatus (cpu);
  
  spend_cycles (2);
}

#endif // TYA_H
