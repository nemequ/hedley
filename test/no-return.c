#include "../hedley.h"

#if !defined(HEDLEY_TI_VERSION)
#  include <stdlib.h>
#endif

HEDLEY_NO_RETURN
static void
test_no_return(int code) {
#if !defined(HEDLEY_TI_VERSION)
  exit(code);
#else
  *((int*) 0) = code;
#endif
}

int main(void) {
  test_no_return(0);
}
