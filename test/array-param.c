#include "../hedley.h"

static void
clear_buffer (int* buffer_size, unsigned char buffer[HEDLEY_ARRAY_PARAM(*buffer_size)]) {
  int p;
  for (p = 0 ; p < *buffer_size ; p++)
    buffer[p] = 0;
}

int main(int argc, char* argv[HEDLEY_ARRAY_PARAM(argc)]) {
  (void) argc;
  (void) argv;

  unsigned char foo[8192];
  int foo_l = (int) sizeof(foo);

  clear_buffer(&foo_l, foo);

  return 0;
}
