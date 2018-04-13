#include "../hedley.h"

#include <assert.h>

static void foo(const char* HEDLEY_RESTRICT a, const char* HEDLEY_RESTRICT b) {
  assert(a != b);
}

int main (void) {
  foo("one", "two");

  return 0;
}
