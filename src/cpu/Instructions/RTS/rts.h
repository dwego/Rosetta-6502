#ifndef RTS_H
#define RTS_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   RTS - Return from Subroutine:
   Pulls the return address (low byte, then high byte) from the stack,
   increments it by 1 (because JSR pushes PC-1),
   and sets the program counter (PC) to this address.
   Consumes 6 CPU cycles.
*/

static inline void
RTS (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word returnAddress = PopWordFromStack (Cycles, bus, memory, cpu);
  cpu->PC = returnAddress + 1;
  (*Cycles) -= 2;
  spend_cycles (6);
}

#endif // RTS_H
