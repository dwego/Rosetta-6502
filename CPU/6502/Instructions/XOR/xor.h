#ifndef XOR_H
#define XOR_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/* 
   This is a header file for the XOR (Load Accumulator) instruction for MOS Technology 6502.
   XOR works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   XOR (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the OR instruction.
*/


void XORSetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->A == 0);
    cpu->Flag.N = (cpu->A & 0x80) > 0;
}


/*
   XOR_IM - Load Accumulator with Immediate value.
   This function fetches a byte from memory OR loads it into the Accumulator (A).
   It then sets the status flags using ORSetStatus.
*/


void XOR_IM(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte Value = FetchByte(Cycles, memory, cpu);
    cpu->A = Value ^ cpu->A;
    XORSetStatus(cpu);
}


/*
   XOR_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, OR loads it into the Accumulator (A). It then sets the status flags.
*/


void XOR_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    cpu->A = ReadByte(Cycles, ZeroPageAddr, memory) ^ cpu->A;
    XORSetStatus(cpu);
}


/*
   XOR_ZPX - Load Accumulator from Zero Page with X Offset.
   Similar to OR_ZP, but adds the X register value to the zero-page address before reading
   the value from memory. It adjusts the cycle count accordingly OR sets the status flags.
*/


void XOR_ZPX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    ZeroPageAddr += cpu->X;
    (*Cycles)--;
    cpu->A = ReadByte(Cycles, ZeroPageAddr, memory) ^ cpu->A;
    XORSetStatus(cpu);
}


/*
   XOR_ABS - Load Accumulator from Absolute address.
   This function fetches a two-byte absolute address from memory, reads the value at that address,
   OR loads it into the Accumulator (A). It then sets the status flags.
*/


void XOR_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    cpu->A = ReadByte(Cycles, Absolute, memory) ^ cpu->A;
    XORSetStatus(cpu);
}


/*
   XOR_ABSX - Load Accumulator from Absolute address with X Offset.
   Similar to OR_ABS, but adds the X register value to the absolute address before reading
   the value from memory. It adjusts the cycle count accordingly OR sets the status flags.
*/


void XOR_ABSX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);

    Word OldPage = Absolute & 0xFF00;
    Absolute += cpu->X;
    Word NewPage = Absolute & 0xFF00;

    if (OldPage != NewPage) {
        (*Cycles)++;
    }

    cpu->A = ReadByte(Cycles, Absolute, memory) ^ cpu->A;
    XORSetStatus(cpu);
}


/*
   XOR_ABSY - Load Accumulator from Absolute address with Y Offset.
   Similar to OR_ABS, but adds the Y register value to the absolute address before reading
   the value from memory. It adjusts the cycle count accordingly OR sets the status flags.
*/


void XOR_ABSY(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);

    Word OldPage = Absolute & 0xFF00;
    Absolute += cpu->Y;
    Word NewPage = Absolute & 0xFF00;

    if (OldPage != NewPage) {
        (*Cycles)++;
    }

    cpu->A = ReadByte(Cycles, Absolute, memory) ^ cpu->A;
    XORSetStatus(cpu);
}

#endif // XOR_H
