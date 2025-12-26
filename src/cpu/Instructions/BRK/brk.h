#ifndef BRK_H
#define BRK_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

#ifdef I
#undef I
#endif

/*
   This is a header file for the BRK (Force Interrupt) instruction for MOS
   Technology 6502. BRK triggers a software interrupt by pushing the program
   counter and processor status to the stack, then loading the interrupt vector
   address into the program counter.

   For more information about the instructions, refer to Instructions.MD
*/

/*
   BRK - Force Interrupt:
   This function increments the program counter by 2 to point past the BRK
   opcode, pushes the program counter and the processor status register (with
   the Break flag set) onto the stack, sets the Interrupt Disable flag to
   prevent further interrupts, and finally loads the interrupt vector address
   from memory location $FFFE/$FFFF into the PC. Cycle counts are adjusted
   according to the 6502 timing for this instruction.
*/

static inline void
BRK (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  cpu->PC += 2;
  

  PushPCToStack (bus, memory, cpu);

  Byte status_with_B = cpu->PS | 0x10;

  PushByteToStack (bus, memory, status_with_B, cpu);

  cpu->Flag.I = 1;
  cpu->PS |= (1 << 2); // Set Interrupt Disable flag in PS

  Byte lo = memory->Data[0xFFFE];
  Byte hi = memory->Data[0xFFFF];
  cpu->PC = (hi << 8) | lo;
  spend_cycles (7);
}

#endif // BRK_H
