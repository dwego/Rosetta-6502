#include "cpu_interrupts.h"

#include "cpu6502.h"

/*
   CPU Interrupts - MOS Technology 6502 Interrupt Handling

   This module handles external IRQ and NMI requests for the emulated 6502.

   Interrupts are checked between instructions, before the next opcode is
   fetched. This matches the current instruction-level architecture of the
   emulator.

   A future cycle-accurate implementation may move these operations into
   individual bus cycles.
*/

/*
   status_for_interrupt_push - Build the status byte saved by IRQ or NMI.

   The break bit does not represent a persistent physical flag inside the
   original 6502. Instead, its value in the stacked status byte identifies
   how the processor entered the interrupt routine.

   IRQ and NMI push:
   - Break bit cleared.
   - Unused bit set.

*/

static Byte
status_for_interrupt_push (const CPU6502 *cpu)
{
  Byte status = cpu->PS;

  status &= (Byte)~(1u << 4);

  status |= (Byte)(1u << 5);

  return status;
}

/*
   read_interrupt_vector - Read a 16-bit interrupt vector from memory.

   Interrupt vectors are stored in little-endian format. The low byte is read
   first, followed by the high byte.

*/

static Word
read_interrupt_vector (Bus6502 *bus,
                       MEM6502 *memory,
                       Word vector)
{
  cpu_read (bus, memory, vector);
  Byte low = bus->data;

  cpu_read (bus, memory, (Word)(vector + 1));
  Byte high = bus->data;

  return ((Word)high << 8) | low;
}

/*
   enter_interrupt - Transfer execution to an interrupt handler.

   This function contains the operations shared by IRQ and NMI:
   - Push the current program counter.
   - Push the processor status.
   - Disable maskable interrupts.
   - Load the selected interrupt vector.
   - Account for seven interrupt cycles.

   The program counter already points to the next instruction because
   interrupts are checked before the next opcode fetch.
*/
static void
enter_interrupt (Bus6502 *bus,
                 MEM6502 *memory,
                 CPU6502 *cpu,
                 Word vector)
{
  PushWordToStack (bus, memory, cpu->PC, cpu);

  PushByteToStack (bus,
                   memory,
                   status_for_interrupt_push (cpu),
                   cpu);

  cpu->Flag.I = 1;

  cpu->PC = read_interrupt_vector (bus, memory, vector);

  spend_cycles (7);
}

void
cpu_set_irq (CPU6502 *cpu, bool active)
{
  if (cpu == NULL)
    return;

  cpu->irq_line = active;
}

void
cpu_pulse_nmi (CPU6502 *cpu)
{
  if (cpu == NULL)
    return;

  cpu->nmi_pending = true;
}

bool
cpu_handle_pending_interrupt (Bus6502 *bus,
                              MEM6502 *memory,
                              CPU6502 *cpu)
{
  if (bus == NULL || memory == NULL || cpu == NULL)
    return false;

  if (cpu->nmi_pending)
    {
      cpu->nmi_pending = false;

      enter_interrupt (bus, memory, cpu, NMI_VECTOR);
      return true;
    }

  if (cpu->irq_line && !cpu->Flag.I)
    {
      enter_interrupt (bus, memory, cpu, IRQ_VECTOR);
      return true;
    }

  return false;
}