#include "../hedley.h"

#include <stdlib.h>

#if defined(HEDLEY_PGI_VERSION)
#  pragma diag_remark 1622
#elif HEDLEY_SUNPRO_VERSION_CHECK(5,15,0) && defined(__cplusplus)
#  pragma error_messages(off,nonnullarg)
#elif HEDLEY_GNUC_HAS_WARNING("-Wnonnull",3,3,0)
#  pragma GCC diagnostic warning "-Wnonnull"
#endif

HEDLEY_NON_NULL(1)
static const char* non_null(const char* msg) {
  return msg;
}

int main (void) {
  non_null(NULL);

  return 0;
}
