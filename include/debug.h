#ifndef DEBUG_H
#define DEBUG_H

#include "cpu6502.h"
#include "bus.h"
#include <stdbool.h>

typedef enum {
    DEBUG_OFF = 0,
    DEBUG_OPCODES,    // print opcodes only
    DEBUG_CPU,        // CPU registers per instruction
    DEBUG_TRACE,      // detailed: PC, cycles, flags, opcode
    DEBUG_MEMORY      // full memory read/write events
} DebugLevel;

void debug_set_level(DebugLevel level);
void debug_opcode(Word pc, Byte opcode);
void debug_cpu_state(const CPU6502 *cpu);
void debug_mem_read(Word addr, Byte val);
void debug_mem_write(Word addr, Byte val);

extern DebugLevel DEBUG_LEVEL;

#endif
