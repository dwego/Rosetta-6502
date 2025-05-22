#ifndef STX_H
#define STX_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

// TODO Arrumar os comentarios


/*
   This is a header file for the STX (Store Index Register X) instruction for MOS Technology 6502.
   STX works by moving the value from the Index Register X (X) to a specific memory address.
   For more information about the instructions, refer to Instructions.MD
*/

/*
   This function sets the Flags for the Status register
   to identify what happened during the STX instruction.
*/


static inline void STXSetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->X == 0);
    cpu->Flag.N = (cpu->X & 0x80) > 0;
}


/*
   STX (Store Index Register X) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the destination for the data from the Index Register X (X).
*/


/*
   STX_ZP - Load Index Register X from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, and loads it into the Index Register X (X). It then sets the status flags.
*/


static inline void STX_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    WriteByte(Cycles, cpu->X, memory, ZeroPageAddr);
    STXSetStatus(cpu);
     spend_cycles(3);
}


/*
   STX_ZPX - Load Index Register X from Zero Page with X Offset.
   Similar to STX_ZP, but adds the Y register value to the zero-page address before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


static inline void STX_ZPY(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    ZeroPageAddr += cpu->Y;
    (*Cycles)--;
    WriteByte(Cycles, cpu->X, memory, ZeroPageAddr);
    STXSetStatus(cpu);
     spend_cycles(4);
}


/*
   STX_ABS - Load Index Register X from Absolute address.
   This function fetches a two-byte absolute address from memory, reads the value at that address,
   and loads it into the Index Register X (X). It then sets the status flags.
*/



static inline void STX_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    WriteByte(Cycles, cpu->X, memory, Absolute);
    STXSetStatus(cpu);
     spend_cycles(4);
}

#endif // STX_H
