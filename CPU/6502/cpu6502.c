#include "cpu6502.h"
//#include "config/stack.h"

void resetCPU(Word ResetVector, CPU6502 *cpu, MEM6502 *memory) {

  cpu->A = cpu->X = cpu->Y = 0;

  cpu->PC = ResetVector;  // Starting address, replace with your actual start address
  cpu->SP = 0xFF;  // Starting Stack Pointer to 0xFF

  cpu->Flag.C = cpu->Flag.Z = cpu->Flag.I = cpu->Flag.D = cpu->Flag.B = cpu->Flag.V = cpu->Flag.N = 0; // set all flags to 0
  initializeMem6502(memory); // Initialize Memory to allocate 64 kilobytes "RAM"
}

Byte FetchByte(Word *Cycles, const MEM6502* memory, CPU6502 *cpu) {
    // Fetch to Byte value in Address stored in register PC *Program counter
    Byte Data = memory->Data[cpu->PC];
    cpu->PC++;
    (*Cycles)--;
    return Data;
}

Word FetchWord(Word *Cycles, const MEM6502* memory, CPU6502 *cpu) {
    Word Value = memory->Data[cpu->PC];
	cpu->PC++;
		
	Value |= (memory->Data[cpu->PC] << 8 );
	cpu->PC++;

    (*Cycles) -= 2;
	return Value;
}

Word SPToAddress(CPU6502 *cpu) {
    return 0x100 | cpu->SP;
}


void PushWordToStack(Word *Cycles, MEM6502 *memory, Word Value, CPU6502 *cpu) {
    printf("Before Push - SP: %02X, Memory[%04X]: %02X\n", cpu->SP, SPToAddress(cpu), memory->Data[SPToAddress(cpu)]);

    WriteByte(Cycles, Value >> 8, memory, SPToAddress(cpu));

    printf("After 1st Write - SP: %02X, Memory[%04X]: %02X\n", cpu->SP, SPToAddress(cpu), memory->Data[SPToAddress(cpu)]);
    cpu->SP--;

    WriteByte(Cycles, Value & 0xFF, memory, SPToAddress(cpu));

    printf("After 2nd Write - SP: %02X, Memory[%04X]: %02X\n", cpu->SP, SPToAddress(cpu), memory->Data[SPToAddress(cpu)]);
}


void PushPCToStack(Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
    PushWordToStack(Cycles, memory, cpu->PC, cpu);
}

Word PopWordFromStack(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {

    Word ValueFromStack = ReadWord(Cycles, SPToAddress(cpu), memory);

    return ValueFromStack;
}


// int main(void) {
//   CPU6502 cpu;
//   MEM6502 mem;
//   Word Cycles = 20;

//   resetCPU(0xFFFC, &cpu, &mem);
//   // start - inline a little program
//   mem.Data[0xFFFC] = INS_JSR;
//   mem.Data[0xFFFD] = 0x42;
//   mem.Data[0xFFFE] = 0x42;
//   mem.Data[0x4242] = INS_LDA_IM;
//   mem.Data[0x4243] = 0x84;
//   mem.Data[0x4244] = INS_RTS;
//   mem.Data[0xFFFF] = 0x42;

//   // end - inline a little program
//   execute(&Cycles, &mem, &cpu);
//   freeMem6502(&mem);

//   return 0;
// }