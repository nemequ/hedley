#include "../hedley.h"

struct Foo {
  int x;
};

/* For some compilers, deprecated will trigger a different diagnostic
   when it has an attribute. We want to make sure
   HEDLEY_DIAGNOSTIC_DISABLE_DEPRECATED silences both of them, but
   Hedley uses the with attribute version whenever it's
   available. This is only here so we can test both cases; You
   shouldn't do this in your code! */
#if HEDLEY_GNUC_VERSION_CHECK(4,0,0)
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
