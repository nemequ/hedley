#include "../hedley.h"

#if HEDLEY_TI_VERSION_CHECK(8,0,0)
#  pragma diag_suppress 994
#elif HEDLEY_IAR_VERSION_CHECK(8,0,0)
#  pragma diag_suppress=Pe940
#endif

enum Foo {
  FOO_BAR,
  FOO_BAZ,
  FOO_QUX,
  FOO_QUUX
};

static int test_unreachable(enum Foo code) {
  switch (code) {
  case FOO_BAR:
  case FOO_BAZ:
  case FOO_QUX:
    return 0;
  case FOO_QUUX:
  default:
    HEDLEY_UNREACHABLE();
  }
}

int main(void) {
  test_unreachable(FOO_BAR);

  return 0;
}
