#ifndef MEM6502_H
#define MEM6502_H

#include "bus.h"
#include "config.h"

#define RAM_SIZE 65536

#define STACK_START 0x100
#define STACK_END 0x1FF

#define ROM_SIZE 4096

/*
   MEM6502 - 6502 Emulated Memory

   This is a header file for the mem6502.c

   This module provides an emulation of the memory system for the MOS
   Technology 6502 processor.

   The MOS 6502 processor, utilized in various computers and game consoles of
   the 1970s and 1980s, interacts with an addressable memory space. This module
   emulates a simplified version of this memory system, allowing the 6502
   instructions to read from and write to memory.

   The emulated memory is represented by a structure called MEM6502, containing
   an array of bytes to mimic RAM. The maximum size of this memory is defined
   as MAX_MEM (65 Kilobytes).
*/

// Maximum memory size for the 6502 system.
extern const DWord MAX_MEM;

// Structure representing the memory for the 6502 system.
typedef struct
{
  Byte *Data; // Emulates RAM to allocate 65 Kilobytes for storing data.
} MEM6502;

// Initializes memory to 65 Kilobytes (64 * 1024 Bytes).
void initializeMem6502 (MEM6502 *memory);

// Frees 65 Kilobytes of RAM.
void freeMem6502 (MEM6502 *memory);

void cpu_read (Bus6502 *bus, const MEM6502 *memory, Word address,
               Word *Cycles);

void cpu_write (Bus6502 *bus, MEM6502 *memory, Word address, Byte data,
                Word *Cycles);

#endif // MEM6502_H
