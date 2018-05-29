#include "../hedley.h"

#include <stdio.h>
#include <stdarg.h>

#if HEDLEY_HAS_WARNING("-Wnonnull")
#  pragma clang diagnostic warning "-Wformat"
#elif defined(HEDLEY_TI_VERSION)
#  pragma diag_remark 183
#elif defined(HEDLEY_PGI_VERSION) && defined(__cplusplus)
#  pragma diag_remark 181
#elif defined(HEDLEY_GCC_VERSION)
#  pragma GCC diagnostic warning "-Wformat"
#endif

HEDLEY_PRINTF_FORMAT(1,2)
static void print_msg(const char* msg, ...) {
  va_list ap;
  va_start(ap, msg);

  vfprintf(stderr, msg, ap);

  va_end(ap);
}

int main (void) {
  print_msg("mismatch %ld\n", 0.0);

  return 0;
}
