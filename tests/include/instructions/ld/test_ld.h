#ifndef TEST_LDA
#define TEST_LDA

#include "cpu_exec.h"
#include "ld_helpers.h"

/* ----------------------------------------------------------
 * Wrappers para LDA – necessários pois Unity exige funções void(void)
 * -------------------------------------------------------- */

void
test_lda_immediate (void)
{
  test_ld_immediate (&cpu.A, INS_LDA_IM);
}
void
test_lda_zp (void)
{
  test_ld_zp (&cpu.A, INS_LDA_ZP);
}
void
test_lda_zpx (void)
{
  test_ld_zpx (&cpu.A, INS_LDA_ZPX);
}

void
test_lda_abs (void)
{
  test_ld_abs (&cpu.A, INS_LDA_ABS);
}
void
test_lda_absx (void)
{
  test_ld_absx (&cpu.A, INS_LDA_ABSX);
}
void
test_lda_absy (void)
{
  test_ld_absy (&cpu.A, INS_LDA_ABSY);
}

void
test_all_lda (void)
{
  RUN_TEST (test_lda_immediate);
  RUN_TEST (test_lda_zp);
  RUN_TEST (test_lda_zpx);
  RUN_TEST (test_lda_abs);
  RUN_TEST (test_lda_absx);
  RUN_TEST (test_lda_absy);
}

/*
 *  LDX
 */

void
test_ldx_immediate (void)
{
  test_ld_immediate (&cpu.X, INS_LDX_IM);
}
void
test_ldx_zp (void)
{
  test_ld_zp (&cpu.X, INS_LDX_ZP);
}

void
test_ldx_zpy (void)
{
  test_ld_zpy (&cpu.X, INS_LDX_ZPY);
}

void
test_ldx_abs (void)
{
  test_ld_abs (&cpu.X, INS_LDX_ABS);
}

void
test_ldx_absy (void)
{
  test_ld_absy (&cpu.X, INS_LDX_ABSY);
}

void
test_all_ldx (void)
{
  RUN_TEST (test_ldx_immediate);
  RUN_TEST (test_ldx_zp);
  RUN_TEST (test_ldx_zpy);

  RUN_TEST (test_ldx_abs);
  RUN_TEST (test_ldx_absy);
}

/*
 *  LDY
 */

void
test_ldy_immediate (void)
{
  test_ld_immediate (&cpu.Y, INS_LDY_IM);
}
void
test_ldy_zp (void)
{
  test_ld_zp (&cpu.Y, INS_LDY_ZP);
}

void
test_ldy_zpx (void)
{
  test_ld_zpx (&cpu.Y, INS_LDY_ZPX);
}

void
test_ldy_abs (void)
{
  test_ld_abs (&cpu.Y, INS_LDY_ABS);
}

void
test_ldy_absx (void)
{
  test_ld_absx (&cpu.Y, INS_LDY_ABSX);
}

void
test_all_ldy (void)
{
  RUN_TEST (test_ldy_immediate);
  RUN_TEST (test_ldy_zp);
  RUN_TEST (test_ldy_zpx);

  RUN_TEST (test_ldy_abs);
  RUN_TEST (test_ldy_absx);
}

#endif
