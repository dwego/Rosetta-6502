#ifndef PLP_H
#define PLP_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

// TODO Arrumar os comentarios

/*
   This is a header file for the PLP (Load Accumulator) instruction for MOS Technology 6502.
   PLP works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   PLP (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the PLP instruction.
*/


void PLPSetStatus(CPU6502 *cpu) {
    cpu->Flag.B = 0;
    cpu->Flag.Unused = 0;
}


/*
   PLP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, and loads it into the Accumulator (A). It then sets the Status flags.
*/


void PLP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Value = PopWordFromStack(Cycles, memory, cpu);
    cpu->PS = Value;
    PLPSetStatus(cpu);
}

#endif // PLP_H