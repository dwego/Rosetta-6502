#ifndef BIT_H
#define BIT_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the BIT (Load Accumulator) instruction for MOS Technology 6502.
   BIT works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   BIT (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the BIT instruction.
*/


static inline void BITSetStatus(Byte Value, CPU6502 *cpu) {
    cpu->Flag.N = get_bit(Value, 0);
    cpu->Flag.V= get_bit(Value, 1);
    cpu->Flag.Z = (cpu->A & Value) == 0;
}


/*
   BIT_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, BIT loads it into the Accumulator (A). It then sets the status flags.
*/


static inline void BIT_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    Byte Value = ReadByte(Cycles, ZeroPageAddr, memory);
    BITSetStatus(Value, cpu);
     spend_cycles(3);
}

/*
   BIT_ABS - Load Accumulator from Absolute address.
   This function fetches a two-byte absolute address from memory, reads the value at that address,
   BIT loads it into the Accumulator (A). It then sets the status flags.
*/


static inline void BIT_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    Byte Value = ReadByte(Cycles, Absolute, memory);
    BITSetStatus(Value, cpu);
   spend_cycles(4);
}


#endif // BIT_H
