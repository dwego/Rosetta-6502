#include "bus.h"
#include "mem6502.h"

void
cpu_read (Bus6502 *bus, MEM6502 *memory, Word address, Word *Cycles)
{
  bus->address = address;
  bus->rw = true;
  bus->data = ReadByte (Cycles, address, memory);
}

void
cpu_write (Bus6502 *bus, MEM6502 *memory, Word address, Byte data,
           Word *Cycles)
{
  bus->address = address;
  bus->data = data;
  bus->rw = false;
  WriteByte (Cycles, bus->data, memory, bus->address);
}
