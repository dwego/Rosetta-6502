#include "cpu6502.h"

/*
   CPU6502 - 6502 Emulated CPU

   This file implements the CPU (Central Processing Unit) functionality for the
   MOS Technology 6502.

   The MOS Technology 6502 is a widely used 8-bit microprocessor, and this
   implementation provides functions for initializing the CPU, fetching bytes
   and words from memory, and stack manipulation.

   This file implement instructions for functions defined in cpu6502.h

   Functions:
   - resetCPU: This function resets the CPU state to its initial values.
   - FetchByte: This function fetches a byte of data from the memory using the
   Program Counter (PC).
   - FetchWord: This function fetches a 16-bit word of data from the memory
   using the program counter (PC).
   - SPToAddress: This function converts the Stack Pointer (SP) value to a
   memory address.
   - PushWordToStack: This function pushes a 16-bit word onto the stack.
   - PushPCToStack: This function pushes the Program Counter (PC) onto the
   stack.
   - PopWordFromStack: This function pops a 16-bit word from the stack.

   For more information about the instructions and addressing modes, refer to
   Instructions.MD
*/

// Função para inicializar o timer
void
clock_init ()
{
  clock_gettime (CLOCK_MONOTONIC_RAW, &start_time);
}

// Função para sincronizar o clock com o tempo real
void
sync_clock ()
{
  double expected_time_sec = (double)total_cycles_executed / (CPU_FREQ_HZ);
  struct timespec now;
  clock_gettime (CLOCK_MONOTONIC_RAW, &now);

  double elapsed_sec = (now.tv_sec - start_time.tv_sec)
                       + (now.tv_nsec - start_time.tv_nsec) / 1e9;

  while (elapsed_sec < expected_time_sec)
    {
      // Pode dormir pouco para economizar CPU
      struct timespec ts = { 0, 1000 }; // 1 microssegundo
      nanosleep (&ts, NULL);
      clock_gettime (CLOCK_MONOTONIC_RAW, &now);
      elapsed_sec = (now.tv_sec - start_time.tv_sec)
                    + (now.tv_nsec - start_time.tv_nsec) / 1e9;
    }
}

// Simula gastar um ciclo de clock
void
spend_cycle ()
{
  total_cycles_executed++;
  sync_clock ();
}

void
spend_cycles (Word cycles)
{
  for (Word i = 0; i < cycles; i++)
    {
      spend_cycle (); // spend_cycle() espera o tempo de 1 ciclo
    }
}

// This function resets the CPU state to its initial values.
void
resetCPU (CPU6502 *cpu, MEM6502 *memory)
{
  cpu->A = cpu->X = cpu->Y = 0;
  cpu->SP = 0xFD; // valor real após RESET
  cpu->Flag.C = cpu->Flag.Z = cpu->Flag.I = cpu->Flag.D = cpu->Flag.B
      = cpu->Flag.V = cpu->Flag.N = 0;

  /* Lê o vetor de reset (little-endian) */
  Byte lo = memory->Data[0xFFFC];
  Byte hi = memory->Data[0xFFFD];
  cpu->PC = ((Word)hi << 8) | lo;
}

// This function fetches a byte of data from the memory using the program
// counter (PC).
Byte
FetchByte (Word *Cycles, const MEM6502 *memory, CPU6502 *cpu)
{
  // Fetch to Byte value in Address stored in register PC *Program counter
  Byte Data = memory->Data[cpu->PC];
  cpu->PC++;
  (*Cycles)--;
  return Data;
}

// This function fetches a 16-bit word of data from the memory using the
// program counter (PC).
Word
FetchWord (Word *Cycles, const MEM6502 *memory, CPU6502 *cpu)
{
  Word Value = memory->Data[cpu->PC];
  cpu->PC++;

  Value |= (memory->Data[cpu->PC] << 8);
  cpu->PC++;

  (*Cycles) -= 2;
  return Value;
}

// This function converts the Stack Pointer (SP) value to a memory address.

Word
SPToAddress (CPU6502 *cpu)
{
  return 0x100 | cpu->SP;
}

void
PushByteToStack (Word *Cycles, MEM6502 *memory, Word Value, CPU6502 *cpu)
{
  WriteByte (Cycles, Value, memory, SPToAddress (cpu));
  cpu->SP--;
}

// This function pushes a 16-bit word onto the stack.
void
PushWordToStack (Word *Cycles, MEM6502 *memory, Word Value, CPU6502 *cpu)
{
  WriteByte (Cycles, Value >> 8, memory, SPToAddress (cpu));

  WriteByte (Cycles, Value & 0xFF, memory, SPToAddress (cpu));
  cpu->SP--;
}

// This function pushes the Program Counter (PC) onto the stack.
void
PushPCToStack (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  PushWordToStack (Cycles, memory, cpu->PC, cpu);
}

// This function pops a 16-bit word from the stack.
Word
PopWordFromStack (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Word ValueFromStack = ReadWord (Cycles, SPToAddress (cpu), memory);

  return ValueFromStack;
}

Word
PopByteFromStack (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Word ValueFromStack = ReadByte (Cycles, SPToAddress (cpu), memory);
  WriteByte (Cycles, 0, memory, SPToAddress (cpu));
  cpu->SP--;

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
