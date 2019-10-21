#include "../hedley.h"

#if defined(_MSC_VER)
  HEDLEY_DIAGNOSTIC_PUSH
  #pragma warning(disable:4255 4668)
  #include <stdio.h>
  HEDLEY_DIAGNOSTIC_POP
#else
#  include <stdio.h>
#endif

#include <stdarg.h>

#if HEDLEY_HAS_WARNING("-Wformat")
#  pragma clang diagnostic warning "-Wformat"
#elif defined(HEDLEY_TI_VERSION)
#  pragma diag_remark 183
#elif defined(HEDLEY_PGI_VERSION) && defined(__cplusplus)
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
