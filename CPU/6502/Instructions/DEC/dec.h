#ifndef DEC_H
#define DEC_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the DEC (Load Accumulator) instruction for MOS Technology 6502.
   DEC works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   DEC (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the DEC instruction.
*/


void DECSetStatus(Byte Value, CPU6502 *cpu) {
    cpu->Flag.Z = (Value == 0);
    cpu->Flag.N = (Value & 0x80) > 0;
}


/*
   DEC_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, DEC loads it into the Accumulator (A). It then sets the status flags.
*/


void DEC_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);

    Byte Value = ReadByte(Cycles, ZeroPageAddr, memory);
    Byte DecrementValue = Value - 1;
    (*Cycles)--;

    WriteByte(Cycles, DecrementValue, memory, ZeroPageAddr);
    DECSetStatus(DecrementValue, cpu);
}


/*
   DEC - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, DEC loads it into the Accumulator (A). It then sets the status flags.
*/


void DEC_ZPX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    ZeroPageAddr += cpu->X;
    (*Cycles)--;

    Byte Value = ReadByte(Cycles, ZeroPageAddr, memory);
    Byte DecrementValue = Value - 1;
    (*Cycles)--;

    WriteByte(Cycles, DecrementValue, memory, ZeroPageAddr);
    DECSetStatus(DecrementValue, cpu);
}


/*
   DEC - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, DEC loads it into the Accumulator (A). It then sets the status flags.
*/


void DEC_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);

    Byte Value = ReadByte(Cycles, Absolute, memory);
    Byte DecrementValue = Value - 1;
    (*Cycles)--;

    WriteByte(Cycles, DecrementValue, memory, Absolute);
    DECSetStatus(DecrementValue, cpu);
}

void DEC_ABSX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    Absolute += cpu->X;
    (*Cycles)--;

    Byte Value = ReadByte(Cycles, Absolute, memory);
    Byte DecrementValue = Value - 1;
    (*Cycles)--;

    WriteByte(Cycles, DecrementValue, memory, Absolute);
    DECSetStatus(DecrementValue, cpu);
}


#endif // DEC_H