#include "../hedley.h"

HEDLEY_CONST
HEDLEY_INLINE
static int test_const(int a, int b) {
  return a * b;
}

int main(int argc, char* argv[HEDLEY_ARRAY_PARAM(argc)]) {
  (void) argc;
  (void) argv;

  return test_const(9, 9);
}
