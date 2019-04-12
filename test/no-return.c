#include "../hedley.h"

#if defined(HEDLEY_IAR_VERSION)
#  pragma diag_suppress=Pe082
#endif

#include <stdlib.h>

HEDLEY_NO_RETURN
static void
test_no_return(int code) {
  exit(code);
}

int main(void) {
  test_no_return(0);
}
