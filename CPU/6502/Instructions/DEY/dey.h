#ifndef DEY_H
#define DEY_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the DEY (Load Accumulator) instruction for MOS Technology 6502.
   DEY works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   DEY (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the DEY instruction.
*/


void DEYSetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->Y == 0);
    cpu->Flag.N = (cpu->Y & 0x80) > 0;
}


/*
   DEY - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, DEY loads it into the Accumulator (A). It then sets the status flags.
*/


void DEY(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    cpu->Y--;
    (*Cycles)--;
}


#endif // DEY_H