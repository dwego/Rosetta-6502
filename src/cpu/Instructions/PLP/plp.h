#ifndef PLP_H
#define PLP_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the PLP (Pull Processor Status) instruction for
   MOS Technology 6502. PLP pulls the processor status register (P) from the
   stack. For more information about the instructions, refer to Instructions.MD
*/

/*
   PLP uses the implied addressing mode.
   It retrieves a byte from the stack and loads it into the processor status
   register (PS).
*/

/*
   This function clears the Break and Unused flags after loading PS from stack,
   as these bits are always set to 0 when pulled.
*/

static inline void
PLPSetStatus (CPU6502 *cpu)
{
  cpu->Flag.B = 0;
  cpu->Flag.Unused = 0;
}

/*
   PLP - Pull Processor Status from Stack.
   This function pops a byte from the stack and loads it into the processor
   status register (PS), then clears the Break and Unused flags, and spends the
   required CPU cycles.
*/

static inline void
PLP (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte Value = PopByteFromStack (Cycles, bus, memory, cpu);
  cpu->PS = Value;
  PLPSetStatus (cpu);
  spend_cycles (4);
}

#endif // PLP_H
