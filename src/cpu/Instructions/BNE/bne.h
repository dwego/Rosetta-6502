#ifndef BNE_H
#define BNE_H

#include "config.h"
#include "cpu6502.h"


/* 
   This is a header file for the BNE (Jump to Subroutine) and RTS (Return from Subroutine) instructions for MOS Technology 6502.
   BNE is used to jump to a subroutine, saving the return address, and RTS is used to return from that subroutine.
   For more information about the instructions, refer to Instructions.MD
*/


/* 
   BNE - Jump to Subroutine:
   This function fetches a two-byte address from memory, saves the return address (PC + 2) to the stack,
   and then sets the program counter (PC) to the specified address.
   It adjusts the cycle count accordingly.
*/


static inline void BNE(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    if (cpu->Flag.Z == 0) {
        Byte Sub_Addr = FetchByte(Cycles, memory, cpu);
        Word old_pc = cpu->PC;
        cpu->PC += Sub_Addr;

        (*Cycles)--;
         spend_cycle();
        if ((old_pc & 0xFF00) != (cpu->PC & 0xFF00)) {
            (*Cycles)--;
             spend_cycle();
        }
    }
     spend_cycles(2);
}

#endif // BNE_H
