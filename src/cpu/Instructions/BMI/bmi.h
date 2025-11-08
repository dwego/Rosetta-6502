#ifndef BMI_H
#define BMI_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the BMI (Branch if Minus) instruction for MOS
   Technology 6502. BMI branches to a new location if the Negative flag is set.

   For more information about the instructions, refer to Instructions.MD
*/

/*
   BMI - Branch if Minus:
   This function fetches a one-byte signed relative offset from memory,
   checks if the Negative flag is set, and if so, adds the offset to the
   program counter (PC), effectively branching to a new location. Cycle counts
   are adjusted accordingly, with extra cycles if the branch is taken and if it
   crosses a page boundary.
*/

static inline void
BMI (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{
  if (cpu->Flag.N != 0)
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

#endif // BMI_H
