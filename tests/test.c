#include "instructions/ld/test_ld.h"
#include "instructions/st/test_st.h"
#include "test_template.h"

int
main (void)
{
  UNITY_BEGIN ();

  test_all_sta ();
  test_all_stx ();
  test_all_sty ();

  return UNITY_END ();
}
