#include "../hedley.h"

#include <stdio.h>

static const char* foo = "bar\n";

HEDLEY_RETURNS_NON_NULL
static const char* get_string(void) {
  return foo;
}

int main(void) {
  const char* s = get_string();
  if (s != HEDLEY_NULL)
    fputs(s, stdout);
  else
    fputs("This shouldn't happen\n", stdout);

  return 0;
}
