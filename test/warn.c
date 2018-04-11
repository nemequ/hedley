#include "../hedley.h"

#if defined(HEDLEY_INTEL_VERSION)
#  pragma warning(disable:1028)
#endif

HEDLEY_WARNING("I'm a warning")

int main(void) {
  return 0;
}
