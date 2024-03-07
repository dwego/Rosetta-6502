#ifndef BMI_H
#define BMI_H

#include "config.h"
#include "cpu6502.h"


/* 
   This is a header file for the BMI (Jump to Subroutine) and RTS (Return from Subroutine) instructions for MOS Technology 6502.
   BMI is used to jump to a subroutine, saving the return address, and RTS is used to return from that subroutine.
   For more information about the instructions, refer to Instructions.MD
*/


/* 
   BMI - Jump to Subroutine:
   This function fetches a two-byte address from memory, saves the return address (PC + 2) to the stack,
   and then sets the program counter (PC) to the specified address.
   It adjusts the cycle count accordingly.
*/


void BMI(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    if (cpu->Flag.N != 0) {
        Byte relative_offset = FetchByte(Cycles, memory, cpu);
        Word old_pc = cpu->PC;
        cpu->PC += (char) relative_offset;

        (*Cycles)--;

        if ((old_pc & 0xFF00) != (cpu->PC & 0xFF00)) {
            (*Cycles)--;
        }
    }
}
#endif // BMI_H