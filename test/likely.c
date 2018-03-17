#include "../hedley.h"

static int foo(int x) {
  return HEDLEY_LIKELY(x) ? 1 : 0;
}

int main(int argc, char* argv[HEDLEY_ARRAY_PARAM(argc)]) {
  (void) argc;
  (void) argv;

  return foo(argc);
}
