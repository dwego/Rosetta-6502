#ifndef LOADER_H
#define LOADER_H

#include "config.h"
#include "mem6502.h"

bool load_binary_to_memory(MEM6502 *memory, const char *filename, Word start_addr);
void set_reset_vector(MEM6502 *memory, Word start_addr);

#endif