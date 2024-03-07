#ifndef JSR_H
#define JSR_H

#include "config.h"
#include "cpu6502.h"


/* 
   This is a header file for the JSR (Jump to Subroutine) and RTS (Return from Subroutine) instructions for MOS Technology 6502.
   JSR is used to jump to a subroutine, saving the return address, and RTS is used to return from that subroutine.
   For more information about the instructions, refer to Instructions.MD
*/ 


/* 
   JSR - Jump to Subroutine:
   This function fetches a two-byte address from memory, saves the return address (PC + 2) to the stack,
   and then sets the program counter (PC) to the specified address.
   It adjusts the cycle count accordingly.
*/ 


void JSR(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
  Word Sub_Addr = FetchWord(Cycles, memory, cpu);
  PushPCToStack(Cycles, memory, cpu);
  cpu->PC = Sub_Addr;
  (*Cycles)--;
}


/* 
   RTS - Return from Subroutine:
   This function retrieves the return address from the stack and sets the program counter (PC) to that address.
   It adjusts the cycle count accordingly.
*/ 


void RTS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
  Word ReturnAddress = PopWordFromStack(Cycles, memory, cpu);
  cpu->PC = ReturnAddress;
  (*Cycles)-=2;
}


#endif // JSR_H