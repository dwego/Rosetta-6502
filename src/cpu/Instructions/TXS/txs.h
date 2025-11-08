#ifndef TXS_H
#define TXS_H

#include "config.h"
#include "cpu6502.h"

/*
   This is a header file for the TXS (Transfer X to Stack Pointer) instruction
   for MOS Technology 6502.
   TXS transfers the value from the Index Register X (X) to the Stack Pointer
   (SP). This instruction does not affect any flags. For more information about
   the instructions, refer to Instructions.MD
*/

/*
   TXS does NOT affect the Status flags.
   Therefore, no flag-setting function is needed.
*/

/*
   TXS - Transfer X to Stack Pointer.
   Copies the value from the X register into the Stack Pointer (SP).
   Does not modify any flags.
   Consumes 2 CPU cycles.
*/
static inline void
TXS (CPU6502 *cpu)
{
  cpu->SP = cpu->X;
  
  spend_cycles (2);
}

#endif // TXS_H
