#include "../hedley.h"

static int x[4096] = { 0 };

int main(void) {
  HEDLEY_PREFETCH(x, 0, 0);

  return x[0];
}
