#include "../hedley.h"

static int foo(int x) {
  HEDLEY_ASSUME(x < 10 && x > 0);

  return x % 10;
}

int main(void) {
  return foo(5);
}
