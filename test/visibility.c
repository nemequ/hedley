#include "../hedley.h"

#if defined(HEDLEY_INTEL_VERSION)
#  pragma warning(disable:1419)
#endif

HEDLEY_PUBLIC void test_public(void);
HEDLEY_PRIVATE void test_private(void);

HEDLEY_PUBLIC
void
test_public(void) { }

HEDLEY_PRIVATE
void
test_private(void) { }

int main(void) {
  test_public();
  test_private();

  return 0;
}
