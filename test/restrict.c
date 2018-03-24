#include "../hedley.h"

static void foo(const char* HEDLEY_RESTRICT a, const char* HEDLEY_RESTRICT b) {
  (void) a;
  (void) b;
}

int main (void) {
  foo("one", "two");

  return 0;
}
