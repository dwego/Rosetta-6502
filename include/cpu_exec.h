#ifndef CPU_EXEC_H
#define CPU_EXEC_H

#include "../src/cpu/Instructions/instructions.h"
#include "bus.h"
#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"
#include <stdbool.h>

bool run_cpu_instruction (Bus6502 *bus, MEM6502 *memory,
                          CPU6502 *cpu);

#endif // CPU_EXEC_H
