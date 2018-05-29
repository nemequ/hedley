#include "../hedley.h"

static int* b;

HEDLEY_PURE
static int taxi(int a) {
  return
    (a * a * a) +
    (*b * *b * *b);
}

int main(void) {
  *b = 10;

  return taxi(9);
}
