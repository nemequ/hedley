#include "../hedley.h"

static void f(HEDLEY_NO_ESCAPE int *p) {
  *p += 1;
}

int main(void) {
  int x = 0;
  f(&x);
  return 0;
}
