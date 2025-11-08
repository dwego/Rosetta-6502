#ifndef BEQ_H
#define BEQ_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

/*
   This is a header file for the BEQ (Branch if Equal) instruction for MOS
   Technology 6502. BEQ branches to a new location if the Zero flag (Z) is set.
   For more information about the instructions, refer to Instructions.MD
*/

/*
   BEQ - Branch if Equal:
   This function fetches a one-byte signed relative offset from memory,
   checks if the Zero flag is set, and if so, adjusts the program counter (PC)
   by the signed offset. It adjusts the cycle count according to the rules of
   the BEQ instruction, including extra cycles for a successful branch and
   crossing a page boundary.
*/

static inline void
BEQ (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  Byte Relative = FetchByte (bus, memory, cpu);

  if (cpu->Flag.Z == 1)
    {
      Word OldPC = cpu->PC;
      cpu->PC += (SignedByte)Relative;

      
      spend_cycle ();

      if ((OldPC & 0xFF00) != (cpu->PC & 0xFF00))
        {
          
          spend_cycle ();
        }
    }

  spend_cycles (2);
}

#endif // BEQ_H
