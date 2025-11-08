#ifndef BVS_H
#define BVS_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the BVS (Branch if Overflow Set) instruction for
   MOS Technology 6502. BVS branches to a new location if the Overflow flag is
   set. For more information about the instructions, refer to Instructions.MD
*/

/*
   BVS - Branch if Overflow Set:
   This function fetches a signed byte from memory as a relative offset,
   then checks if the Overflow flag is set. If it is, it adds the signed offset
   to the program counter (PC) to branch. The cycle count is adjusted, with an
   extra cycle if the branch is taken, and another cycle if the branch crosses
   a page boundary.
*/

static inline void
BVS (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  if (cpu->Flag.V == 1)
    {
      Byte relative_offset = FetchByte (bus, memory, cpu);
      Word old_pc = cpu->PC;
      cpu->PC += (SignedByte)relative_offset;

      
      spend_cycle ();

      if ((old_pc & 0xFF00) != (cpu->PC & 0xFF00))
        {
          
          spend_cycle ();
        }
    }
  spend_cycles (2);
}

#endif // BVS_H
