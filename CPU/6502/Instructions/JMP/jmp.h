#ifndef JMP_H
#define JMP_H

#include "config.h"
#include "cpu6502.h"


/* 
   This is a header file for the JMP (Jump to Subroutine) and RTS (Return from Subroutine) instructions for MOS Technology 6502.
   JMP is used to jump to a subroutine, saving the return address, and RTS is used to return from that subroutine.
   For more information about the instructions, refer to Instructions.MD
*/


/* 
   JMP - Jump to Subroutine:
   This function fetches a two-byte address from memory, saves the return address (PC + 2) to the stack,
   and then sets the program counter (PC) to the specified address.
   It adjusts the cycle count accordingly.
*/


void JMP_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Sub_Addr = FetchWord(Cycles, memory, cpu);
    cpu->PC = Sub_Addr;
    (*Cycles)--;
}

void JMP_IND(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Sub_Addr = FetchWord(Cycles, memory, cpu);
    cpu->PC = ReadByte(Cycles, Sub_Addr, memory);
    (*Cycles)--;
}

#endif // JMP_H