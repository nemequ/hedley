#include "../hedley.h"

#if !defined(HEDLEYX_FEATURE_STATEMENT_EXPRESSIONS)
#if \
  HEDLEY_GNUC_VERSION_CHECK(2,95,0) || \
  HEDLEY_TINYC_VERSION_CHECK(0,9,26) || \
  HEDLEY_INTEL_VERSION_CHECK(9,0,0) || \
  HEDLEY_PGI_VERSION_CHECK(18,10,0) || \
  HEDLEY_SUNPRO_VERSION_CHECK(5,12,0) || \
  HEDLEY_IBM_VERSION_CHECK(11,1,0)
#  define HEDLEYX_FEATURE_STATEMENT_EXPRESSIONS 1
#elif \
  defined(HEDLEY_MSVC_VERSION) || \
  HEDLEY_PELLES_VERSION_CHECK(9,0,0) || \
  HEDLEY_DMC_VERSION_CHECK(8,5,7) || \
  1
#endif
#endif

#include <stdio.h>

int main(void) {
#if defined(HEDLEYX_FEATURE_STATEMENT_EXPRESSIONS)
  int a = 42;
  int b = 100;
  int x = (__extension__ ({
	int tmp_ = a + b;
	tmp_;
      }));

  return x;
#else
  return 0;
#endif
}
