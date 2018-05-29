#include "../hedley.h"

#include <assert.h>

static void acopy(int n, int* HEDLEY_RESTRICT a, int* HEDLEY_RESTRICT b) {
  int i;
  for (i = 0 ; i < n ; i++)
    a[i] = b[i];
}

int main (void) {
  int a[512] = { 0, };
  int b[512];

  acopy(512, b, a);

  return 0;
}
