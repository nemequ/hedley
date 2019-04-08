#include "../hedley.h"

#include <stddef.h>
#include <assert.h>

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
