#ifndef EOR_H
#define EOR_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/* 
   This is a header file for the EOR (Load Accumulator) instruction for MOS Technology 6502.
   EOR works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   EOR (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the EOR instruction.
*/


void EORSetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->A == 0);
    cpu->Flag.N = (cpu->A & 0x80) > 0;
}


/*
   EOR_IM - Load Accumulator with Immediate value.
   This function fetches a byte from memoryEOR loads it into the Accumulator (A).
   It then sets the status flags usingEORSetStatus.
*/


void EOR_IM(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte Value = FetchByte(Cycles, memory, cpu);
    cpu->A = Value ^ cpu->A;
    EORSetStatus(cpu);
}


/*
   EOR_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address,EOR loads it into the Accumulator (A). It then sets the status flags.
*/


void EOR_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    cpu->A = ReadByte(Cycles, ZeroPageAddr, memory) ^ cpu->A;
    EORSetStatus(cpu);
}


/*
   EOR_ZPX - Load Accumulator from Zero Page with X Offset.
   Similar to EOR_ZP, but adds the X register value to the zero-page address before reading
   the value from memory. It adjusts the cycle count accordingly EOR sets the status flags.
*/


void EOR_ZPX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    ZeroPageAddr += cpu->X;
    (*Cycles)--;
    cpu->A = ReadByte(Cycles, ZeroPageAddr, memory) ^ cpu->A;
    EORSetStatus(cpu);
}


/*
   EOR_ABS - Load Accumulator from Absolute address.
   This function fetches a two-byte absolute address from memory, reads the value at that address,
   EOR loads it into the Accumulator (A). It then sets the status flags.
*/


void EOR_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    cpu->A = ReadByte(Cycles, Absolute, memory) ^ cpu->A;
    EORSetStatus(cpu);
}


/*
   EOR_ABSX - Load Accumulator from Absolute address with X Offset.
   Similar to EOR_ABS, but adds the X register value to the absolute address before reading
   the value from memory. It adjusts the cycle count accordinglyEOR sets the status flags.
*/


void EOR_ABSX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);

    Word OldPage = Absolute & 0xFF00;
    Absolute += cpu->X;
    Word NewPage = Absolute & 0xFF00;

    if (OldPage != NewPage) {
        (*Cycles)++;
    }

    cpu->A = ReadByte(Cycles, Absolute, memory) ^ cpu->A;
    EORSetStatus(cpu);
}


/*
   EOR_ABSY - Load Accumulator from Absolute address with Y Offset.
   Similar to EOR_ABS, but adds the Y register value to the absolute address before reading
   the value from memory. It adjusts the cycle count accordinglyEOR sets the status flags.
*/


void EOR_ABSY(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);

    Word OldPage = Absolute & 0xFF00;
    Absolute += cpu->Y;
    Word NewPage = Absolute & 0xFF00;

    if (OldPage != NewPage) {
        (*Cycles)++;
    }

    cpu->A = ReadByte(Cycles, Absolute, memory) ^ cpu->A;
    EORSetStatus(cpu);
}

#endif // EOR_H
