#ifndef PHP_H
#define PHP_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the PHP (Push Processor Status) instruction for
   MOS Technology 6502. PHP pushes a copy of the processor status register onto
   the stack. For more information about the instructions, refer to
   Instructions.MD
*/

/*
   PHP (Push Processor Status) instruction uses the implied addressing mode.
   The processor status flags B (Break) and Unused are set before pushing the
   status register.
*/

/*
   This function sets the Flags for the Status register
   to the required state when executing PHP instruction.
*/

static inline void
PHPSetStatus (CPU6502 *cpu)
{
  cpu->Flag.B = 1;
  cpu->Flag.Unused = 1;
}

/*
   PHP - Push Processor Status.
   This function sets the necessary flags and pushes the status register (PS)
   onto the stack, then spends the required CPU cycles.
*/

static inline void
PHP (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  PHPSetStatus (cpu);
  PushByteToStack (bus, memory, cpu->PS, cpu);
  spend_cycles (3);
}

#endif // PHP_H
