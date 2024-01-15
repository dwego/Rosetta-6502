#ifndef PLA_H
#define PLA_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

// TODO Arrumar os comentarios

/*
   This is a header file for the PLA (Load Accumulator) instruction for MOS Technology 6502.
   PLA works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   PLA (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the PLA instruction.
*/


void PLASetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->X == 0);
    cpu->Flag.N = (cpu->X & 0x80) > 0;
}


/*
   PLA - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, and loads it into the Accumulator (A). It then sets the Status flags.
*/


void PLA(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Value = PopWordFromStack(Cycles, memory, cpu);
    cpu->A = Value;
    PLASetStatus(cpu);
}

#endif // PLA_H