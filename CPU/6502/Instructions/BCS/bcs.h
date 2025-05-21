#ifndef BCS_H
#define BCS_H

#include "config.h"
#include "cpu6502.h"


/*
   This is a header file for the BCS (Branch if Carry Set) instruction for MOS Technology 6502.
   BCS is used to branch conditionally based on the state of the Carry flag. If the Carry flag is set, BCS will branch to a new location.
   For more information about the instructions, refer to Instructions.MD
*/

/*
   BCS - Branch if Carry Set:
   This function fetches a byte from memory, interprets it as a signed quantity (allowing for backwards branching),
   then checks if the carry flag is set. If it is, it branches by adding the signed quantity to the program counter.
   It adjusts the cycle count accordingly, with an extra cycle consumed if the branch is taken,
   and another cycle consumed if the branch crosses a page boundary.
*/


void BCS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte Relative = FetchByte(Cycles, memory, cpu);
    if(cpu->Flag.C == 0) {
        Word OldPC = cpu->PC;
        // Since the fetched value is signed, we cast it to signed Byte
        // to make sure it's treated as negative if the high bit is set.
        cpu->PC += (SignedByte)Relative;

        // BCC instruction takes an extra cycle if branch succeeds.
        (*Cycles)--;

        // If the branch crosses a page boundary, it takes an additional cycle.
        if ((OldPC & 0xFF00) != (cpu->PC & 0xFF00))  {
            (*Cycles)--;
        }
    }
}

#endif // BCS_H