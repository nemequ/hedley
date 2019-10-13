#include "../hedley.h"

#if defined(HEDLEY_IAR_VERSION)
#  pragma diag_suppress=Pe082
#endif

#if defined(_MSC_VER)
  HEDLEY_DIAGNOSTIC_PUSH
  #pragma warning(disable:4255 4668)
  #include <stdlib.h>
  HEDLEY_DIAGNOSTIC_POP
#else
  #include <stdlib.h>
#endif

HEDLEY_NO_RETURN
static void
test_no_return(int code) {
  exit(code);
}

int main(void) {
  test_no_return(0);
}
