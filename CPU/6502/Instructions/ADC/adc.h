#ifndef ADC_H
#define ADC_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"


/*
   This is a header file for the ADC (Add with Carry) instruction for MOS Technology 6502.
   ADC adds a value and the carry flag to the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/


/*
   This function sets the Flags for the Status register
   to represent the result of the ADC instruction.
*/


void ADCSetStatus(CPU6502 *cpu, Byte before, Byte value){
    cpu->Flag.Z = (cpu->A == 0);
    cpu->Flag.N = (cpu->A & 0x80) > 0;
    cpu->Flag.V = (~(before ^ value) & (before ^ cpu->A) & 0x80) != 0;
    cpu->Flag.C = (cpu->A < before);
}


/*
   ADC_IM - Add Immediate value and the carry flag (if set) to the Accumulator.
   This function fetches a byte from memory and adds it and the carry flag (if set) to the Accumulator (A).
   It then sets the status flags.
*/


void
ADC_IM(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    Byte Value = FetchByte(Cycles, memory, cpu);

    Byte Before = cpu->A;
    cpu->A += Value + cpu->Flag.C;
    ADCSetStatus(cpu, Before, Value);
    spend_cycles(2);

}


/*
   ADC_ZP - Add value from Zero Page and the carry flag (if set) to the Accumulator.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, and adds it and the carry flag (if set) to the Accumulator (A).
   It then sets the status flags.
*/


void
ADC_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    Byte Value = ReadByte(Cycles, ZeroPageAddr, memory);

    Byte Before = cpu->A;
    cpu->A += Value + cpu->Flag.C;
    ADCSetStatus(cpu, Before, Value);
    spend_cycles(3);
}


/*
   ADC_ZPX - Add value from Zero Page with X Offset and the carry flag (if set) to the Accumulator.
   This function fetches a byte representing a zero-page address from memory, adds the X register to this address,
   reads the value at the resultant address, and adds it and the carry flag (if set) to the Accumulator (A).
   It then sets the status flags.
*/


void
ADC_ZPX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    ZeroPageAddr += cpu->X;

    Byte Value = ReadByte(Cycles, ZeroPageAddr, memory);
    Byte Before = cpu->A;
    cpu->A += Value + cpu->Flag.C;
    ADCSetStatus(cpu, Before, Value);
     spend_cycles(4);
}


/*
   ADC_ABS - Add value from Absolute address and the carry flag (if set) to the Accumulator.
   This function fetches an absolute address from memory, reads the value at that address,
   and adds it and the carry flag (if set) to the Accumulator (A).
   It then sets the status flags.
*/


void
ADC_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    Word Absolute = FetchWord(Cycles, memory, cpu);

    Byte Value = ReadByte(Cycles, Absolute, memory);
    Byte Before = cpu->A;
    cpu->A += Value + cpu->Flag.C;
    ADCSetStatus(cpu, Before, Value);
     spend_cycles(4);
}


/*
   ADC_ABSX - Add value from Absolute address with X Offset and the carry flag (if set) to the Accumulator.
   This function fetches an absolute address from memory, adds the X register to this address,
   reads the value at the resultant address, and adds it and the carry flag (if set) to the Accumulator (A).
   It then sets the status flags.
*/


void
ADC_ABSX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    Word Absolute = FetchWord(Cycles, memory, cpu);
    Word NewAddress = Absolute + cpu->X;

    if ((NewAddress & 0xFF00) != (Absolute & 0xFF00)) {
        (*Cycles)++;
         spend_cycle();
    }

    Byte Value = ReadByte(Cycles, NewAddress, memory);
    Byte Before = cpu->A;
    cpu->A += Value + cpu->Flag.C;
    ADCSetStatus(cpu, Before, Value);
     spend_cycles(4);
}


/*
   ADC_ABSY - Add value from Absolute address with Y Offset and the carry flag (if set) to the Accumulator.
   This function fetches an absolute address from memory, adds the Y register to this address,
   reads the value at the resultant address, and adds it and the carry flag (if set) to the Accumulator (A).
   It then sets the status flags.
*/


void
ADC_ABSY(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    Word Absolute = FetchWord(Cycles, memory, cpu);
    Word NewAddress = Absolute + cpu->Y;

    if ((NewAddress & 0xFF00) != (Absolute & 0xFF00)) {
        (*Cycles)++;
         spend_cycle();
    }

    Byte Value = ReadByte(Cycles, NewAddress, memory);
    Byte Before = cpu->A;
    cpu->A += Value + cpu->Flag.C;
    ADCSetStatus(cpu, Before, Value);
     spend_cycles(4);
}

#endif
