#include "mem6502.h"

const DWord MAX_MEM = 1024 * 64;

void initializeMem6502(MEM6502 *memory) {
    memory->Data = (Byte *)malloc(MAX_MEM);
    if (memory->Data == NULL) {
        exit(EXIT_FAILURE);
    }

    for (DWord i = 0; i < MAX_MEM; i++) {
      memory->Data[i] = 0;
    }
}

void freeMem6502(MEM6502 *memory) {
    free(memory->Data);
    memory->Data = NULL;  // Optional: define data null
}

void WriteWord(Word *Cycles, Word Value, MEM6502 *mem, DWord Address) {
    mem->Data[Address] = Value & 0xFF;
    mem->Data[Address + 1] = (Value >> 8);
    (*Cycles)-=2;
}

Byte ReadByte(Word *Cycles, Word Address, MEM6502* memory) {
    Byte Data = memory->Data[Address];
    (*Cycles)--;
    return Data;
}

Word ReadWord(Word *Cycles, Word Address, MEM6502* memory) {
    Byte LoByte = ReadByte( Cycles, Address, memory );
	Byte HiByte = ReadByte( Cycles, Address + 1, memory );
	return LoByte | (HiByte << 8);
}

void WriteByte(Word *Cycles, Word Value, MEM6502 *mem, DWord Address) {
    mem->Data[Address] = Value;
    (*Cycles)--;
}