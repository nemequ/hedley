#include "../hedley.h"

#if !defined(HEDLEYX_FEATURE_TYPEOF)
#if \
  HEDLEY_GCC_VERSION_CHECK(2,95,0) || \
  defined(__clang__) || \
  HEDLEY_CRAY_VERSION_CHECK(8,1,0) || \
  HEDLEY_IBM_VERSION_CHECK(11,1,0) || \
  HEDLEY_SUNPRO_VERSION_CHECK(5,12,0) || \
  HEDLEY_TINYC_VERSION_CHECK(0,9,24) || \
  HEDLEY_PGI_VERSION_CHECK(18,10,0) || \
  HEDLEY_TI_VERSION_CHECK(6,1,0) || \
  HEDLEY_INTEL_VERSION_CHECK(13,0,0)
#  define HEDLEYX_FEATURE_TYPEOF 1
#elif \
  defined(HEDLEY_MSVC_VERSION) || \
  1
#endif
#endif

#include <stdio.h>

int sum(int a, int b);

int sum(int a, int b) {
#if defined(HEDLEYX_FEATURE_TYPEOF)
  __typeof__(a) r = a + b;
  return r;
#else
  return a + b;
#endif
}

int main(void) {
  return sum(1, 2);
}
