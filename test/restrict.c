#include "../hedley.h"

void foo(char* HEDLEY_RESTRICT a, char* HEDLEY_RESTRICT b) {
  (void) a;
  (void) b;
}

int main (void) {
  return 0;
}
