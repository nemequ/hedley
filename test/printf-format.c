#include "../hedley.h"

#include <stdio.h>
#include <stdarg.h>

#if HEDLEY_HAS_WARNING("-Wformat")
#  pragma clang diagnostic warning "-Wformat"
#elif \
    defined(HEDLEY_TI_VERSION) || \
    defined(HEDLEY_TI_CL6X_VERSION) || \
    defined(HEDLEY_TI_CL7X_VERSION) || \
    defined(HEDLEY_TI_CLPRU_VERSION)
#  pragma diag_remark 183
#elif (defined(HEDLEY_PGI_VERSION) && defined(__cplusplus)) || HEDLEY_MCST_LCC_VERSION_CHECK(1,25,10)
#  pragma diag_remark 181
#elif defined(HEDLEY_GCC_VERSION)
#  pragma GCC diagnostic warning "-Wformat"
#elif defined(HEDLEY_INTEL_VERSION)
#  pragma warning(disable:181)
#endif

HEDLEY_PRINTF_FORMAT(1,2)
static void print_msg(const char* msg, ...) {
  char buf[128];
  va_list ap;

  va_start(ap, msg);

  vsnprintf(buf, sizeof(buf), msg, ap);

  va_end(ap);
}

int main (void) {
  print_msg("mismatch %ld\n", 0.0);

  return 0;
}
