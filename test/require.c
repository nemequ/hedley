#include "../hedley.h"

#if defined(_MSC_VER)
  HEDLEY_DIAGNOSTIC_PUSH
  #pragma warning(disable:4668)
  #include <limits.h>
  HEDLEY_DIAGNOSTIC_POP
#else
  #include <limits.h>
#endif

static int add(int a, int b)
  HEDLEY_REQUIRE_MSG((a < b), "a must be less than b")
{
  return a + b;
}

int main(void) {
  return add(2, 3);
}
