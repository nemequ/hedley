#include "../hedley.h"

#if defined(_MSC_VER)
  HEDLEY_DIAGNOSTIC_PUSH
  #pragma warning(disable:4255 4710 4668 4820)
  #include <time.h>
  #include <stdlib.h>
  HEDLEY_DIAGNOSTIC_POP
#else
#  include <time.h>
  #include <stdlib.h>
#endif

HEDLEY_MALLOC
static void* randalloc(size_t size) {
  size_t p;
  unsigned char* r = HEDLEY_STATIC_CAST(unsigned char*, malloc(size));

  for (p = 0 ; p < size ; p++) {
    r[p] = HEDLEY_STATIC_CAST(unsigned char, HEDLEY_STATIC_CAST(unsigned int, rand()) & 0xffU);
  }

  return HEDLEY_STATIC_CAST(void*, r);
}

int main (void) {
  srand(HEDLEY_STATIC_CAST(unsigned int, time(HEDLEY_STATIC_CAST(time_t*, HEDLEY_NULL))));

  free(randalloc(1024));

  return 0;
}
