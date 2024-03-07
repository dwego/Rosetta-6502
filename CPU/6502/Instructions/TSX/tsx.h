#ifndef TSX_H
#define TSX_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

// TODO Arrumar os comentarios

/*
   This is a header file for the TSX (Load Accumulator) instruction for MOS Technology 6502.
   TSX works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   TSX (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the TSX instruction.
*/


void TSXSetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->X == 0);
    cpu->Flag.N = (cpu->X & 0x80) > 0;
}


/*
   TSX_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, and loads it into the Accumulator (A). It then sets the TSXtus flags.
*/


void TSX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    cpu->SP = cpu->X;
    TSXSetStatus(cpu);
}

#endif // TSX_H