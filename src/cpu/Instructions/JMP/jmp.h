#ifndef JMP_H
#define JMP_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the JMP (Jump) instruction for MOS Technology
   6502. JMP is used to jump to a specified address unconditionally. For more
   information about the instruction, refer to Instructions.MD
*/

/*
   JMP_ABS - Jump to Absolute Address:
   This function fetches a two-byte absolute address from memory,
   then sets the program counter (PC) to that address.
   It updates the cycle count accordingly.
*/
static inline void
JMP_ABS (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Word Sub_Addr = FetchWord (Cycles, memory, cpu);
  cpu->PC = Sub_Addr;
  spend_cycles (3);
}

/*
   JMP_IND - Jump to Indirect Address (with 6502 bug emulation):
   This function fetches a two-byte pointer address from memory,
   then reads the 16-bit target address indirectly through this pointer.
   It emulates the 6502 bug where if the pointer low byte is 0xFF,
   the high byte is read from the start of the same memory page,
   instead of the next byte across the page boundary.
   The PC is then set to the target address.
   Cycle count is adjusted accordingly.
*/
static inline void
JMP_IND (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Word PtrAddr = FetchWord (Cycles, memory, cpu);

  Byte LoByte = ReadByte (Cycles, PtrAddr, memory);
  Byte HiByte;

  if ((PtrAddr & 0x00FF) == 0x00FF)
    {
      // Emulate page boundary bug: high byte read wraps around in the same
      // page
      HiByte = ReadByte (Cycles, PtrAddr & 0xFF00, memory);
    }
  else
    {
      // Normal case: high byte read from next address
      HiByte = ReadByte (Cycles, PtrAddr + 1, memory);
    }

  cpu->PC = (HiByte << 8) | LoByte;
  spend_cycles (5);
}

#endif // JMP_H
