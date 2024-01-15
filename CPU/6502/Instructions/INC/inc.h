#ifndef INC_H
#define INC_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the INC (Load Accumulator) instruction for MOS Technology 6502.
   INC works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   INC (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the INC instruction.
*/


void INCSetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->A == 0);
    cpu->Flag.N = (cpu->A & 0x80) > 0;
}


/*
   INC_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, INC loads it into the Accumulator (A). It then sets the status flags.
*/



void INC_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);

    Byte Value = ReadByte(Cycles, ZeroPageAddr, memory);
    Byte IncrementValue = Value + 1;

    WriteByte(Cycles, IncrementValue, memory, ZeroPageAddr);
    INCSetStatus(cpu);
}


/*
   INC - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, INC loads it into the Accumulator (A). It then sets the status flags.
*/


void INC_ZPX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    ZeroPageAddr += cpu->X;

    Byte Value = ReadByte(Cycles, ZeroPageAddr, memory);
    Byte IncrementValue = Value + 1;

    WriteByte(Cycles, IncrementValue, memory, ZeroPageAddr);
    INCSetStatus(cpu);
}


/*
   INC - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, INC loads it into the Accumulator (A). It then sets the status flags.
*/


void INC_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);

    Byte Value = ReadByte(Cycles, Absolute, memory);
    Byte IncrementValue = Value + 1;

    WriteByte(Cycles, IncrementValue, memory, Absolute);
    INCSetStatus(cpu);
}


#endif // INC_H