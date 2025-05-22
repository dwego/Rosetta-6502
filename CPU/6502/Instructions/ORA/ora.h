#ifndef ORA_H
#define ORA_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/* 
   This is a header file for the OR (Load Accumulator) instruction for MOS Technology 6502.
   ORA works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   ORA (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the OR instruction.
*/


static inline void ORASetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->A == 0);
    cpu->Flag.N = (cpu->A & 0x80) > 0;
}


/*
   ORA_IM - Load Accumulator with Immediate value.
   This function fetches a byte from memory OR loads it into the Accumulator (A).
   It then sets the status flags using ORASetStatus.
*/


static inline void ORA_IM(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte Value = FetchByte(Cycles, memory, cpu);;
    cpu->A = Value | cpu->A;
    ORASetStatus(cpu);
     spend_cycles(2);
}


/*
   ORA_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, ORA loads it into the Accumulator (A). It then sets the status flags.
*/


static inline void ORA_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    cpu->A = ReadByte(Cycles, ZeroPageAddr, memory) | cpu->A;
    ORASetStatus(cpu);
     spend_cycles(3);
}


/*
   ORA_ZPX - Load Accumulator from Zero Page with X Offset.
   Similar to ORA_ZP, but adds the X register value to the zero-page address before reading
   the value from memory. It adjusts the cycle count accordingly ORA sets the status flags.
*/


static inline void ORA_ZPX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    ZeroPageAddr += cpu->X;
    (*Cycles)--;
    cpu->A = ReadByte(Cycles, ZeroPageAddr, memory) | cpu->A;
    ORASetStatus(cpu);
     spend_cycles(4);
}


/*
   ORA_ABS - Load Accumulator from Absolute address.
   This function fetches a two-byte absolute address from memory, reads the value at that address,
   ORA loads it into the Accumulator (A). It then sets the status flags.
*/


static inline void ORA_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    cpu->A = ReadByte(Cycles, Absolute, memory) | cpu->A;
    ORASetStatus(cpu);
     spend_cycles(4);
}


/*
   ORA_ABSX - Load Accumulator from Absolute address with X Offset.
   Similar to ORA_ABS, but adds the X register value to the absolute address before reading
   the value from memory. It adjusts the cycle count accordingly ORA sets the status flags.
*/


static inline void ORA_ABSX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);

    Word OldPage = Absolute & 0xFF00;
    Word AddressWithX = Absolute + cpu->X;
    Word NewPage = AddressWithX & 0xFF00;

    if (OldPage != NewPage) {
        (*Cycles)++;
        spend_cycle();
    }

    cpu->A = ReadByte(Cycles, AddressWithX, memory) | cpu->A;
    ORASetStatus(cpu);
    spend_cycles(4);
}
/*
   ORA_ABSY - Load Accumulator from Absolute address with Y Offset.
   Similar to ORA_ABS, but adds the Y register value to the absolute address before reading
   the value from memory. It adjusts the cycle count accordingly ORA sets the status flags.
*/


static inline void ORA_ABSY(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);

    Word OldPage = Absolute & 0xFF00;
    Word AddressWithY = Absolute + cpu->Y;
    Word NewPage = AddressWithY & 0xFF00;

    if (OldPage != NewPage) {
        (*Cycles)++;
        spend_cycle();
    }

    cpu->A = ReadByte(Cycles, AddressWithY, memory) | cpu->A;
    ORASetStatus(cpu);
    spend_cycles(4);
}

#endif // ORA_H
