#include "../hedley.h"

#if HEDLEY_HAS_WARNING("-Wsentinel")
#  pragma clang diagnostic warning "-Wsentinel"
#elif defined(HEDLEY_INTEL_VERSION)
#  pragma warning(disable:1881)
#elif defined(HEDLEY_PGI_VERSION)
#  pragma diag_remark 1546
#elif defined(HEDLEY_GNUC_VERSION)
#  pragma GCC diagnostic warning "-Wformat"
#endif

#include <assert.h>

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
