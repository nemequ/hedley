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
#elif defined(HEDLEY_PGI_VERSION)
#  pragma diag_remark 1650
#elif defined(HEDLEY_GNUC_VERSION)
#  pragma GCC diagnostic warning "-Wunused-result"
#endif

HEDLEY_WARN_UNUSED_RESULT
static int test_unused_result(void) {
  return 1729;
}

int main(void) {
  test_unused_result();

  if (test_unused_result() != 1729)
    return 1;

  return 0;
}
