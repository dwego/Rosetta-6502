#ifndef INX_H
#define INX_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the INX (Load Accumulator) instruction for MOS Technology 6502.
   INX works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   INX (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the INX instruction.
*/


void INXSetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->X == 0);
    cpu->Flag.N = (cpu->X & 0x80) > 0;
}


/*
   INX - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, INX loads it into the Accumulator (A). It then sets the status flags.
*/


void INX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    cpu->X++;
    (*Cycles)--;
}


#endif // INX_H