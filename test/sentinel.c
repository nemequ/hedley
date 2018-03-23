#include "../hedley.h"

#ifndef NULL
#  define NULL 0
#endif

HEDLEY_SENTINEL(0)
int test_sentinel(void* ptr, ...) {
  (void) ptr;

  return 42;
}

int main(int argc, char* argv[HEDLEY_ARRAY_PARAM(argc)]) {
  (void) argc;
  (void) argv;

  test_sentinel(NULL, 1, NULL);
  test_sentinel(NULL, 1);

  return 0;
}
