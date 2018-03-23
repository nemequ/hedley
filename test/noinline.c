#include "../hedley.h"

HEDLEY_NEVER_INLINE
static
int cube(int v) {
  return v * v * v;
}

int main(void) {
  return cube(9) + cube(10);
}
