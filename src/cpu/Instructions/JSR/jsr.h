#ifndef JSR_H
#define JSR_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the JSR (Jump to Subroutine) and RTS (Return from
   Subroutine) instructions for MOS Technology 6502. JSR is used to jump to a
   subroutine, saving the return address, and RTS is used to return from that
   subroutine. For more information about the instructions, refer to
   Instructions.MD
*/

/*
   JSR - Jump to Subroutine:
   This function fetches a two-byte address from memory, saves the return
   address (PC + 2) to the stack, and then sets the program counter (PC) to the
   specified address. It adjusts the cycle count accordingly.
*/

static inline void
JSR (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Word SubAddr = FetchWord (Cycles, memory, cpu);
  Word ReturnAddr = cpu->PC - 1;
  PushWordToStack (Cycles, memory, ReturnAddr, cpu);
  cpu->PC = SubAddr;
  spend_cycles (6);
}

#endif // JSR_H
