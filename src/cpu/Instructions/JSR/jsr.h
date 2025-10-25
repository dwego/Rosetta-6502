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
   This function fetches a two-byte address from memory, which is the target
   subroutine address. It pushes the return address (PC - 1) onto the stack,
   which corresponds to the address of the last byte of the JSR instruction (so
   that RTS returns correctly to the instruction following the JSR). Then it
   sets the program counter (PC) to the subroutine address. The cycle count is
   decremented accordingly.
*/

static inline void
JSR (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Word SubAddr = FetchWord (Cycles, bus, memory, cpu);

  // Push the return address (PC - 1) onto the stack.
  // This is because RTS will pull the return address and add 1 before resuming
  // execution.
  Word ReturnAddr = cpu->PC - 1;
  PushWordToStack (Cycles, bus, memory, ReturnAddr, cpu);

  // Set the program counter to the target subroutine address.
  cpu->PC = SubAddr;

  spend_cycles (6);
}

#endif // JSR_H
