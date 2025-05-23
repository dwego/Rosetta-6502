#ifndef BUS_H
#define BUS_H

#include "config.h"
#include "mem6502.h"

typedef struct
{
  Word address;
  Byte data;
  bool rw;
} Bus6502;

void cpu_read (Bus6502 *bus, const MEM6502 *memory, Word address,
               Word *Cycles);
void cpu_write (Bus6502 *bus, MEM6502 *memory, Word address, Byte data,
                Word *Cycles);

#endif // BUS_H
