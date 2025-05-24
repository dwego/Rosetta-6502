#include "instructions/ld/test_ld.h"
#include "test_template.h"

int
main (void)
{
  UNITY_BEGIN ();

  test_all_lda ();
  test_all_ldx ();
  test_all_ldy ();

  return UNITY_END ();
}
