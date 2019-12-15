#include "../hedley.h"

#if defined(_MSC_VER)
  HEDLEY_DIAGNOSTIC_PUSH
  #pragma warning(disable:4668)
  #include <assert.h>
  #include <stddef.h>
  HEDLEY_DIAGNOSTIC_POP
#else
  #include <assert.h>
  #include <stddef.h>
#endif

#if \
     defined(HEDLEY_TI_CL6X_VERSION) || \
     defined(HEDLEY_TI_CL7X_VERSION)
/* __builtin_expect with second argument not equal to 0 or 1 is ignored */
#  pragma diag_remark 1362
#endif

static int foo(int x) {
  return HEDLEY_LIKELY(x) ? 1 : 0;
}

int main(int argc, char* argv[HEDLEY_ARRAY_PARAM(argc)]) {
  assert(argv[argc - 1] != NULL);

  assert(HEDLEY_PREDICT(argc + 1, 2, 0.95) == 2);
  assert(HEDLEY_UNPREDICTABLE(argc + 1) == 2);
  assert(HEDLEY_PREDICT_TRUE(argc + 1, 0.95) == 1);
  assert(HEDLEY_PREDICT_FALSE(argc + 1, 0.95) == 1);
  assert(HEDLEY_LIKELY(argc + 1) == 1);
  assert(HEDLEY_UNLIKELY(argc + 1) == 1);

  return foo(argc);
}
