#include "../hedley.h"

#if HEDLEY_HAS_WARNING("-Wunused-result")
#  pragma clang diagnostic warning "-Wunused-result"
#elif defined(HEDLEY_INTEL_VERSION)
#  pragma warning(disable:2218)
#elif HEDLEY_SUNPRO_VERSION_CHECK(5,15,0) && defined(__cplusplus)
#  pragma error_messages(off,unusedresult)
#elif \
    defined(HEDLEY_TI_VERSION) || \
    defined(HEDLEY_TI_CL6X_VERSION) || \
    defined(HEDLEY_TI_CL7X_VERSION) || \
    defined(HEDLEY_TI_CLPRU_VERSION)
#  pragma diag_remark 1490
#elif HEDLEY_PGI_VERSION_CHECK(20,7,0)
#  pragma diag_remark 1650,1651
#elif defined(HEDLEY_PGI_VERSION) || HEDLEY_MCST_LCC_VERSION_CHECK(1,25,10)
#  pragma diag_remark 1650
#elif defined(HEDLEY_IAR_VERSION)
#  pragma diag_suppress=Pe2809
#elif defined(HEDLEY_GNUC_VERSION)
#  pragma GCC diagnostic warning "-Wunused-result"
#endif

HEDLEY_WARN_UNUSED_RESULT
static int test_unused_result(void) {
  return 1729;
}

HEDLEY_WARN_UNUSED_RESULT_MSG("Foo")
static int test_unused_result_msg(void) {
  return 1701;
}

int main(void) {
  test_unused_result();
  test_unused_result_msg();

  if (test_unused_result() != 1729)
    return 1;
  if (test_unused_result_msg() != 1701)
    return 1;

  return 0;
}
