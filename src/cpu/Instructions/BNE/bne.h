#ifndef BNE_H
#define BNE_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the BNE (Branch if Not Equal) instruction for MOS
   Technology 6502. BNE branches to a new location if the Zero flag is clear
   (i.e., result was not zero).

   For more information about the instructions, refer to Instructions.MD
*/

/*
   BNE - Branch if Not Equal:
   This function fetches a one-byte signed relative offset from memory,
   checks if the Zero flag is clear, and if so, adds the offset to the program
   counter (PC), effectively branching to a new location. Cycle counts are
   adjusted accordingly, with extra cycles if the branch is taken and if it
   crosses a page boundary.
*/

static inline void
BNE (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  if (cpu->Flag.Z == 0)
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

#endif // BNE_H
