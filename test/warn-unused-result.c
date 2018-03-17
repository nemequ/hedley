#include "../hedley.h"

HEDLEY_WARN_UNUSED_RESULT
static int test_unused_result(void) {
  return 1729;
}

int main(int argc, char* argv[HEDLEY_ARRAY_PARAM(argc)]) {
  (void) argc;
  (void) argv;

  test_unused_result();

  if (test_unused_result() != 1729)
    return 1;

  return 0;
}
