#ifndef TXA_H
#define TXA_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the TXA (Transfer X to Accumulator) instruction
   for MOS Technology 6502.
   TXA works by transferring the value from the Index Register X (X) into the
   Accumulator (A). For more information about the instructions, refer to
   Instructions.MD
*/

/*
   This function sets the Flags for the Status register
   based on the current value of the Accumulator (A) after the transfer.
*/
static inline void
TXASetStatus (CPU6502 *cpu)
{
  cpu->Flag.Z = (cpu->A == 0);
  cpu->Flag.N = (cpu->A & 0x80) != 0;
}

/*
   TXA - Transfer X to Accumulator.
   Copies the value from the X register into the Accumulator (A),
   then updates the Zero and Negative flags accordingly.
   Consumes 2 CPU cycles.
*/
static inline void
TXA (Word *Cycles, CPU6502 *cpu)
{
  cpu->A = cpu->X;
  TXASetStatus (cpu);
  (*Cycles)--;
  spend_cycles (2);
}

#endif // TXA_H
