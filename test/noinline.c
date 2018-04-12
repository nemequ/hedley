#include "../hedley.h"

#if defined(HEDLEY_INTEL_VERSION)
#  pragma warning(disable:981)
#endif

HEDLEY_NEVER_INLINE
static
int cube(int v) {
  return v * v * v;
}

int main(void) {
  return cube(9) + cube(10);
}
