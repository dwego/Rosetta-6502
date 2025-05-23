#include "mem6502.h"

// Maximum memory size for the 6502 system.
const DWord MAX_MEM = 1024 * 64;

/*
   MEM6502 - 6502 Emulated Memory

   This module provides an emulation of the memory system for the MOS
   Technology 6502 processor.

   The MOS 6502 processor, utilized in various computers and game consoles of
   the 1970s and 1980s, interacts with an addressable memory space. This module
   emulates a simplified version of this memory system, allowing the 6502
   instructions to read from and write to memory.

   The emulated memory is represented by a structure called MEM6502, containing
   an array of bytes to mimic RAM. The maximum size of this memory is defined
   as MAX_MEM (65 Kilobytes).

   This file implement instructions for functions defined in mem6502.h

   Functions:
   - initializeMem6502: Initializes the emulated memory, allocating space for
   65 Kilobytes of RAM.
   - freeMem6502: Frees the allocated memory used for emulating the 6502 memory
   system.
   - ReadByte: Reads a byte of data from emulated memory at the specified
   address.
   - ReadWord: Reads a 16-bit word of data from emulated memory at the
   specified address.
   - WriteByte: Writes a byte of data to emulated memory at the specified
   address.
   - WriteWord: Writes a 16-bit word of data to emulated memory at the
   specified address.

   For more information about the instructions and addressing modes, refer to
   Instructions.MD.
*/

// Initializes memory to 65 Kilobytes (64 * 1024 Bytes).
void
initializeMem6502 (MEM6502 *memory)
{
  memory->Data = (Byte *)malloc (MAX_MEM);
  if (memory->Data == NULL)
    {
      exit (EXIT_FAILURE); // Exit if memory allocation fails.
    }

  // Initialize memory with zeros.
  for (DWord i = 0; i < MAX_MEM; i++)
    {
      memory->Data[i] = 0;
    }
}

// Frees 65 Kilobytes of RAM.
void
freeMem6502 (MEM6502 *memory)
{
  free (memory->Data);
  memory->Data
      = NULL; // Optional: define data as null after freeing the memory.
}

// Write a 16-bit word of data to emulated memory at the specified address.
void
WriteWord (Word *Cycles, Word Value, MEM6502 *mem, DWord Address)
{
  // Write the low byte.
  mem->Data[Address] = Value & 0xFF;

  // Write the high byte.
  mem->Data[Address + 1] = (Value >> 8);

  // Adjust the cycle count.
  (*Cycles) -= 2;
}

// Read a byte of data from emulated memory at the specified address.
Byte
ReadByte (Word *Cycles, Word Address, const MEM6502 *memory)
{
  // Read the byte from memory.
  Byte Data = memory->Data[Address];

  // Adjust the cycle count.
  (*Cycles)--;

  return Data;
}

// Read a 16-bit word of data from emulated memory at the specified address.
Word
ReadWord (Word *Cycles, Word Address, const MEM6502 *memory)
{
  // Read the low byte.
  Byte LoByte = ReadByte (Cycles, Address, memory);

  // Read the high byte.
  Byte HiByte = ReadByte (Cycles, Address + 1, memory);

  // Combine the bytes into a 16-bit word.
  return LoByte | (HiByte << 8);
}

// Write a byte of data to emulated memory at the specified address.
void
WriteByte (Word *Cycles, Word Value, MEM6502 *mem, DWord Address)
{
  // Write the byte to memory.
  mem->Data[Address] = Value;

  // Adjust the cycle count.
  (*Cycles)--;
}
