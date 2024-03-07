#ifndef CLC_H
#define CLC_H

#include "config.h"
#include "cpu6502.h"


/*
   This is a header file for the CLC (Jump to Subroutine) and RTS (Return from Subroutine) instructions for MOS Technology 6502.
   CLC is used to jump to a subroutine, saving the return address, and RTS is used to return from that subroutine.
   For more information about the instructions, refer to Instructions.MD
*/


/*
   CLC - Jump to Subroutine:
   This function fetches a two-byte address from memory, saves the return address (PC + 2) to the stack,
   and then sets the program counter (PC) to the specified address.
   It adjusts the cycle count accordingly.
*/

void
CLCSetStatus(CPU6502 *cpu)
{
    cpu->Flag.C = 0;
}

void
CLC(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    CLCSetStatus(cpu);
    (*Cycles)--;
}

#endif // CLC_H