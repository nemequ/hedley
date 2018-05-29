#include "../hedley.h"

#include <stdlib.h>
#include <time.h>

HEDLEY_MALLOC
static void* randalloc(size_t size) {
  size_t p;
  unsigned char* r = (unsigned char*) malloc(size);

  for (p = 0 ; p < size ; p++) {
    r[p] = (unsigned char) (((unsigned int) rand()) & 0xffU);
  }

  return (void*) r;
}

int main (void) {
  srand((unsigned int) time(NULL));

  free(randalloc(1024));

  return 0;
}
