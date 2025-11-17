#ifndef DEBUG_H
#define DEBUG_H

#include "bus.h"

struct CPU6502;

typedef enum {
    DEBUG_OFF = 0,
    DEBUG_OPCODES,
    DEBUG_CPU,
    DEBUG_TRACE,
    DEBUG_MEMORY
} DebugLevel;

extern DebugLevel DEBUG_LEVEL;

void debug_set_level(DebugLevel level);
void debug_opcode(Word pc, Byte opcode);
void debug_cpu_state(const struct CPU6502 *cpu);
void debug_mem_read(Word addr, Byte val);
void debug_mem_write(Word addr, Byte val);

#endif
