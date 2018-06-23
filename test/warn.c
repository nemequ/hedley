#include "../hedley.h"

#if defined(HEDLEY_INTEL_VERSION)
#  pragma warning(disable:1028)
#elif defined(HEDLEY_PGI_VERSION)
#  pragma diag_remark 1105
#endif

HEDLEY_WARNING("I'm a warning")

int main(void) {
  return 0;
}
