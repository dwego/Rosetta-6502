#include "loader.h"
#include <stdio.h>

bool load_binary_to_memory(MEM6502 *memory, const char *filename, Word start_addr)
{
    if (!memory || !filename)
        return false;

    FILE *f = fopen(filename, "rb");
    if (!f) {
        perror("Error opening binary file");
        return false;
    }

    Word addr = start_addr;
    int byte;

    while ((byte = fgetc(f)) != EOF && addr < MAX_MEM) {
        memory->Data[addr++] = (Byte)byte;
    }

    fclose(f);
    return true;
}

// Sets the RESET, NMI, and IRQ vectors to point to the specified start address
void set_reset_vector(MEM6502 *memory, Word start_addr)
{
    memory->Data[0xFFFC] = (Byte)(start_addr & 0xFF);
    memory->Data[0xFFFD] = (Byte)((start_addr >> 8) & 0xFF);
}

