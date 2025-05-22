#ifndef TAX_H
#define TAX_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the TAX (Load Accumulator) instruction for MOS Technology 6502.
   TAX works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   TAX (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the TAX instruction.
*/


void TAXSetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->A == 0);
    cpu->Flag.N = (cpu->A & 0x80) > 0;
}


/*
   TAX - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, TAX loads it into the Accumulator (A). It then sets the status flags.
*/


void TAX(Word *Cycles, CPU6502 *cpu) {
    cpu->X = cpu->A;
    TAXSetStatus(cpu);
    (*Cycles)--;
   spend_cycles(2);
}


#endif // TAX_H
