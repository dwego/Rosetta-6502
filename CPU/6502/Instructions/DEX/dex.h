#ifndef DEX_H
#define DEX_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the DEX (Load Accumulator) instruction for MOS Technology 6502.
   DEX works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   DEX (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the DEX instruction.
*/


void DEXSetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->X == 0);
    cpu->Flag.N = (cpu->X & 0x80) > 0;
}


/*
   DEX - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, DEX loads it into the Accumulator (A). It then sets the status flags.
*/


void DEX(Word *Cycles, CPU6502 *cpu) {
    cpu->X--;
    (*Cycles)--;
    spend_cycles(2);
}


#endif // DEX_H
