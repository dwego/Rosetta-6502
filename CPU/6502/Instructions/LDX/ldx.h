#ifndef LDX_H
#define LDX_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"


/* 
   This is a header file for the LDX (Load Index Register X) instruction for MOS Technology 6502.
   LDX works by moving a value into the Index Register X (X).
   For more information about the instructions, refer to Instructions.MD
*/ 

/* 
   LDX (Load Index Register X) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Index Register X, (X).
*/   


/* 
   LDX_IM - Load Index Register X with Immediate value.
   This function fetches a byte from memory and loads it into the Index Register X (X).
   It then sets the status flags using LDXSetStatus.
*/ 


void LDX_IM(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte Value = FetchByte(Cycles, memory, cpu);
    cpu->X = Value;
    LDXSetStatus(cpu);
}


/* 
   LDX_ZP - Load Index Register X from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, and loads it into the Index Register X (X). It then sets the status flags.
*/ 


void LDX_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    cpu->X = ReadByte(Cycles, ZeroPageAddr, memory);
    LDXSetStatus(cpu);
}


/* 
   LDX_ZPX - Load Index Register X from Zero Page with X Offset.
   Similar to LDX_ZP, but adds the Y register value to the zero-page address before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/ 


void LDX_ZPY(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    ZeroPageAddr += cpu->Y;
    (*Cycles)--;
    cpu->X = ReadByte(Cycles, ZeroPageAddr, memory);
    LDXSetStatus(cpu);
}


/* 
   LDX_ABS - Load Index Register X from Absolute address.
   This function fetches a two-byte absolute address from memory, reads the value at that address,
   and loads it into the Index Register X (X). It then sets the status flags.
*/ 



void LDX_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    cpu->X = ReadByte(Cycles, Absolute, memory);
    LDXSetStatus(cpu);
}


/* 
   LDX_ABSY - Load Index Register X from Absolute address with Y Offset.
   Similar to LDX_ABS, but adds the Y register value to the absolute address before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/ 


void LDX_ABSY(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    Absolute += cpu->Y;
    cpu->X = ReadByte(Cycles, Absolute, memory);
    LDXSetStatus(cpu);
}


/* 
   This function sets the Flags for the Status register 
   to identify what happened during the LDX instruction.
*/ 


void LDXSetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->X == 0);
    cpu->Flag.N = (cpu->X & 0x80) > 0;
}

#endif // LDX_H