/*
  Works:
    suncc 5.13+ (at least)
    clang
   Doesn't:
     gcc
     icc
*/

#include "../hedley.h"

#include <stdlib.h>

HEDLEY_NO_RETURN
void test_no_return(int code) {
  exit(code);
}

int main(void) {
  test_no_return(0);

  return 1;
}
