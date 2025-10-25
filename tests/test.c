#include "instructions/ld/test_ld.h"
#include "instructions/rt/test_rt.h"
#include "instructions/st/test_st.h"
#include "test_template.h"

int
main (void)
{
  UNITY_BEGIN ();

  test_all_rt ();

  return UNITY_END ();
}
