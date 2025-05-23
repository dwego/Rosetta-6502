#include "ld_helpers.h"
#include "test_template.h"

void
setUp (void)
{
  open_log ("../cpu_log.txt");
  initializeMem6502 (&mem);
  mem.Data[0xFFFC] = 0x00;
  mem.Data[0xFFFD] = 0x80;
  resetCPU (&cpu, &mem);
  cycles = 20;
}

void
tearDown (void)
{
  freeMem6502 (&mem);
  close_log ();
}

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

/* ----------------------------------------------------------
 * Runner
 * ---------------------------------------------------------- */

int
main (void)
{
  UNITY_BEGIN ();

  RUN_TEST (test_lda_immediate);
  RUN_TEST (test_lda_zp);
  RUN_TEST (test_lda_zpx);
  RUN_TEST (test_lda_abs);
  RUN_TEST (test_lda_absx);
  RUN_TEST (test_lda_absy);

  return UNITY_END ();
}
