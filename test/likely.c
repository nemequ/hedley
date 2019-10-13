#include "../hedley.h"

#if defined(_MSC_VER)
  HEDLEY_DIAGNOSTIC_PUSH
  #pragma warning(disable:4668)
  #include <assert.h>
  #include <stddef.h>
  HEDLEY_DIAGNOSTIC_POP
#else
  #include <assert.h>
  #include <stddef.h>
#endif

static int foo(int x) {
  return HEDLEY_LIKELY(x) ? 1 : 0;
}

int main(int argc, char* argv[HEDLEY_ARRAY_PARAM(argc)]) {
  assert(argv[argc - 1] != NULL);

  return foo(argc);
}
