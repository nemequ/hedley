#include "../hedley.h"

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
