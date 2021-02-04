#include "../hedley.h"

#if defined(_MSC_VER)
  HEDLEY_DIAGNOSTIC_PUSH
  #pragma warning(disable:4255 4668)
  #include <stdlib.h>
  HEDLEY_DIAGNOSTIC_POP
#else
  #include <stdlib.h>
#endif

#if HEDLEY_PGI_VERSION_CHECK(20,7,0)
#  pragma diag_remark 1622,1623
#elif defined(HEDLEY_PGI_VERSION)
#  pragma diag_remark 1622
#elif HEDLEY_SUNPRO_VERSION_CHECK(5,15,0) && defined(__cplusplus)
#  pragma error_messages(off,nonnullarg)
#elif HEDLEY_GCC_HAS_WARNING("-Wnonnull",3,3,0)
#  pragma GCC diagnostic warning "-Wnonnull"
#elif HEDLEY_INTEL_VERSION_CHECK(19,0,0)
#  pragma warning(disable:2193)
#elif HEDLEY_MCST_LCC_VERSION_CHECK(1,25,10)
#  pragma diag_suppress 1622
#endif

HEDLEY_NON_NULL(1)
static const char* non_null(const char* msg) {
  return msg;
}

int main (void) {
  non_null(HEDLEY_STATIC_CAST(const char*, HEDLEY_NULL));

  return 0;
}
