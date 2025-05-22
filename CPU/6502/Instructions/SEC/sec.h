#ifndef SEC_H
#define SEC_H

#include "config.h"
#include "cpu6502.h"


/*
   This is a header file for the BVS (Jump to Subroutine) and RTS (Return from Subroutine) instructions for MOS Technology 6502.
   BVS is used to jump to a subroutine, saving the return address, and RTS is used to return from that subroutine.
   For more information about the instructions, refer to Instructions.MD
*/


/*
   BVS - Jump to Subroutine:
   This function fetches a two-byte address from memory, saves the return address (PC + 2) to the stack,
   and then sets the program counter (PC) to the specified address.
   It adjusts the cycle count accordingly.
*/


void SEC(Word *Cycles, CPU6502 *cpu) {
    cpu->Flag.C = 1;
    (*Cycles)--;
   spend_cycles(2);
}

#endif // SEC_H
