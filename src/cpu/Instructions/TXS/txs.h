#ifndef TXS_H
#define TXS_H

#include "config.h"
#include "cpu6502.h"

// TODO Arrumar os comentarios

/*
   This is a header file for the TXS (Load Accumulator) instruction for MOS Technology 6502.
   TXS works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   TXS (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the TXS instruction.
*/


static inline void TXSSetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->X == 0);
    cpu->Flag.N = (cpu->X & 0x80) > 0;
}


/*
   TXS_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, and loads it into the Accumulator (A). It then sets the TXStus flags.
*/


static inline void TXS(Word *Cycles, CPU6502 *cpu) {
    cpu->X = cpu->SP;
    TXSSetStatus(cpu);
    (*Cycles)--;
     spend_cycles(2);
}

#endif // TXS_H
