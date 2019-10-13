#include "../hedley.h"

#if HEDLEY_HAS_WARNING("-Wcovered-switch-default")
#  pragma clang diagnostic warning "-Wcovered-switch-default"
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

  HEDLEY_UNREACHABLE_RETURN(0);
}

int main(void) {
  test_unreachable(FOO_BAR);

  return 0;
}
