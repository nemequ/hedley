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

static void
clear_buffer (size_t* buffer_size, unsigned char buffer[HEDLEY_ARRAY_PARAM(*buffer_size)]) {
  size_t p;
  for (p = 0 ; p < *buffer_size ; p++)
    buffer[p] = 0;
}

int main(int argc, char* argv[HEDLEY_ARRAY_PARAM(argc)]) {
  unsigned char foo[8192];
  size_t foo_l = sizeof(foo);

  assert(argv[argc - 1] != NULL);

  clear_buffer(&foo_l, foo);

  return 0;
}
