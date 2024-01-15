#ifndef CPU6502_H
#define CPU6502_H

#include "../../config/config.h"

typedef struct StatusFlags
{	
	Byte C : 1;	//0: Carry Flag	
	Byte Z : 1;	//1: Zero Flag
	Byte I : 1; //2: Interrupt disable
	Byte D : 1; //3: Decimal mode
	Byte B : 1; //4: Break
	Byte Unused : 1; //5: Unused
	Byte V : 1; //6: Overflow
	Byte N : 1; //7: Negative
} StatusFlags ;

typedef struct {
    Byte A, X, Y;   // registers
    Byte SP;        // stack pointer
    Word PC;        // program counter
    Byte S;         // status

    union // processor status
	{
		Byte PS;	
		StatusFlags Flag;
	};
} CPU6502;

void resetCPU(Word ResetVector, CPU6502 *cpu, MEM6502 *memory);

Byte FetchByte(Word *Cycles, const MEM6502* memory, CPU6502 *cpu);
Word FetchWord(Word *Cycles, const MEM6502* memory, CPU6502 *cpu);

Word SPToAddress(CPU6502 *cpu);

void PushWordToStack(Word *Cycles, MEM6502 *memory, Word Value, CPU6502 *cpu);
void PushPCToStack(Word *Cycles, MEM6502 *memory, CPU6502 *cpu);
Word PopWordFromStack(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)

void execute(Word *Cycles, MEM6502 *memory, CPU6502 *cpu);

#endif // CPU6502_H
