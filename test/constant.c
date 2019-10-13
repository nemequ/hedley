#if defined(_MSC_VER)
  #pragma warning(push)
  #pragma warning(disable:4668)
  #include <assert.h>
  #include <stddef.h>
  #pragma warning(pop)
#else
  #include <assert.h>
  #include <stddef.h>
#endif

#include "../hedley.h"

int main(int argc, char* argv[HEDLEY_ARRAY_PARAM(argc)]) {
  char foo[HEDLEY_REQUIRE_CONSTEXPR(42)] = { 0, };

  assert(argv[argc - 1] != NULL);
  assert(foo[0] == 0);

#if defined(HEDLEY__IS_CONSTEXPR)
  assert(HEDLEY__IS_CONSTEXPR(1729) == 1);
  assert(HEDLEY__IS_CONSTEXPR(argc) == 0);
#endif

  assert(HEDLEY_IS_CONSTANT(argc) == 0);

  return 0;
}
