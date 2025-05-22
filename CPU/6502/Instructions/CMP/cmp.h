#ifndef CMP_H
#define CMP_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/* 
   This is a header file for the CMP (Load Accumulator) instruction for MOS Technology 6502.
   CMP works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   CMP (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/

/*
   This function sets the Flags for the Status register
   to identify what happened during the CMP instruction.
*/


static inline void
CMPSetStatus(Byte Result, CPU6502 *cpu)
{
    cpu->Flag.Z = (Result == cpu->A);
    cpu->Flag.C = (cpu->A >= Result);
    cpu->Flag.N = (Result & 0x80) > 0;
}

/*
   CMP_IM - Load Accumulator with Immediate value.
   This function fetches a byte from memory and loads it into the Accumulator (A).
   It then sets the status flags using CMPSetStatus.
*/
static inline void
CMP_IM(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    Byte Value = FetchByte(Cycles, memory, cpu);
    Byte Result = cpu->A - Value;
    CMPSetStatus(Result, cpu);
      spend_cycles(2);
}

/*
   CMP_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, and loads it into the Accumulator (A). It then sets the status flags.
*/
static inline void
CMP_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    Byte Data = ReadByte(Cycles, ZeroPageAddr, memory);
    Byte Result = cpu->A - Data;
    CMPSetStatus(Result, cpu);
    spend_cycles(3);
}

/*
   CMP_ZPX - Load Accumulator from Zero Page with X Offset.
   Similar to CMP_ZP, but adds the X register value to the zero-page address before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/
static inline void
CMP_ZPX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    ZeroPageAddr += cpu->X;
    (*Cycles)--;
    Byte Data = ReadByte(Cycles, ZeroPageAddr, memory);
    Byte Result = cpu->A - Data;
    CMPSetStatus(Result, cpu);
    spend_cycles(4);
}

/*
   CMP_ABS - Load Accumulator from Absolute address.
   This function fetches a two-byte absolute address from memory, reads the value at that address,
   and loads it into the Accumulator (A). It then sets the status flags.
*/
static inline void
CMP_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    Word Absolute = FetchWord(Cycles, memory, cpu);
    Byte Data = ReadByte(Cycles, Absolute, memory);
    Byte Result = cpu->A - Data;
    CMPSetStatus(Result, cpu);
    spend_cycles(4);
}

/*
   CMP_ABSX - Load Accumulator from Absolute address with X Offset.
   Similar to CMP_ABS, but adds the X register value to the absolute address before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/
static inline void
CMP_ABSX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    Word Absolute = FetchWord(Cycles, memory, cpu);
    Word NewAddress = Absolute + cpu->X;

    if ((NewAddress & 0xFF00) != (Absolute & 0xFF00)) {
        (*Cycles)++;
        spend_cycle();
    }

    Byte Data = ReadByte(Cycles, NewAddress, memory);
    Byte Result = cpu->A - Data;
    CMPSetStatus(Result, cpu);
    spend_cycles(4);
}

/*
   CMP_ABSY - Load Accumulator from Absolute address with Y Offset.
   Similar to CMP_ABS, but adds the Y register value to the absolute address before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/
static inline void
CMP_ABSY(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    Word Absolute = FetchWord(Cycles, memory, cpu);
    Word NewAddress = Absolute + cpu->Y;

    if ((NewAddress & 0xFF00) != (Absolute & 0xFF00)) {
        (*Cycles)++;
        spend_cycle();
    }

    Byte Data = ReadByte(Cycles, NewAddress, memory);
    Byte Result = cpu->A - Data;
    CMPSetStatus(Result, cpu);
    spend_cycles(4);
}

#endif // CMP_H
