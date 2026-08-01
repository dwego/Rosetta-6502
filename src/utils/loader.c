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

/*
   set_vector - Store a 16-bit target in a processor vector.

   The 6502 reads vectors in little-endian order. The target low byte is stored
   at vector, and the target high byte is stored at vector + 1.
*/

void
set_vector (MEM6502 *memory, Word vector, Word target)
{
  if (memory == NULL || memory->Data == NULL)
    return;

  memory->Data[vector] = (Byte)(target & 0x00FF);
  memory->Data[(Word)(vector + 1)]
      = (Byte)((target >> 8) & 0x00FF);
}

// Sets the RESET, NMI, and IRQ vectors to point to the specified start address
void set_reset_vector(MEM6502 *memory, Word target)
{
    set_vector (memory, RESET_VECTOR, target);
}

/*
   set_nmi_vector - Configure the address loaded when NMI is accepted.
*/
void
set_nmi_vector (MEM6502 *memory, Word target)
{
  set_vector (memory, NMI_VECTOR, target);
}

/*
   set_irq_vector - Configure the shared IRQ and BRK handler address.
*/
void
set_irq_vector (MEM6502 *memory, Word target)
{
  set_vector (memory, IRQ_VECTOR, target);
}
