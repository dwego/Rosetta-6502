#ifndef TEST_CONFIG_H
#define TEST_CONFIG_H

#include "../../libs/unity/src/unity.h"
#include "cpu_exec.h"

extern CPU6502 cpu;
extern Bus6502 bus;
extern MEM6502 mem;
extern Word cycles;

void load_and_run (const Byte *prog, size_t len, Word expected_cycles);

#endif
