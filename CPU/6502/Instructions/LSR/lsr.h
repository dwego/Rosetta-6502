#ifndef LSR_H
#define LSR_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/* 
   This is a header file for the LSR (Load Accumulator) instruction for MOS Technology 6502.
   LSR works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   LSR (Load Accumulator) instruction supports various LSRressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the LSR instruction.
*/


void LSRSetStatus(Byte Value, CPU6502 *cpu) {
    cpu->Flag.C = Value & 1;
    cpu->Flag.Z = (cpu->A == 0);
    cpu->Flag.N = (cpu->A & 0x80) > 0;
}


/*
   LSR_IM - Load Accumulator with Immediate value.
   This function fetches a byte from memory and loads it into the Accumulator (A).
   It then sets the status flags using LSRSetStatus.
*/


void LSR_ACC(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte Value = FetchByte(Cycles, memory, cpu);
    cpu->A = Value >> 1;
    LSRSetStatus(Value, cpu);
     spend_cycles(2);
}


/*
   LSR_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page LSRress from memory, reads the
   value at that LSRress, and loads it into the Accumulator (A). It then sets the status flags.
*/


void LSR_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageLSRr = FetchByte(Cycles, memory, cpu);

    Byte Value = ReadByte(Cycles, ZeroPageLSRr, memory);
    cpu->A = Value >> 1;
    LSRSetStatus(Value, cpu);
     spend_cycles(5);
}


/*
   LSR_ZPX - Load Accumulator from Zero Page with X Offset.
   Similar to LSR_ZP, but LSRs the X register value to the zero-page LSRress before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


void LSR_ZPX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageLSRr = FetchByte(Cycles, memory, cpu);
    ZeroPageLSRr += cpu->X;
    (*Cycles)--;

    Byte Value = ReadByte(Cycles, ZeroPageLSRr, memory);
    cpu->A = Value >> 1;
    LSRSetStatus(Value, cpu);
     spend_cycles(6);
}


/*
   LSR_ABS - Load Accumulator from Absolute LSRress.
   This function fetches a two-byte absolute LSRress from memory, reads the value at that LSRress,
   and loads it into the Accumulator (A). It then sets the status flags.
*/


void LSR_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);

    Byte Value = ReadByte(Cycles, Absolute, memory);
    cpu->A = Value >> 1;
    LSRSetStatus(Value, cpu);
     spend_cycles(6);
}


/*
   LSR_ABSX - Load Accumulator from Absolute LSRress with X Offset.
   Similar to LSR_ABS, but LSRs the X register value to the absolute LSRress before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


void LSR_ABSX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    Absolute += cpu->X;

    Byte Value = ReadByte(Cycles, Absolute, memory);
    cpu->A = Value >> 1;
    LSRSetStatus(Value, cpu);
     spend_cycles(6);
}

#endif // LSR_H
