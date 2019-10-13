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

int main(void) {
  int x = 0, y = 0;

  y += HEDLEY_PREDICT(x, 0, 0.95);
  y += HEDLEY_PREDICT(x, 0, 0.85);
  y += HEDLEY_PREDICT(x, 0, 0.15);
  y += HEDLEY_PREDICT(x, 0, 0.05);

  y += HEDLEY_PREDICT_TRUE(x, 0.95);
  y += HEDLEY_PREDICT_TRUE(x, 0.85);
  y += HEDLEY_PREDICT_TRUE(x, 0.15);
  y += HEDLEY_PREDICT_TRUE(x, 0.05);

  y += HEDLEY_PREDICT_FALSE(x, 0.95);
  y += HEDLEY_PREDICT_FALSE(x, 0.85);
  y += HEDLEY_PREDICT_FALSE(x, 0.15);
  y += HEDLEY_PREDICT_FALSE(x, 0.05);

  y += HEDLEY_UNPREDICTABLE(x);

  return y;
}
