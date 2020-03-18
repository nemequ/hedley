#include "../hedley.h"

#define FOO a
#define BAR b

static int ab(int v) {
  return v * v;
}

static int a_b(int v) {
  return HEDLEY_CONCAT(FOO, b)(v) * v;
}

int main(int argc, const char** argv) {
  (void) argv;

  return HEDLEY_CONCAT3(FOO, _, BAR)(argc);
}
