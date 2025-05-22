#ifndef RTS_H
#define RTS_H

#include "config.h"
#include "cpu6502.h"


/* 
   RTS - Return from Subroutine:
   This function retrieves the return address from the stack and sets the program counter (PC) to that address.
   It adjusts the cycle count accordingly.
*/ 


void RTS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
  Word ReturnAddress = PopWordFromStack(Cycles, memory, cpu);
  cpu->PC = ReturnAddress;
  (*Cycles)-=2;
  spend_cycles(6);
}


#endif // RTS_H
