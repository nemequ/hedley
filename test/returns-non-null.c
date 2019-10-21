#include "../hedley.h"

#include <string.h>

static const char* foo = "bar\n";

HEDLEY_RETURNS_NON_NULL
static const char* get_string(void) {
  return foo;
}

int main(void) {
  const char* s = get_string();
  return HEDLEY_STATIC_CAST(int, strlen(s));
}
