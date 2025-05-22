#ifndef CLI_H
#define CLI_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the CLI (Clear Interrupt Disable) instruction for
   MOS Technology 6502. CLI clears the Interrupt Disable flag in the processor
   status register (i.e., enables maskable interrupts). For more information
   about the instructions, refer to Instructions.MD
*/

/*
   CLI - Clear Interrupt Disable:
   This function clears the Interrupt Disable flag (I) in the CPU status
   register. It adjusts the cycle count accordingly.
*/

static inline void
CLISetStatus (CPU6502 *cpu)
{
  cpu->Flag.I = 0;
}

static inline void
CLI (Word *Cycles, CPU6502 *cpu)
{
  CLISetStatus (cpu);
  (*Cycles)--;
  spend_cycles (2);
}

#endif // CLI_H
