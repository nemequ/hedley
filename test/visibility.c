#include <stdlib.h>

#include "../hedley.h"

HEDLEY_PUBLIC
void test_public(void) { }

HEDLEY_PRIVATE
void test_private(void) { }

int main() {
  test_public();
  test_private();

  return EXIT_FAILURE;
}
