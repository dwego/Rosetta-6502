#ifndef ROL_H
#define ROL_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the ROL (Load Accumulator) instruction for MOS Technology 6502.
   ROL works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   ROL (Load Accumulator) instruction supports various ROLressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/

/*
   This function sets the Flags for the Status register
   to identify what happened during the ROL instruction.
*/
void ROLSetStatus(Byte originalValue, Byte result, CPU6502 *cpu) 
{
    // Carry vem do bit 7 do valor original (antes da rotação)
    cpu->Flag.C = (originalValue & 0x80) ? 1 : 0;

    // Zero e Negative vêm do resultado da rotação
    cpu->Flag.Z = (result == 0);
    cpu->Flag.N = (result & 0x80) != 0;
}
/*
   ROL_IM - Load Accumulator with Immediate value.
   This function fetches a byte from memory and loads it into the Accumulator (A).
   It then sets the status flags using ROLSetStatus.
*/
void ROL_ACC(Word *Cycles, CPU6502 *cpu) 
{
    Byte oldCarry = cpu->Flag.C;
    Byte original = cpu->A;

    Byte result = (cpu->A << 1) | oldCarry;
    cpu->A = result;
    (*Cycles)--;

    ROLSetStatus(original, result, cpu);
}
/*
   ROL_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page ROLress from memory, reads the
   value at that ROLress, and loads it into the Accumulator (A). It then sets the status flags.
*/
void ROL_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) 
{
    Byte addr = FetchByte(Cycles, memory, cpu);

    Byte original = ReadByte(Cycles, addr, memory);
    Byte oldCarry = cpu->Flag.C;

    Byte result = (original << 1) | oldCarry;
    WriteByte(Cycles, result, memory, addr);

    ROLSetStatus(original, result, cpu);
}
/*
   ROL_ZPX - Load Accumulator from Zero Page with X Offset.
   Similar to ROL_ZP, but ROLs the X register value to the zero-page ROLress before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/
void ROL_ZPX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) 
{
    Byte addr = FetchByte(Cycles, memory, cpu);
    addr += cpu->X;
    (*Cycles)--;

    Byte original = ReadByte(Cycles, addr, memory);
    Byte oldCarry = cpu->Flag.C;

    Byte result = (original << 1) | oldCarry;
     WriteByte(Cycles, result, memory, addr);

    ROLSetStatus(original, result, cpu);
}

/*
   ROL_ABS - Load Accumulator from Absolute ROLress.
   This function fetches a two-byte absolute ROLress from memory, reads the value at that ROLress,
   and loads it into the Accumulator (A). It then sets the status flags.
*/
void ROL_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) 
{
    Word addr = FetchWord(Cycles, memory, cpu);

    Byte original = ReadByte(Cycles, addr, memory);
    Byte oldCarry = cpu->Flag.C;

    Byte result = (original << 1) | oldCarry;
     WriteByte(Cycles, result, memory, addr);

    ROLSetStatus(original, result, cpu);
}


/*
   ROL_ABSX - Load Accumulator from Absolute ROLress with X Offset.
   Similar to ROL_ABS, but ROLs the X register value to the absolute ROLress before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/
void ROL_ABSX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) 
{
    Word addr = FetchWord(Cycles, memory, cpu);
    addr += cpu->X;

    Byte original = ReadByte(Cycles, addr, memory);
    Byte oldCarry = cpu->Flag.C;

    Byte result = (original << 1) | oldCarry;
     WriteByte(Cycles, result, memory, addr);

    ROLSetStatus(original, result, cpu);
}

#endif // ROL_H
