#ifndef TEST_RT
#define TEST_RT

#include "cpu_exec.h"
#include "rt_helpers.h"

/* ----------------------------------------------------------
 * Wrappers para RT – necessários pois Unity exige funções void(void)
 * -------------------------------------------------------- */

void
test_tax (void)
{
  test_rt (&cpu.A, &cpu.X, INS_TAX);
}

void
test_tay (void)
{
  test_rt (&cpu.A, &cpu.Y, INS_TAY);
}

void
test_txa (void)
{
  test_rt (&cpu.X, &cpu.A, INS_TXA);
}

void
test_tya (void)
{
  test_rt (&cpu.Y, &cpu.A, INS_TYA);
}

void
test_tsx (void)
{
  test_rt (&cpu.SP, &cpu.X, INS_TSX);
}

void
test_txs (void)
{
  test_rt (&cpu.X, &cpu.SP, INS_TXS);
}

void
test_all_rt (void)
{
  RUN_TEST (test_tax);
  RUN_TEST (test_tay);
  RUN_TEST (test_txa);
  RUN_TEST (test_tya);
  RUN_TEST (test_tsx);
  RUN_TEST (test_txs);
}

#endif
