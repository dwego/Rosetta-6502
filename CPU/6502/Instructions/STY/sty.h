#ifndef STY_H
#define STY_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

// TODO Arrumar os comentarios


/*
   This is a header file for the STY (Store Index Register X) instruction for MOS Technology 6502.
   STY works by moving the value from the Index Register X (X) to a specific memory address.
   For more information about the instructions, refer to Instructions.MD
*/

/*
   This function sets the Flags for the Status register
   to identify what happened during the STY instruction.
*/


void STYSetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->Y == 0);
    cpu->Flag.N = (cpu->Y & 0x80) > 0;
}


/*
   STY (Store Index Register X) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the destination for the data from the Index Register X (X).
*/


/*
   STY_ZP - Load Index Register X from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, and loads it into the Index Register X (X). It then sets the status flags.
*/


void STY_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    WriteByte(Cycles, cpu->Y, memory, ZeroPageAddr);
    STYSetStatus(cpu);
}


/*
   STY_ZPX - Load Index Register X from Zero Page with X Offset.
   Similar to STY_ZP, but adds the Y register value to the zero-page address before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


void STY_ZPX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    ZeroPageAddr += cpu->X;
    (*Cycles)--;
    WriteByte(Cycles, cpu->Y, memory, ZeroPageAddr);
    STYSetStatus(cpu);
}


/*
   STY_ABS - Load Index Register X from Absolute address.
   This function fetches a two-byte absolute address from memory, reads the value at that address,
   and loads it into the Index Register X (X). It then sets the status flags.
*/



void STY_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    WriteByte(Cycles, cpu->Y, memory, Absolute);
    STYSetStatus(cpu);
}

#endif // STY_H
