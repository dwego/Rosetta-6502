#ifndef BVC_H
#define BVC_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the BVC (Branch if Overflow Clear) instruction for
   MOS Technology 6502. BVC branches to a new location if the Overflow flag is
   clear. For more information about the instructions, refer to Instructions.MD
*/

/*
   BVC - Branch if Overflow Clear:
   This function fetches a signed byte from memory as a relative offset,
   then checks if the Overflow flag is clear. If it is, it adds the signed
   offset to the program counter (PC) to branch. The cycle count is adjusted,
   with an extra cycle if the branch is taken, and another cycle if the branch
   crosses a page boundary.
*/

static inline void
BVC (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  if (cpu->Flag.V == 0)
    {
      Byte Sub_Addr = FetchByte (Cycles, bus, memory, cpu);
      Word old_pc = cpu->PC;
      cpu->PC += (SignedByte)Sub_Addr;

      (*Cycles)--;
      spend_cycle ();

      if ((old_pc & 0xFF00) != (cpu->PC & 0xFF00))
        {
          (*Cycles)--;
          spend_cycle ();
        }
    }
  spend_cycles (2);
}

#endif // BVC_H
