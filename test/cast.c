#include "../hedley.h"

int main(void) {
  int foo = 0;
  long bar = HEDLEY_STATIC_CAST(long, foo);
  const char* baz = "Hello, world!";
  char* qux = HEDLEY_CONST_CAST(char*, baz);

  if (bar != 0)
    return 1;
  if (baz != qux)
    return 1;

  return 0;
}
