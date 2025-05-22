#ifndef PHA_H
#define PHA_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

// TODO Arrumar os comentarios

/*
   This is a header file for the PHA (Load Accumulator) instruction for MOS Technology 6502.
   PHA works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   PHA (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the PHA instruction.
*/


static inline void PHASetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->X == 0);
    cpu->Flag.N = (cpu->X & 0x80) > 0;
}


/*
   PHA_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, and loads it into the Accumulator (A). It then sets the PHAtus flags.
*/


static inline void PHA(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    PushByteToStack(Cycles, memory, cpu->A, cpu);
    PHASetStatus(cpu);
    spend_cycles(3);
}

#endif // PHA_H
