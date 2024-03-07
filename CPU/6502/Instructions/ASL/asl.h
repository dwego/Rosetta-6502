#ifndef ASL_H
#define ASL_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/* 
   This is a header file for the ASL (Load Accumulator) instruction for MOS Technology 6502.
   ASL works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   ASL (Load Accumulator) instruction supports various ASLressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the ASL instruction.
*/


void ASLSetStatus(Byte Value, CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->A == 0);
    cpu->Flag.C = (Value & 0x80) ? 1 : 0;
    cpu->Flag.N = (cpu->A & 0x80) > 0;
}


/*
   ASL_IM - Load Accumulator with Immediate value.
   This function fetches a byte from memory and loads it into the Accumulator (A).
   It then sets the status flags using ASLSetStatus.
*/


void ASL_ACC(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte Value = FetchByte(Cycles, memory, cpu);
    cpu->A = Value << 1;
    ASLSetStatus(Value, cpu);
}


/*
   ASL_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page ASLress from memory, reads the
   value at that ASLress, and loads it into the Accumulator (A). It then sets the status flags.
*/


void ASL_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageASLr = FetchByte(Cycles, memory, cpu);

    Byte Value = ReadByte(Cycles, ZeroPageASLr, memory);
    cpu->A = Value << 1;
    (*Cycles)=-2;
    ASLSetStatus(Value, cpu);
}


/*
   ASL_ZPX - Load Accumulator from Zero Page with X Offset.
   Similar to ASL_ZP, but ASLs the X register value to the zero-page ASLress before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


void ASL_ZPX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageASLr = FetchByte(Cycles, memory, cpu);
    ZeroPageASLr += cpu->X;
    (*Cycles)--;

    Byte Value = ReadByte(Cycles, ZeroPageASLr, memory);
    cpu->A = Value << 1;
    (*Cycles)=-2;
    ASLSetStatus(Value, cpu);
}


/*
   ASL_ABS - Load Accumulator from Absolute ASLress.
   This function fetches a two-byte absolute ASLress from memory, reads the value at that ASLress,
   and loads it into the Accumulator (A). It then sets the status flags.
*/


void ASL_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);

    Byte Value = ReadByte(Cycles, Absolute, memory);
    cpu->A = Value << 1;
    (*Cycles)=-2;
    ASLSetStatus(Value, cpu);
}


/*
   ASL_ABSX - Load Accumulator from Absolute ASLress with X Offset.
   Similar to ASL_ABS, but ASLs the X register value to the absolute ASLress before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


void ASL_ABSX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    Absolute += cpu->X;

    Byte Value = ReadByte(Cycles, Absolute, memory);
    cpu->A = Value << 1;
    (*Cycles)=-3;
    ASLSetStatus(Value, cpu);
}

#endif // ASL_H