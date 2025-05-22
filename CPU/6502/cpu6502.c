#include "cpu6502.h"
#include "config.h"
#include <time.h>

/*
   CPU6502 - MOS Technology 6502 CPU Emulator

   This file contains the implementation of the core CPU functions for the
   8-bit MOS Technology 6502 microprocessor.

   The 6502 was a popular CPU used in many classic systems such as the NES,
   Commodore 64, and Apple II.

   This implementation covers CPU initialization, fetching instructions and
   operands from memory, stack operations, and timing synchronization.

   Functions implemented here correspond to those declared in cpu6502.h.

   Key functionalities:
   - resetCPU: Initialize the CPU registers and set the program counter based
     on the reset vector.
   - FetchByte: Fetch a single byte from memory at the current program counter,
     then increment the PC.
   - FetchWord: Fetch a 16-bit word (little endian) from memory at the PC,
     incrementing the PC by two.
   - SPToAddress: Convert the 8-bit stack pointer to the corresponding 16-bit
     memory address in the 0x0100-0x01FF page.
   - PushByteToStack: Push a single byte onto the CPU stack.
   - PushWordToStack: Push a 16-bit word onto the CPU stack (high byte first).
   - PushPCToStack: Push the current program counter onto the stack.
   - PopWordFromStack: Pop a 16-bit word from the stack.
   - PopByteFromStack: Pop a single byte from the stack.

   Timing control:
   - The CPU execution is synchronized to real time based on the CPU clock
     frequency.
   - Functions clock_init, sync_clock, spend_cycle, and spend_cycles manage
     this synchronization.

   For detailed instruction behavior and addressing modes, see Instructions.MD.
*/

QWord total_cycles_executed = 0;
struct timespec start_time;

// Initialize the monotonic clock to start timing CPU cycles.
void
clock_init ()
{
  clock_gettime (CLOCK_MONOTONIC_RAW, &start_time);
}

// Synchronize the emulated CPU clock with real elapsed time.
// This function will sleep in small increments if the emulator is running
// faster than real time, ensuring accurate timing.
void
sync_clock ()
{
  double expected_time_sec = (double)total_cycles_executed / (CPU_FREQ_HZ);
  struct timespec now;
  clock_gettime (CLOCK_MONOTONIC_RAW, &now);

  double elapsed_sec = (now.tv_sec - start_time.tv_sec)
                       + (now.tv_nsec - start_time.tv_nsec) / 1e9;

  if (log_file)
    {
      fprintf (log_file, "[sync_clock] total_cycles_executed = %llu\n",
               (unsigned long long)total_cycles_executed);
      fprintf (log_file, "[sync_clock] expected_time_sec = %f\n",
               expected_time_sec);
      fprintf (log_file, "[sync_clock] elapsed_sec = %f\n", elapsed_sec);
    }

  // Wait until the elapsed real time catches up with the emulated CPU cycles.
  while (elapsed_sec < expected_time_sec)
    {
      // Sleep for 1 microsecond to reduce CPU load while waiting.
      struct timespec ts = { 0, 1000 };
      nanosleep (&ts, NULL);
      clock_gettime (CLOCK_MONOTONIC_RAW, &now);
      elapsed_sec = (now.tv_sec - start_time.tv_sec)
                    + (now.tv_nsec - start_time.tv_nsec) / 1e9;

      if (log_file)
        {
          fprintf (log_file,
                   "[sync_clock] Waiting... elapsed_sec = %f, "
                   "expected_time_sec = %f\n",
                   elapsed_sec, expected_time_sec);
          fflush (log_file); // flush immediately to log file
        }
    }
}

// Simulate the consumption of one CPU clock cycle.
// Increments the total cycles count and synchronizes timing.
void
spend_cycle ()
{
  total_cycles_executed++;
  fprintf (log_file,
           "[spend_cycle] total_cycles_executed incremented to %llu\n",
           (unsigned long long)total_cycles_executed);
  sync_clock ();
}

// Simulate the consumption of multiple CPU clock cycles.
void
spend_cycles (Word cycles)
{
  for (Word i = 0; i < cycles; i++)
    {
      spend_cycle ();
    }
}

// Reset the CPU registers and flags to their power-on default state.
// Sets the stack pointer to 0xFD as per 6502 reset behavior.
// Reads the reset vector (0xFFFC and 0xFFFD) to set the program counter.
void
resetCPU (CPU6502 *cpu, MEM6502 *memory)
{
  cpu->A = cpu->X = cpu->Y = 0;
  cpu->SP = 0xFD;

  // Clear all flags: Carry, Zero, Interrupt Disable, Decimal,
  // Break, Overflow, Negative
  cpu->Flag.C = cpu->Flag.Z = cpu->Flag.I = cpu->Flag.D = cpu->Flag.B
      = cpu->Flag.V = cpu->Flag.N = 0;

  // Load the reset vector address (little-endian) from memory
  Byte lo = memory->Data[0xFFFC];
  Byte hi = memory->Data[0xFFFD];
  cpu->PC = ((Word)hi << 8) | lo;
}

// Fetch a byte from memory at the current program counter (PC),
// increment PC by 1, and decrement the cycle count.
Byte
FetchByte (Word *Cycles, const MEM6502 *memory, CPU6502 *cpu)
{
  Byte Data = memory->Data[cpu->PC];
  cpu->PC++;
  (*Cycles)--;
  return Data;
}

// Fetch a 16-bit word (little-endian) from memory at the current PC,
// increment PC by 2, and decrement cycles by 2.
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

// Convert the 8-bit stack pointer (SP) to the 16-bit memory address
// in the stack page (0x0100 - 0x01FF).
Word
SPToAddress (CPU6502 *cpu)
{
  return 0x100 | cpu->SP;
}

// Push a byte onto the stack, write it to memory at the stack address,
// and decrement the stack pointer.
void
PushByteToStack (Word *Cycles, MEM6502 *memory, Word Value, CPU6502 *cpu)
{
  WriteByte (Cycles, Value, memory, SPToAddress (cpu));
  cpu->SP--;
}

// Push a 16-bit word onto the stack (high byte first, then low byte),
// decrementing the stack pointer accordingly.
// Note: The 6502 stack grows downward.
void
PushWordToStack (Word *Cycles, MEM6502 *memory, Word Value, CPU6502 *cpu)
{
  WriteByte (Cycles, Value >> 8, memory, SPToAddress (cpu));
  WriteByte (Cycles, Value & 0xFF, memory, SPToAddress (cpu));
  cpu->SP--;
}

// Push the current program counter (PC) onto the stack.
void
PushPCToStack (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  PushWordToStack (Cycles, memory, cpu->PC, cpu);
}

// Pop a 16-bit word from the stack.
// Reads from the stack memory and returns the combined word.
// Note: Stack pointer handling must be managed accordingly outside this
// function.
Word
PopWordFromStack (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Word ValueFromStack = ReadWord (Cycles, SPToAddress (cpu), memory);
  return ValueFromStack;
}

// Pop a byte from the stack, clear the byte in memory (optional),
// and decrement the stack pointer.
Word
PopByteFromStack (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Word ValueFromStack = ReadByte (Cycles, SPToAddress (cpu), memory);
  WriteByte (Cycles, 0, memory, SPToAddress (cpu));
  cpu->SP--;
  return ValueFromStack;
}
