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

void set_reset_vector(MEM6502 *memory, Word start_addr)
{
    memory->Data[0xFFFC] = (Byte)(start_addr & 0xFF);
    memory->Data[0xFFFD] = (Byte)((start_addr >> 8) & 0xFF);

    // NMI and IRQ pointing to the same RESET address
    memory->Data[0xFFFA] = memory->Data[0xFFFC];
    memory->Data[0xFFFB] = memory->Data[0xFFFD];
    memory->Data[0xFFFE] = memory->Data[0xFFFC];
    memory->Data[0xFFFF] = memory->Data[0xFFFD];
}
