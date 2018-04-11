#include "../hedley.h"

HEDLEY_PURE
static int test_pure(int a, int b) {
  return a * b;
}

int main(void) {
  return test_pure(9, 9);
}
