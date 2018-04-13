#include "../hedley.h"

HEDLEY_CONST
HEDLEY_INLINE
static int test_const(int a, int b) {
  return a * b;
}

int main(void) {
  return test_const(9, 9);
}
