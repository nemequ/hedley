#include "../hedley.h"

HEDLEY_DIAGNOSTIC_PUSH
HEDLEY_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS
#pragma Foo
HEDLEY_DIAGNOSTIC_POP

int main (void) {
  return 0;
}
