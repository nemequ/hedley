#include "../hedley.h"

HEDLEY_UNAVAILABLE(3.14)
void test_unavailable(void) { }

int main(int argc, char* argv[HEDLEY_ARRAY_PARAM(argc)]) {
  (void) argc;
  (void) argv;

  test_unavailable();

  return 0;
}
