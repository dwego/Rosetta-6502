#ifndef PLA_H
#define PLA_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the PLA (Pull Accumulator) instruction for MOS
   Technology 6502. PLA pulls a byte from the stack and loads it into the
   Accumulator register (A). For more information about the instructions, refer
   to Instructions.MD
*/

/*
   PLA uses the implied addressing mode.
   It retrieves a byte from the stack and loads it into the Accumulator (A).
*/

/*
   This function sets the Flags for the Status register
   to identify what happened during the PLA instruction.
*/

static inline void
PLASetStatus (CPU6502 *cpu)
{
  cpu->Flag.Z = (cpu->A == 0);
  cpu->Flag.N = (cpu->A & 0x80) > 0;
}

/*
   PLA - Pull Accumulator from Stack.
   This function pops a byte from the stack, loads it into the Accumulator (A),
   sets the status flags accordingly, and spends the required CPU cycles.
*/

static inline void
PLA (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte Value = PopByteFromStack (Cycles, memory,
                                 cpu); // Use a PopByteFromStack if available
  cpu->A = Value;
  PLASetStatus (cpu);
  spend_cycles (4);
}

#endif // PLA_H
