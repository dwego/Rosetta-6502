#ifndef BCC_H
#define BCC_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the BCC (Branch if Carry Clear) instruction for
   MOS Technology 6502. BCC branches to a new location if the Carry flag is
   clear. For more information about the instructions, refer to Instructions.MD
*/

/*
   BCC (Branch if Carry Clear) instruction for the MOS Technology 6502 CPU.

   The BCC instruction causes a branch to a new memory location if the Carry
   flag is clear (0). It adds a signed 8-bit relative offset to the Program
   Counter (PC) when the condition is met.

   Flags affected: None.
   Timing: Takes 2 cycles plus 1 extra cycle if the branch is taken,
   plus another cycle if the branch crosses a page boundary.
*/

/*
   BCC - Branch if Carry Clear:
   This function fetches a one-byte signed relative offset from memory,
   checks if the Carry flag is clear,
   and if so, adds the signed offset to the program counter (PC).
   It adjusts the cycle count accordingly, including extra cycles for branching
   and page crossing.
*/

static inline void
BCC (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte Relative = FetchByte (Cycles, memory, cpu);
  if (cpu->Flag.C == 0)
    {
      Word OldPC = cpu->PC;
      cpu->PC += (SignedByte)Relative;

      (*Cycles)--;
      spend_cycle ();

      if ((OldPC & 0xFF00) != (cpu->PC & 0xFF00))
        {
          (*Cycles)--;
          spend_cycle ();
        }
    }
  spend_cycles (2);
}

#endif /* BCC_H */
