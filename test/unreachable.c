#include "../hedley.h"

#if defined(__has_warning)
#  if __has_warning("-Wswitch-enum")
#    pragma GCC diagnostic warning "-Wswitch-enum"
#  endif
#elif HEDLEY_GCC_VERSION_CHECK(4,5,0)
#    pragma GCC diagnostic warning "-Wswitch-enum"
#endif

enum Foo {
  FOO_BAR,
  FOO_BAZ,
  FOO_QUX,
  FOO_QUUX
};

static void test_unreachable(enum Foo code) {
  switch (code) {
  case FOO_BAR:
  case FOO_BAZ:
  case FOO_QUX:
    break;
  case FOO_QUUX:
    HEDLEY_UNREACHABLE();
  }
}

int main(void) {
  test_unreachable(FOO_QUUX);

  return 0;
}
