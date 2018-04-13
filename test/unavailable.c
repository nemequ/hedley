#include "../hedley.h"

HEDLEY_UNAVAILABLE(3.14)
static void
test_unavailable(void) { }

int main(void) {
  test_unavailable();

  return 0;
}
