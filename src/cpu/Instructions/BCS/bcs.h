#ifndef BCS_H
#define BCS_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the BCS (Branch if Carry Set) instruction for MOS
   Technology 6502. BCS branches to a new location if the Carry flag is set.
   For more information about the instructions, refer to Instructions.MD

   BCS - Branch if Carry Set:
   This function fetches a one-byte signed value from memory,
   checks if the Carry flag is set, and if so, adjusts the program counter (PC)
   by the fetched signed value. It adjusts the cycle count according to the
   rules of the BCS instruction, including extra cycles for a successful branch
   and crossing a page boundary.
*/

static inline void
BCS (Word *Cycles, MEM6502 *memory, CPU6502 *cpu)
{
  Byte Relative = FetchByte (Cycles, memory, cpu);

  if (cpu->Flag.C != 0)
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

#endif /* BCS_H */
