#include "../hedley.h"

struct Foo {
  int x;
};

#if defined(__GNUC__) && (__GNUC__ >= 4)
__attribute__((__deprecated__))
#else
HEDLEY_DEPRECATED(1.1)
#endif
static int value = 9;

HEDLEY_DEPRECATED(1.0)
static int cube(int x) {
  return x * x * x;
}

HEDLEY_DIAGNOSTIC_PUSH
HEDLEY_DIAGNOSTIC_DISABLE_DEPRECATED
int main (void) {
  struct Foo foo;
  foo.x = value;
  return cube(foo.x);
}
HEDLEY_DIAGNOSTIC_POP
