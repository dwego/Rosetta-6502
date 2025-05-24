#ifndef TEST_STA
#define TEST_STA

#include "cpu_exec.h"
#include "st_helpers.h"

/* ----------------------------------------------------------
 * Wrappers para STA – necessários pois Unity exige funções void(void)
 * -------------------------------------------------------- */

void
test_sta_zp (void)
{
  test_st_zp (&cpu.A, INS_STA_ZP);
}
void
test_sta_zpx (void)
{
  test_st_zpx (&cpu.A, INS_STA_ZPX);
}

void
test_sta_abs (void)
{
  test_st_abs (&cpu.A, INS_STA_ABS);
}
void
test_sta_absx (void)
{
  test_st_absx (&cpu.A, INS_STA_ABSX);
}
void
test_sta_absy (void)
{
  test_st_absy (&cpu.A, INS_STA_ABSY);
}

void
test_all_sta (void)
{

  RUN_TEST (test_sta_zp);
  RUN_TEST (test_sta_zpx);
  RUN_TEST (test_sta_abs);
  RUN_TEST (test_sta_absx);
  RUN_TEST (test_sta_absy);
}

/*
 *  STX
 */

void
test_stx_zp (void)
{
  test_st_zp (&cpu.X, INS_STX_ZP);
}

void
test_stx_zpy (void)
{
  test_st_zpy (&cpu.X, INS_STX_ZPY);
}

void
test_stx_abs (void)
{
  test_st_abs (&cpu.X, INS_STX_ABS);
}

void
test_all_stx (void)
{

  RUN_TEST (test_stx_zp);
  RUN_TEST (test_stx_zpy);

  RUN_TEST (test_stx_abs);
}

/*
 *  STY
 */

void
test_sty_zp (void)
{
  test_st_zp (&cpu.Y, INS_STY_ZP);
}

void
test_sty_zpx (void)
{
  test_st_zpx (&cpu.Y, INS_STY_ZPX);
}

void
test_sty_abs (void)
{
  test_st_abs (&cpu.Y, INS_STY_ABS);
}

void
test_all_sty (void)
{

  RUN_TEST (test_sty_zp);
  RUN_TEST (test_sty_zpx);

  RUN_TEST (test_sty_abs);
}

#endif
