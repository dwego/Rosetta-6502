#ifndef PHP_H
#define PHP_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

// TODO Arrumar os comentarios

/*
   This is a header file for the PHP (Load Accumulator) instruction for MOS Technology 6502.
   PHP works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   PHP (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the PHP instruction.
*/


void PHPSetStatus(CPU6502 *cpu) {
    cpu->Flag.B = 1;
    cpu->Flag.Unused = 1;
}


/*
   PHP_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, and loads it into the Accumulator (A). It then sets the PHPtus flags.
*/


void PHP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    PHPSetStatus(cpu);
    PushByteToStack(Cycles, memory, cpu->PS, cpu);
     spend_cycles(3);
}

#endif // PHP_H
