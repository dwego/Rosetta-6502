#ifndef ROR_H
#define ROR_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the ROR (Load Accumulator) instruction for MOS Technology 6502.
   ROR works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   ROR (Load Accumulator) instruction supports various RORressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the ROR instruction.
*/


static inline void RORSetStatus(Byte originalValue, Byte result, CPU6502 *cpu) 
{
    cpu->Flag.C = (originalValue & 0x01) ? 1 : 0;
    cpu->Flag.Z = (result == 0);
    cpu->Flag.N = (result & 0x80) != 0;
}


/*
   ROR_IM - Load Accumulator with Immediate value.
   This function fetches a byte from memory and loads it into the Accumulator (A).
   It then sets the status flags using RORSetStatus.
*/


static inline void ROR_ACC(Word *Cycles, CPU6502 *cpu) 
{
    Byte original = cpu->A;
    Byte oldCarry = cpu->Flag.C;

    Byte result = (original >> 1) | (oldCarry << 7);
    cpu->A = result;
    (*Cycles)--;

    RORSetStatus(original, result, cpu);
}
/*
   ROR_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page RORress from memory, reads the
   value at that RORress, and loads it into the Accumulator (A). It then sets the status flags.
*/


static inline void ROR_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) 
{
    Byte addr = FetchByte(Cycles, memory, cpu);

    Byte original = ReadByte(Cycles, addr, memory);
    Byte oldCarry = cpu->Flag.C;

    Byte result = (original >> 1) | (oldCarry << 7);
    WriteByte(Cycles, result, memory, addr);

    RORSetStatus(original, result, cpu);
}

/*
   ROR_ZPX - Load Accumulator from Zero Page with X Offset.
   Similar to ROR_ZP, but RORs the X register value to the zero-page RORress before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


static inline void ROR_ZPX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) 
{
    Byte addr = FetchByte(Cycles, memory, cpu);
    addr += cpu->X;
    (*Cycles)--;

    Byte original = ReadByte(Cycles, addr, memory);
    Byte oldCarry = cpu->Flag.C;

    Byte result = (original >> 1) | (oldCarry << 7);
    WriteByte(Cycles, result, memory, addr);

    RORSetStatus(original, result, cpu);
}

/*
   ROR_ABS - Load Accumulator from Absolute RORress.
   This function fetches a two-byte absolute RORress from memory, reads the value at that RORress,
   and loads it into the Accumulator (A). It then sets the status flags.
*/


static inline void ROR_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) 
{
    Word addr = FetchWord(Cycles, memory, cpu);

    Byte original = ReadByte(Cycles, addr, memory);
    Byte oldCarry = cpu->Flag.C;

    Byte result = (original >> 1) | (oldCarry << 7);
    WriteByte(Cycles, result, memory, addr);

    RORSetStatus(original, result, cpu);
}

/*
   ROR_ABSX - Load Accumulator from Absolute RORress with X Offset.
   Similar to ROR_ABS, but RORs the X register value to the absolute RORress before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


static inline void ROR_ABSX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) 
{
    Word addr = FetchWord(Cycles, memory, cpu);
    addr += cpu->X;

    Byte original = ReadByte(Cycles, addr, memory);
    Byte oldCarry = cpu->Flag.C;

    Byte result = (original >> 1) | (oldCarry << 7);
    WriteByte(Cycles, result, memory, addr);

    RORSetStatus(original, result, cpu);
}

#endif // ROR_H
