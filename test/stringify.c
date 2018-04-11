#include "../hedley.h"

#define PREFIX foo_
#define BAR bar

static int
my_strcmp(const char* s1, const char* s2) {
  while (1) {
    if (*s1 < *s2)
      return -1;
    else if (*s1 > *s2)
      return 1;
    else if (*s1 == '\0')
      return 0;
    s1++;
    s2++;
  }
}

static const char*
foo_bar(void) {
  return HEDLEY_STRINGIFY(BAR);
}

int main(void) {
  return my_strcmp("bar", HEDLEY_CONCAT(PREFIX, BAR)());
}
