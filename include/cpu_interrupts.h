#ifndef CPU_INTERRUPTS_H
#define CPU_INTERRUPTS_H

#include "bus.h"
#include "cpu6502.h"
#include "mem6502.h"
#include "cpu_vectors.h"

/*
   CPU Interrupt Vectors

   The final six bytes of the 6502 address space contain the interrupt and
   reset vectors.

   Each vector is stored as a 16-bit little-endian address:
   - Low byte at VECTOR.
   - High byte at VECTOR + 1.
*/

/*
   cpu_set_irq - Set the current state of the external IRQ line.

   IRQ is level-sensitive. A device should keep the line active while the
   interrupt condition remains pending.
*/

void cpu_set_irq (CPU6502 *cpu, bool active);

/*
   cpu_pulse_nmi - Register a pending non-maskable interrupt.

   NMI is not blocked by the interrupt-disable flag. Calling this function
   records an NMI request, which will be handled before the next instruction.

*/
void cpu_pulse_nmi (CPU6502 *cpu);

/*
   cpu_handle_pending_interrupt - Handle a pending NMI or IRQ request.
*/
bool cpu_handle_pending_interrupt (Bus6502 *bus,
                                   MEM6502 *memory,
                                   CPU6502 *cpu);

#endif /* CPU_INTERRUPTS_H */