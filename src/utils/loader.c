#include "loader.h"
#include <stdio.h>

bool
load_binary_to_memory(MEM6502 *memory,
                      const char *filename,
                      Word start_addr)
{
    if (memory == NULL || filename == NULL)
        return false;

    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        perror("Error opening binary file");
        return false;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        perror("Error seeking binary file");
        fclose(file);
        return false;
    }

    long file_size = ftell(file);

    if (file_size < 0) {
        perror("Error getting binary size");
        fclose(file);
        return false;
    }

    /*
     * Come back before read the content.
     */
    if (fseek(file, 0, SEEK_SET) != 0) {
        perror("Error rewinding binary file");
        fclose(file);
        return false;
    }

    size_t binary_size = (size_t)file_size;
    size_t available_memory = (size_t)MAX_MEM - (size_t)start_addr;

    if (binary_size > available_memory) {
        fprintf(
            stderr,
            "Binary does not fit in memory:\n"
            "  binary size: %zu bytes\n"
            "  load address: $%04X\n"
            "  available: %zu bytes\n",
            binary_size,
            start_addr,
            available_memory
        );

        fclose(file);
        return false;
    }

    size_t bytes_read = fread(
        &memory->Data[start_addr],
        sizeof(Byte),
        binary_size,
        file
    );

    if (bytes_read != binary_size) {
        fprintf(
            stderr,
            "Failed to read complete binary: expected %zu bytes, read %zu\n",
            binary_size,
            bytes_read
        );

        fclose(file);
        return false;
    }

    if (fclose(file) != 0) {
        perror("Error closing binary file");
        return false;
    }

    return true;
}

// Sets the RESET, NMI, and IRQ vectors to point to the specified start address
void set_reset_vector(MEM6502 *memory, Word start_addr)
{
    memory->Data[0xFFFC] = (Byte)(start_addr & 0xFF);
    memory->Data[0xFFFD] = (Byte)((start_addr >> 8) & 0xFF);
}

