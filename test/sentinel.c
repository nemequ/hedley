#include "../hedley.h"

#if HEDLEY_HAS_WARNING("-Wsentinel")
#  pragma clang diagnostic warning "-Wsentinel"
#elif defined(HEDLEY_INTEL_VERSION)
#  pragma warning(disable:1881)
#elif HEDLEY_PGI_VERSION_CHECK(20,7,0)
#  pragma diag_remark 1546,1547
#elif defined(HEDLEY_PGI_VERSION) || HEDLEY_MCST_LCC_VERSION_CHECK(1,25,10)
#  pragma diag_remark 1546
#elif defined(HEDLEY_GNUC_VERSION)
#  pragma GCC diagnostic warning "-Wformat"
#endif

#if defined(_MSC_VER)
  HEDLEY_DIAGNOSTIC_PUSH
  #pragma warning(disable:4668)
  #include <assert.h>
  HEDLEY_DIAGNOSTIC_POP
#else
  #include <assert.h>
#endif

HEDLEY_SENTINEL(0)
static int test_sentinel(void* ptr, ...) {
  assert(ptr == HEDLEY_NULL);

  return 42;
}

int main(void) {
  test_sentinel(HEDLEY_NULL, 1, HEDLEY_NULL);
  test_sentinel(HEDLEY_NULL, 1);

  return 0;
}
