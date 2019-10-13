#include "../hedley.h"

#if defined(_MSC_VER)
  HEDLEY_DIAGNOSTIC_PUSH
  #pragma warning(disable:4255 4668)
  #include <stdio.h>
  HEDLEY_DIAGNOSTIC_POP
#else
#  include <stdio.h>
#endif

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
