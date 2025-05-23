/* tests/test_template.h */
#ifndef TEST_TEMPLATE_H
#define TEST_TEMPLATE_H

#include "../include/cpu_exec.h"
#include "../unity/Unity/src/unity.h"

extern CPU6502 cpu;
extern Bus6502 bus;
extern MEM6502 mem;
extern Word cycles;

void load_and_run (const Byte *prog, size_t len, Word expected_cycles);

#endif /* TEST_TEMPLATE_H */
