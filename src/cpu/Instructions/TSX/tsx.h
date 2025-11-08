#ifndef TSX_H
#define TSX_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the TSX (Transfer Stack Pointer to Index X)
   instruction for the MOS Technology 6502. TSX copies the value from the Stack
   Pointer (SP) register into the Index Register X (X). For more information
   about the instructions, refer to Instructions.MD
*/

/*
   This function sets the Flags for the Status register
   based on the current value of the X register after the transfer.
*/
static inline void
TSXSetStatus (CPU6502 *cpu)
{
  cpu->Flag.Z = (cpu->X == 0);
  cpu->Flag.N = (cpu->X & 0x80) != 0;
}

/*
   TSX - Transfer Stack Pointer to Index X.
   Copies the value of the Stack Pointer (SP) into the X register,
   then updates the Zero and Negative flags accordingly.
   Consumes 2 CPU cycles.
*/
static inline void
TSX (CPU6502 *cpu)
{
  cpu->X = cpu->SP;
  TSXSetStatus (cpu);
  
  spend_cycles (2);
}

#endif // TSX_H
