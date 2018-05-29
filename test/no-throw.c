#include "../hedley.h"

HEDLEY_INLINE
static int test_inline(int a, int b) {
  return a * b;
}

HEDLEY_ALWAYS_INLINE
static int test_always_inline(int a, int b) {
  return a * b;
}

HEDLEY_NEVER_INLINE
static int test_never_inline(int a, int b) {
  return a * b;
}

int main(void) {
  return
    test_inline(
        test_always_inline(1, 2),
        test_never_inline(3, 4));
}
