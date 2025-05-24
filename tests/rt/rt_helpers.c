/*
 * Testes da instrução rt (6502)
 */

#include "instructions/rt/rt_helpers.h"
#include "config.h"
#include "test_config.h"

const rt_case_t rt_cases[] = { { "positive", 0x10, false, false },
                               { "zero", 0x00, true, false },
                               { "negative", 0x80, false, true } };

/* ----------------------------------------------------------
 * Helpers
 * ---------------------------------------------------------- */
void
test_rt (Byte *reg_input, Byte *reg_output, Instruction ins)
{
  for (size_t i = 0; i < N_CASES; ++i)
    {
      *reg_input = rt_cases[i].value;

      const Byte prog[] = { ins };
      load_and_run (prog, sizeof prog, 2); /* rt = 4 ciclos     */

      char msg[32];
      sprintf (msg, "RT %s", rt_cases[i].label);

      TEST_ASSERT_EQUAL_UINT8_MESSAGE (*reg_input, *reg_output, msg);
      if (reg_output != (Byte *)&cpu.SP)
        {

          TEST_ASSERT_EQUAL_MESSAGE (rt_cases[i].expectZ, cpu.Flag.Z,
                                     "Z flag");
          TEST_ASSERT_EQUAL_MESSAGE (rt_cases[i].expectN, cpu.Flag.N,
                                     "N flag");
        }
      resetCPU (&cpu, &mem);
    }
}
