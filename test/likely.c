#include "../hedley.h"

#if defined(_MSC_VER)
  HEDLEY_DIAGNOSTIC_PUSH
  #pragma warning(disable:4668)
  #include <stdio.h>
  HEDLEY_DIAGNOSTIC_POP
#else
  #include <stdio.h>
#endif

int main(int argc, char* argv[]) {
  (void) argv;

  if (HEDLEY_LIKELY(argc == 1)) {
    fputs("Argument required\n", stderr);
    return -1;
  }

  printf("Arguments: %d\n", argc);

  return 0;
}
