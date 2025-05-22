#ifndef CPU_EXEC_H
#define CPU_EXEC_H

#include "../CPU/6502/Instructions/instructions.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

void run_cpu_instruction(Word *Cycles, MEM6502 *memory, CPU6502 *cpu);

#endif // CPU_EXEC_H

