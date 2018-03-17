#include "../hedley.h"

HEDLEY_DIAGNOSTIC_PUSH
HEDLEY_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS
#pragma foo
HEDLEY_DIAGNOSTIC_POP

int main (void) {
  return 0;
}
