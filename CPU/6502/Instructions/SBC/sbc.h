#ifndef SBC_H
#define SBC_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/* 
   This is a header file for the SBC (Load Accumulator) instruction for MOS Technology 6502.
   SBC works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   SBC (Load Accumulator) instruction supports various SBCressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the SBC instruction.
*/


void SBCSetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->A == 0);
    cpu->Flag.N = (cpu->A & 0x80) > 0;
}


/*
   SBC_IM - Load Accumulator with Immediate value.
   This function fetches a byte from memory and loads it into the Accumulator (A).
   It then sets the status flags using SBCSetStatus.
*/


void SBC_IM(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte Value = FetchByte(Cycles, memory, cpu);
    cpu->A -= Value - cpu->Flag.C;
    SBCSetStatus(cpu);
}


/*
   SBC_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page SBCress from memory, reads the
   value at that SBCress, and loads it into the Accumulator (A). It then sets the status flags.
*/


void SBC_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageSBCr = FetchByte(Cycles, memory, cpu);

    Byte Value = ReadByte(Cycles, ZeroPageSBCr, memory);
    cpu->A -= Value - cpu->Flag.C;
    SBCSetStatus(cpu);
}


/*
   SBC_ZPX - Load Accumulator from Zero Page with X Offset.
   Similar to SBC_ZP, but SBCs the X register value to the zero-page SBCress before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


void SBC_ZPX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageSBCr = FetchByte(Cycles, memory, cpu);
    ZeroPageSBCr += cpu->X;
    (*Cycles)--;

    Byte Value = ReadByte(Cycles, ZeroPageSBCr, memory);
    cpu->A -= Value - cpu->Flag.C;
    SBCSetStatus(cpu);
}


/*
   SBC_ABS - Load Accumulator from Absolute SBCress.
   This function fetches a two-byte absolute SBCress from memory, reads the value at that SBCress,
   and loads it into the Accumulator (A). It then sets the status flags.
*/


void SBC_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);

    Byte Value = ReadByte(Cycles, Absolute, memory);
    cpu->A -= Value - cpu->Flag.C;
    SBCSetStatus(cpu);
}


/*
   SBC_ABSX - Load Accumulator from Absolute SBCress with X Offset.
   Similar to SBC_ABS, but SBCs the X register value to the absolute SBCress before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


void SBC_ABSX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    Absolute += cpu->X;

    Byte Value = ReadByte(Cycles, Absolute, memory);
    cpu->A -= Value - cpu->Flag.C;
    SBCSetStatus(cpu);
}


/*
   SBC_ABSY - Load Accumulator from Absolute SBCress with Y Offset.
   Similar to SBC_ABS, but SBCs the Y register value to the absolute SBCress before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


void SBC_ABSY(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    Absolute += cpu->Y;

    Byte Value = ReadByte(Cycles, Absolute, memory);
    cpu->A -= Value - cpu->Flag.C;
    SBCSetStatus(cpu);
}

#endif // SBC_H