#include "../hedley.h"

#if HEDLEY_IAR_VERSION_CHECK(8,0,0)
#  pragma diag_suppress=Pe381
#endif

HEDLEY_STATIC_ASSERT(sizeof(char) == 1, "char must be one byte");

int main(void) {
  return 0;
}
