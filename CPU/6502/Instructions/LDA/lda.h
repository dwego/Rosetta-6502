#ifndef LDA_H
#define LDA_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/* 
   This is a header file for the LDA (Load Accumulator) instruction for MOS Technology 6502.
   LDA works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   LDA (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the LDA instruction.
*/


void LDASetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->A == 0);
    cpu->Flag.N = (cpu->A & 0x80) > 0;
}


/*
   LDA_IM - Load Accumulator with Immediate value.
   This function fetches a byte from memory and loads it into the Accumulator (A).
   It then sets the status flags using LDASetStatus.
*/


void LDA_IM(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte Value = FetchByte(Cycles, memory, cpu);;
    cpu->A = Value;
    LDASetStatus(cpu);
     spend_cycles(2);
}


/*
   LDA_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, and loads it into the Accumulator (A). It then sets the status flags.
*/


void LDA_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    cpu->A = ReadByte(Cycles, ZeroPageAddr, memory);
    LDASetStatus(cpu);
     spend_cycles(3);
}


/*
   LDA_ZPX - Load Accumulator from Zero Page with X Offset.
   Similar to LDA_ZP, but adds the X register value to the zero-page address before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


void LDA_ZPX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    ZeroPageAddr += cpu->X;
    (*Cycles)--;
    cpu->A = ReadByte(Cycles, ZeroPageAddr, memory);
    LDASetStatus(cpu);
   spend_cycles(4);
}


/*
   LDA_ABS - Load Accumulator from Absolute address.
   This function fetches a two-byte absolute address from memory, reads the value at that address,
   and loads it into the Accumulator (A). It then sets the status flags.
*/


void LDA_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    cpu->A = ReadByte(Cycles, Absolute, memory);
    LDASetStatus(cpu);
     spend_cycles(4);
}


/*
   LDA_ABSX - Load Accumulator from Absolute address with X Offset.
   Similar to LDA_ABS, but adds the X register value to the absolute address before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


void LDA_ABSX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    Absolute += cpu->X;

    Word OldPage = Absolute & 0xFF00;
    Absolute += cpu->X;
    Word NewPage = Absolute & 0xFF00;

    if (OldPage != NewPage) {
        (*Cycles)++;
         spend_cycle();  
    }

    cpu->A = ReadByte(Cycles, Absolute, memory);
    LDASetStatus(cpu);
     spend_cycles(4);
}


/*
   LDA_ABSY - Load Accumulator from Absolute address with Y Offset.
   Similar to LDA_ABS, but adds the Y register value to the absolute address before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


void LDA_ABSY(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);

    Word OldPage = Absolute & 0xFF00;
    Absolute += cpu->Y;
    Word NewPage = Absolute & 0xFF00;

    // Add an extra cycle if page is crossed
    if (OldPage != NewPage) {
        (*Cycles)++;
         spend_cycle();
    }

    cpu->A = ReadByte(Cycles, Absolute, memory);
    LDASetStatus(cpu);
     spend_cycles(4);
}

#endif // LDA_H
