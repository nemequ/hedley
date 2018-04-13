#include "../hedley.h"

#include <stddef.h>
#include <assert.h>

static int foo(int x) {
  return HEDLEY_LIKELY(x) ? 1 : 0;
}

int main(int argc, char* argv[HEDLEY_ARRAY_PARAM(argc)]) {
  assert(argv[argc - 1] != NULL);

  return foo(argc);
}
