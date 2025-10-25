#ifndef RT_HELPERS
#define RT_HELPERS

/*
 * Testes da instruções RT (6502) – modos: Immediate, ZP, ZP,X
 */

#include "test_config.h"

/* ----------------------------------------------------------
 * Helpers
 * ---------------------------------------------------------- */

/* ----------------------------------------------------------
 * Casos-de-teste genéricos
 * ---------------------------------------------------------- */

typedef struct
{
  const char *label;
  Byte value;
  bool expectZ;
  bool expectN;
} rt_case_t;

extern const rt_case_t rt_cases[];
#define N_CASES (3)

/* ----------------------------------------------------------
 * Immediate ($A9)
 * ---------------------------------------------------------- */
void test_rt (Byte *reg_input, Byte *reg_output, Instruction ins);

#endif
