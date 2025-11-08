#ifndef BPL_H
#define BPL_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the BPL (Branch if Positive) instruction for MOS
   Technology 6502. BPL branches to a new location if the Negative flag is
   clear (i.e., result is positive or zero).

   For more information about the instructions, refer to Instructions.MD
*/

/*
   BPL - Branch if Positive:
   This function fetches a one-byte signed relative offset from memory,
   checks if the Negative flag is clear, and if so, adds the offset to the
   program counter (PC), effectively branching to a new location. Cycle counts
   are adjusted accordingly, with extra cycles if the branch is taken and if it
   crosses a page boundary.
*/

static inline void
BPL (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  if (cpu->Flag.N == 0)
    {
      Byte relative_offset = FetchByte (bus, memory, cpu);
      Word old_pc = cpu->PC;
      cpu->PC += (char)relative_offset;

      
      spend_cycle ();
      if ((old_pc & 0xFF00) != (cpu->PC & 0xFF00))
        {
          
          spend_cycle ();
        }
    }
  spend_cycles (2);
}

#endif // BPL_H
