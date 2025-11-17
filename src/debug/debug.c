#include "debug.h"
#include "cpu6502.h"
#include <stdio.h>

DebugLevel DEBUG_LEVEL = DEBUG_OFF;

void debug_set_level(DebugLevel level) {
    DEBUG_LEVEL = level;
}

void debug_opcode(Word pc, Byte opcode) {
    if (DEBUG_LEVEL >= DEBUG_OPCODES)
        printf("[OP ] PC=%04X OP=%02X\n", pc, opcode);
}

void debug_cpu_state(const CPU6502 *cpu) {
    if (DEBUG_LEVEL >= DEBUG_CPU) {
        printf("[CPU] A=%02X X=%02X Y=%02X SP=%02X PC=%04X  "
               "N:%d V:%d B:%d D:%d I:%d Z:%d C:%d\n",
            cpu->A, cpu->X, cpu->Y, cpu->SP, cpu->PC,
            cpu->Flag.N, cpu->Flag.V, cpu->Flag.B,
            cpu->Flag.D, cpu->Flag.I, cpu->Flag.Z, cpu->Flag.C);
    }
}

void debug_mem_read(Word addr, Byte val) {
    if (DEBUG_LEVEL >= DEBUG_MEMORY)
        printf("[READ ] %04X => %02X\n", addr, val);
}

void debug_mem_write(Word addr, Byte val) {
    if (DEBUG_LEVEL >= DEBUG_MEMORY)
        printf("[WRITE] %04X <= %02X\n", addr, val);
}
