#ifndef CPX_H
#define CPX_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/* 
   This is a header file for the CPX (Load Accumulator) instruction for MOS Technology 6502.
   CPX works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   CPX (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/

/*
   This function sets the Flags for the Status register
   to identify what happened during the CPX instruction.
*/
void
CPXSetStatus(Byte Result, CPU6502 *cpu)
{
    cpu->Flag.Z = (Result == cpu->X);
    cpu->Flag.C = (cpu->X >= Result);
    cpu->Flag.N = (Result & 0x80) > 0;
}


/*
   CPX_IM - Load Accumulator with Immediate value.
   This function fetches a byte from memory and loads it into the Accumulator (A).
   It then sets the status flags using CPXSetStatus.
*/
void
CPX_IM(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    Byte Value = FetchByte(Cycles, memory, cpu);
    Byte Result = cpu->X - Value;
    CPXSetStatus(Result, cpu);
}

/*
   CPX_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, and loads it into the Accumulator (A). It then sets the status flags.
*/
void
CPX_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    Byte Data = ReadByte(Cycles, ZeroPageAddr, memory);
    Byte Result = cpu->X - Data;
    CPXSetStatus(Result, cpu);
}

/*
   CPX_ABS - Load Accumulator from Absolute address.
   This function fetches a two-byte absolute address from memory, reads the value at that address,
   and loads it into the Accumulator (A). It then sets the status flags.
*/
void
CPX_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    Word Absolute = FetchWord(Cycles, memory, cpu);
    Byte Data = ReadByte(Cycles, Absolute, memory);
    Byte Result = cpu->X - Data;
    CPXSetStatus(Result, cpu);
}

#endif // CPX_H