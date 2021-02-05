#include "../hedley.h"

#define FOO a
#define BAR b

#if HEDLEY_IAR_VERSION_CHECK(8,5,0)
#  pragma diag_suppress=Pe1818
#endif

static int ab(int v) {
  return v * v;
}

static int a_b(int v) {
  return HEDLEY_CONCAT(FOO, b)(v) * v;
}

int main(int argc, const char** argv) {
  HEDLEY_STATIC_CAST(void, argv);

  return HEDLEY_CONCAT3(FOO, _, BAR)(argc);
}
