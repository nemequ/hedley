#include "../hedley.h"

#if defined(HEDLEY_TI_VERSION)
#  pragma diag_remark 190
#endif

enum Foo {
  FOO_BAR = 1 << 0,
  FOO_BAZ = 1 << 1,
  FOO_QUX = 1 << 2
} HEDLEY_FLAGS;

int main(void) {
  const enum Foo foo = HEDLEY_CPP_CAST(enum Foo, FOO_BAR | FOO_BAZ);

  return (int) foo;
}
