#ifndef BCC_H
#define BCC_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the BCC (Branch if Carry Clear) instruction for MOS Technology 6502.
   BCC branches to a new location if the Carry flag is clear.
   For more information about the instructions, refer to Instructions.MD
*/

/*
   BCC - Branch if Carry Clear:
   This function fetches a one-byte signed value from memory,
   checks if the Carry flag is clear, and if so, adjusts the program counter (PC) by the fetched value.
   It adjusts the cycle count according to the rules of the BCC instruction.
*/

void BCC(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte Relative = FetchByte(Cycles, memory, cpu);
    if(cpu->Flag.C == 0) {
        Word OldPC = cpu->PC;
        // Since the fetched value is signed, we cast it to signed Byte
        // to make sure it's treated as negative if the high bit is set.
        cpu->PC += (SignedByte)Relative;

        // BCC instruction takes an extra cycle if branch succeeds.
        (*Cycles)--;
         spend_cycle();
        // If the branch crosses a page boundary, it takes an additional cycle.
        if ((OldPC & 0xFF00) != (cpu->PC & 0xFF00))  {
            (*Cycles)--;
             spend_cycle();
        }
    }
    spend_cycles(2);
}
 
#endif // BCC_H
