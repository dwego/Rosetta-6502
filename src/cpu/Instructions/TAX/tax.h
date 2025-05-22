#ifndef TAX_H
#define TAX_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the TAX (Transfer Accumulator to Index X)
   instruction for MOS Technology 6502. TAX copies the value from the
   Accumulator register (A) to the Index Register X (X). For more information
   about the instructions, refer to Instructions.MD
*/

/*
   TAX affects the processor status flags:
   - Zero flag (Z) is set if the new X value is zero.
   - Negative flag (N) is set if bit 7 of the new X value is set.
*/

/*
   This function sets the Flags for the Status register
   based on the current value of the X register.
*/
static inline void
TAXSetStatus (CPU6502 *cpu)
{
  cpu->Flag.Z = (cpu->X == 0);
  cpu->Flag.N = (cpu->X & 0x80) != 0;
}

/*
   TAX - Transfer Accumulator to Index X.
   Copies the value of the Accumulator into the X register,
   then updates the Zero and Negative flags accordingly.
   Consumes 2 CPU cycles.
*/
static inline void
TAX (Word *Cycles, CPU6502 *cpu)
{
  cpu->X = cpu->A;
  TAXSetStatus (cpu);
  (*Cycles)--;
  spend_cycles (2);
}

#endif // TAX_H
