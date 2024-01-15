#ifndef MEM6502_H
#define MEM6502_H

#include "../../../config/config.h"

extern const DWord MAX_MEM;

typedef struct
{
    Byte *Data; // Emulates RAM to allocate 65 Kilobytes for storing data.
} MEM6502;

// Initializes memory to 65 Kilobytes (64 * 1024 Bytes).
void initializeMem6502(MEM6502 *memory);

// Frees 65 Kilobytes of RAM.
void freeMem6502(MEM6502 *memory);

// Reads data stored at the specified address.
Byte ReadByte(Word *Cycles, Word Address, MEM6502* memory);
Word ReadWord(Word *Cycles, Word Address, MEM6502* memory);

// Writes data at the specified address.
void WriteByte(Word *Cycles, Word Value, MEM6502 *mem, DWord Address);
void WriteWord(Word *Cycles, Word Value, MEM6502 *mem, DWord Address);

#endif // MEM6502_H
