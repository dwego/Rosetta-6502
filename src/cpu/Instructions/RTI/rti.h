#ifndef RTI_H
#define RTI_H

#include "bus.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   RTI - Return from Interrupt
   Restores the processor status and program counter from the stack.
   Used to return from BRK, IRQ, or NMI interrupts.
*/
static inline void
RTI (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  cpu->PS = PopByteFromStack (Cycles, bus, memory, cpu);
  cpu->PC = PopWordFromStack (Cycles, bus, memory, cpu);

  spend_cycles (6);
}

#endif // RTI_H
