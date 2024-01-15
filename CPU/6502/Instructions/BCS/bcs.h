#ifndef BCS_H
#define BCS_H

#include "config.h"
#include "cpu6502.h"


/* 
   This is a header file for the BCS (Jump to Subroutine) and RTS (Return from Subroutine) instructions for MOS Technology 6502.
   BCS is used to jump to a subroutine, saving the return address, and RTS is used to return from that subroutine.
   For more information about the instructions, refer to Instructions.MD
*/


/* 
   BCS - Jump to Subroutine:
   This function fetches a two-byte address from memory, saves the return address (PC + 2) to the stack,
   and then sets the program counter (PC) to the specified address.
   It adjusts the cycle count accordingly.
*/


void BCS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    if (cpu->A != 0) {
        Word Sub_Addr = FetchByte(Cycles, memory, cpu);
        cpu->PC = Sub_Addr;
        (*Cycles)--;
    }
}

#endif // BCS_H