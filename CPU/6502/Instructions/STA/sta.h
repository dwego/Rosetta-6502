#ifndef STA_H
#define STA_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

// TODO Arrumar os comentarios

/*
   This is a header file for the STA (Load Accumulator) instruction for MOS Technology 6502.
   STA works by moving a value into the Accumulator register (A).
   For more information about the instructions, refer to Instructions.MD
*/

/*
   STA (Load Accumulator) instruction supports various addressing modes in the 6502 architecture.
   The different modes provide flexibility in specifying the source of the data to be loaded into the Accumulator (A).
*/


/*
   This function sets the Flags for the Status register
   to identify what happened during the STA instruction.
*/


static inline void STASetStatus(CPU6502 *cpu) {
    cpu->Flag.Z = (cpu->A == 0);
    cpu->Flag.N = (cpu->A & 0x80) > 0;
}


/*
   STA_ZP - Load Accumulator from Zero Page.
   This function fetches a byte representing a zero-page address from memory, reads the
   value at that address, and loads it into the Accumulator (A). It then sets the status flags.
*/


static inline void STA_ZP(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    WriteByte(Cycles, cpu->A, memory, ZeroPageAddr);
    STASetStatus(cpu);
     spend_cycles(3);
}


/*
   STA_ZPX - Load Accumulator from Zero Page with X Offset.
   Similar to STA_ZP, but adds the X register value to the zero-page address before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


static inline void STA_ZPX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Byte ZeroPageAddr = FetchByte(Cycles, memory, cpu);
    ZeroPageAddr += cpu->X;
    (*Cycles)--;
    WriteByte(Cycles, cpu->A, memory, ZeroPageAddr);
    STASetStatus(cpu);
     spend_cycles(4);
}


/*
   STA_ABS - Load Accumulator from Absolute address.
   This function fetches a two-byte absolute address from memory, reads the value at that address,
   and loads it into the Accumulator (A). It then sets the status flags.
*/


static inline void STA_ABS(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    WriteByte(Cycles, cpu->A, memory, Absolute);
    STASetStatus(cpu);
     spend_cycles(4);
}


/*
   STA_ABSX - Load Accumulator from Absolute address with X Offset.
   Similar to STA_ABS, but adds the X register value to the absolute address before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


static inline void STA_ABSX(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    Absolute += cpu->X;
    WriteByte(Cycles, cpu->A, memory, Absolute);
    STASetStatus(cpu);
     spend_cycles(5);
}


/*
   STA_ABSY - Load Accumulator from Absolute address with Y Offset.
   Similar to STA_ABS, but adds the Y register value to the absolute address before reading
   the value from memory. It adjusts the cycle count accordingly and sets the status flags.
*/


static inline void STA_ABSY(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    Word Absolute = FetchWord(Cycles, memory, cpu);
    Absolute += cpu->Y;
    WriteByte(Cycles, cpu->A, memory, Absolute);
    STASetStatus(cpu);
     spend_cycles(5);
}

#endif // STA_H
