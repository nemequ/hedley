#include <string.h>

#include "../hedley.h"

#define PREFIX foo_
#define BAR bar

const char*
foo_bar(void) {
  return HEDLEY_STRINGIFY(BAR);
}

int main(void) {
  return strcmp("bar", HEDLEY_CONCAT(PREFIX, BAR)());
}
