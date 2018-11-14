#include "../hedley.h"

#include <limits.h>

static int add(int a, int b)
  HEDLEY_REQUIRE_MSG((a < b), "a must be less than b")
{
  return a + b;
}

int main(void) {
  return add(2, 3);
}
