#ifndef BPL_H
#define BPL_H

#include "config.h"
#include "cpu6502.h"


/* 
   This is a header file for the BPL (Jump to Subroutine) and RTS (Return from Subroutine) instructions for MOS Technology 6502.
   BPL is used to jump to a subroutine, saving the return address, and RTS is used to return from that subroutine.
   For more information about the instructions, refer to Instructions.MD
*/


/* 
   BPL - Jump to Subroutine:
   This function fetches a two-byte address from memory, saves the return address (PC + 2) to the stack,
   and then sets the program counter (PC) to the specified address.
   It adjusts the cycle count accordingly.
*/


static inline void BPL(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    if (cpu->Flag.N == 0) {
        Byte relative_offset = FetchByte(Cycles, memory, cpu);
        Word old_pc = cpu->PC;
        cpu->PC += (char) relative_offset;

        (*Cycles)--;
         spend_cycle();
        if ((old_pc & 0xFF00) != (cpu->PC & 0xFF00)) {
            (*Cycles)--;
             spend_cycle();
        }
    }
     spend_cycles(2);
}

#endif // BPL_H
